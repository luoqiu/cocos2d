
//  Downloader.cpp

#include "curltest.h"
#include "curl/curl.h"
#include <cocos-ext.h>

namespace cocos2d
{
	using namespace extension;
	const char* CDownloader::_szUrl = nullptr;
	CDownloader::CDownloader(void)
	{

	}

	CDownloader::~CDownloader(void)
	{

	}
	
	bool CDownloader::getUrlData(const char* szUrl, std::vector<char> & strContent)
	{
		if (szUrl == NULL || strlen(szUrl) < 1)
		{
			log("#### the url invalid");
			return false;
		}
		_szUrl = szUrl;

		CURLcode code;
		std::string strErrorBuffer;

		CURL* curl = curl_easy_init();
		if (curl == NULL)
		{
			log("#### failed to init curl!");
			return false;
		}

		curl_easy_setopt(curl, CURLOPT_URL, szUrl);
		// 保存写入相关参数
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getUrlDataCallback);        //回调函数
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strContent);                        //回调参数
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); // if want to use https  
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false); // set peer and host verify false  
		//curl_easy_setopt(curl, CURLOPT_HTTPGET,1);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		return (code == CURLE_OK);
	}

	size_t CDownloader::getUrlDataCallback(uint8_t* ptrData, size_t size, size_t number, void* pData)
	{
		std::vector<char> * pContent = (std::vector<char> *)pData;
		//pContent->append((char*)ptrData);
		//std::vector<char> *data = (std::vector<char> *)ptrData;
		int len = size * number;
		std::vector<char> data( len);
		memcpy(&data[0], ptrData, len);
		//pContent->push_back(data->begin(), data->end());
		pContent->insert(pContent->end(), data.begin(), data.end());
		return size * number;
	}

} // end of namespace cocos2d