#include "dealImage.h"
#include <thread>
#include "curltest.h"
#include "GetUrl.h"

using namespace cocos2d;
static const std::string g_baiduimgPath = "https://m.baidu.com/sf/vsearch?pd=image_content&atn=page&fr=tab&tn=vsearch&ss=100&sa=tb&rsv_sug4=2235&inputT=2234&word=";

void imageDeal::AddThread()
{
	std::thread t(&imageDeal::run, this);
	t.detach();
}

imageDeal & imageDeal::GetInstance()
{
	// TODO: 在此处插入 return 语句
	static imageDeal imgDeal;
	return imgDeal;
}

void imageDeal::AddTask(const std::vector<std::string>& vecWords)
{
	_mutex.lock();
	for (int i = 0; i< vecWords.size();++i)
	{
		auto imgPath = FileUtils::getInstance()->getWritablePath();

		std::string img = imgPath + "/" + vecWords[i] + ".jpg";
	
		if (!FileUtils::getInstance()->isFileExist(img))
		{
			std::string tmp(vecWords[i]);
			size_t nPos = tmp.find(' ');
			while (nPos != std::string::npos)
			{
				tmp.replace(nPos, 1, "+");
				nPos = tmp.find(' ');
			}
			_queWords.push(tmp);
		}
	}
	_mutex.unlock();
}

void imageDeal::run()
{
	int index = 0;
	while (true)
	{		
		if (_queWords.size() == 0)
		{
			break;
		}		

		_mutex.lock();
		_currentWord = _queWords.front();
		_queWords.pop();
		_mutex.unlock();

		//新启线程网络下载图片
		std::string searchWord = g_baiduimgPath + _currentWord;

		CDownloader ttt;
		std::vector<char> vecUrl;

		bool rc = ttt.getUrlData(searchWord.c_str(), vecUrl);
		if (vecUrl.empty())
		{
			continue;;
		}

		IndexVec& indexVecTmp = _mUrls[index];
		indexVecTmp.index = -1;

		size_t nPos = _currentWord.find('+');
		while (nPos != std::string::npos)
		{
			_currentWord.replace(nPos, 1, " ");
			nPos = _currentWord.find('+');
		}

		indexVecTmp.word = _currentWord;
		std::string value;
		value.assign(vecUrl.begin(), vecUrl.end());
		GetUrl::GetInstance().Pcre2Regex(value, indexVecTmp.vecUrl);

		TryDownImg(index);
	}
}

void imageDeal::TryDownImg(int index)
{
	IndexVec& indexVec = _mUrls[index];
	indexVec.index++;
	if (indexVec.index >= indexVec.vecUrl.size())
	{
		_mUrls.erase(index);
		return;
	}

	CDownloader ttt;
	//std::string value;
	std::vector<char> vecImg;
	ttt.getUrlData(indexVec.vecUrl[indexVec.index].c_str(), vecImg);

	if (vecImg.empty())
	{
		TryDownImg(index);
		return;
	}

	std::string imgName = indexVec.word + ".jpg";
	std::string path = FileUtils::getInstance()->getWritablePath() + "/" + imgName;

	if (FileUtils::getInstance()->isFileExist(path))
	{
		FileUtils::getInstance()->removeFile(path);//
	}

	CCImage img;
	img.initWithImageData((const unsigned char*)&vecImg[0], vecImg.size());
	if (img.getWidth() == 0 || img.getHeight() == 0)
	{
		TryDownImg(index);
		return;
	}

	std::string imgPath = FileUtils::getInstance()->getWritablePath() + "/" + indexVec.word + ".jpg";
	if (!img.saveToFile(imgPath, false))
	{
		TryDownImg(index);
	}
	else
	{
		_mUrls.erase(index);
	}
}


