//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "configData.h"
#include "sqlite3/searchSqlite.h"
#include "ui/CocosGUI.h"
#include <thread>
#include "GetUrl.h"
#include "SimpleAudioEngine.h"
#include "curltest.h"
using namespace CocosDenshion;
using namespace ui;
static const std::string defaultStr = "1";
static const int g_gradeTag = 1;
static const int g_contentTag = 2;

static const std::string g_baiduimgPath = "https://m.baidu.com/sf/vsearch?pd=image_content&atn=page&fr=tab&tn=vsearch&ss=100&sa=tb&rsv_sug4=2235&inputT=2234&word=";

static const int g_maxLen = 200;//图片最长或最宽200;

typedef struct _ContentMenu
{
	std::string name;
	//Scene* scene;
	//Widget::ccWidgetTouchCallback callBack;
}ContentMenu;

ContentMenu contentMenu[] =
{
	"上一个单词",		//[=](Ref* p, Widget::TouchEventType type) {}},
	"重复发音",		//[=](Ref* p, Widget::TouchEventType type) {}},
	"下一个单词",		//[=](Ref* p, Widget::TouchEventType type) {}},
	"完成本节单词",	//[=](Ref* p, Widget::TouchEventType type) {}},
	"返回选择年级",	//[=](Ref* p, Widget::TouchEventType type) {}}
};

cocos2d::Scene * EnglishClass::createScene()
{
	// 创建一个场景对象，该对象将会由自动释放池管理内存的释放
	auto scene = Scene::create();

	// 创建层对象，该对象将会由自动释放池管理内存的释放
	auto layer = EnglishClass::create();

	// 将HelloWorld层作为子节点添加到场景
	scene->addChild(layer);

	// 返回场景对象
	return scene;
}

void EnglishClass::GetValueForKey(const std::string& key, std::string& value, const std::string& defaultValue)
{
	value = UserDefault::getInstance()->getStringForKey(key.c_str());
	if (value.empty())
	{
		value = defaultValue;
		UserDefault::getInstance()->setStringForKey("stage", defaultValue);
		UserDefault::getInstance()->flush();
	}
}

void EnglishClass::GetVec(std::string& index, std::vector<int>& vec)
{
	vec.clear();
	for (int i = atoi(index.c_str()); i < atoi(_wordsOnce.c_str()); ++i)
	{
		vec.push_back(i);
	}
}

bool EnglishClass::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_indexWord = 0;
	_bGradeFlag = true;

	_stage = UserDefault::getInstance()->getStringForKey("stage");
	if (_stage.empty() || _stage != "小学英语")
	{
		_stage = "小学英语";
		UserDefault::getInstance()->setStringForKey("stage", _stage);
		UserDefault::getInstance()->flush();
	}

	_sGrade = UserDefault::getInstance()->getStringForKey("grade");
	if (_sGrade.empty())
	{
		_sGrade = "人教第一册";
		UserDefault::getInstance()->setStringForKey("grade", _sGrade);
		UserDefault::getInstance()->flush();
	}

	 _index = UserDefault::getInstance()->getStringForKey(_sGrade.c_str());
	if (_index.empty())
	{
		_index = "1";
		UserDefault::getInstance()->setStringForKey(_sGrade.c_str(), _index);
		UserDefault::getInstance()->flush();
	}
	
	_wordsOnce = UserDefault::getInstance()->getStringForKey("_wordsOnce");
	if (_wordsOnce.empty())
	{
		_wordsOnce = "5";
		UserDefault::getInstance()->setStringForKey("_wordsOnce", _wordsOnce);
		UserDefault::getInstance()->flush();
	}

	_vecSerialumber.clear();
	for (int i =  1; i < 10; ++i)
	{
		_vecSerialumber.push_back(i);
	}
	SearchSqlite::GetInstance().SearchValue(_vecSerialumber, _stage, _vecGrade);

	_vecSerialumber.clear();
	_vecHttpDown.clear();
	for (int i = atoi(_index.c_str()) + 1; i <= atoi(_wordsOnce.c_str())+1; ++i)
	{
		HTTPDOWNPTR httpDown(new HttpDown());
		_vecHttpDown.push_back(httpDown);
		_vecSerialumber.push_back(i);
	}

	SearchSqlite::GetInstance().SearchValue(_vecSerialumber, _sGrade, _vecWords);
	DownWordPicture();

	return true;
}

void EnglishClass::onEnterGrade()
{
	//Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize - Size(1, 1));
	listView->addEventListener([=](Ref *pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			int index = listView->getCurSelectedIndex();
			if (index < _vecGrade.size())
			{
				std::string grade = _vecGrade[index];
				std::string gradeIndex;
				GetValueForKey(grade, gradeIndex, defaultStr);
				std::vector<int> vecIndex;
				GetVec(gradeIndex, vecIndex);
				_vecWords.clear();
				SearchSqlite::GetInstance().SearchValue(vecIndex, grade, _vecWords);
				//切换展示内容;
				_bGradeFlag = false;

				auto chl = getChildByTag(g_gradeTag);
				if (chl)
				{
					chl->setVisible(false);
					/*removeChildByTag(g_gradeTag);*/
					removeChild(chl);					
					//onEnterContent();
				}
			}
			else
			{
				Director::getInstance()->popScene();
			}

			break;
		}
		default:
			break;
		}
	});

	for (int i = 0; i < _vecGrade.size(); ++i)
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName(_vecGrade[i]);
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(_vecGrade[i]);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);
		
		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
		
	}
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("exit");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText("返回上级");
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);

		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}

	listView->setTag(g_gradeTag);
	addChild(listView);
}

void EnglishClass::callBackImg(std::vector<char>* pRes, int index)
{
	CCImage img ;
	img.initWithImageData((const unsigned char*)&pRes[0], pRes->size());
	if (img.getWidth() == 0 || img.getHeight() == 0)
	{
		RetryDownImg(index);
		return;
	}	
	
	std::string imgPath = FileUtils::getInstance()->getWritablePath() + "/" + _vecWords[index] + ".jpg";
	if (!img.saveToFile(imgPath, false))
	{
		RetryDownImg(index);
	}
	else
	{
		_mUrls.erase(index);
	}	
}

void EnglishClass::RetryDownImg(int index)
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
		RetryDownImg(index);
		return;
	}

	std::string imgName = _vecWords[index]+".jpg";
	std::string path = FileUtils::getInstance()->getWritablePath() + "/" + imgName;
	
	if (FileUtils::getInstance()->isFileExist(path))
	{
		FileUtils::getInstance()->removeFile(path);
	}

// 	FILE* file = fopen(path.c_str(), "wb");
// 	if (file)
// 	{
// 		int len = fwrite(value.c_str(), 1, value.size(), file);
// 		if (len != value.size())
// 		{
// 			
// 			return;
// 		}
// 
// 		fclose(file);
// 	}

	CCImage img;
	//img.initWithImageData((const unsigned char*)&value[0], value.size());
	img.initWithImageData((const unsigned char*)&vecImg[0], vecImg.size());
	//img.initWithImageFile(path);
	if (img.getWidth() == 0 || img.getHeight() == 0)
	{
		RetryDownImg(index);
		return;
	}

	std::string imgPath = FileUtils::getInstance()->getWritablePath() + "/" + _vecWords[index] + ".jpg";
	if (!img.saveToFile(imgPath, false))
	{
		RetryDownImg(index);
	}
	else
	{
		_mUrls.erase(index);
	}


// 	for (int i = 0; i < _vecHttpDown.size(); ++i)
// 	{
// 		HTTPDOWNPTR& http = _vecHttpDown[i];
// 		if (http->Isbusy())
// 		{
// 			if (i == _vecHttpDown.size() - 1)
// 			{
// 				i = 0;
// 			}
// 			continue;
// 		}
// 		else
// 		{
// 			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackImg, this));
// 			http->HttpGetTest(indexVec.vecUrl[indexVec.index]);
// 		}
// 	}

// 	HTTPDOWNPTR httpDown(new HttpDown());
// 	httpDown->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackImg, this));
// 	httpDown->HttpGetTest(indexVec.vecUrl[indexVec.index]);

// 	HTTPDOWNPTR& http = _vecHttpDown[0];
// 	while (true)
// 	{
// 		if (!http->Isbusy())
// 		{
// 			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackImg, this));
// 			http->HttpGetTest(indexVec.vecUrl[indexVec.index]);
// 			break;
// 		}
// 	}
}

void EnglishClass::callBackHtml(std::vector<char>* pRes, int index)
{
	//查找可以使用的图片
	IndexVec& indexVecTmp = _mUrls[index];
	indexVecTmp.index = -1;

	std::string res(pRes->begin(), pRes->end());
	GetUrl::GetInstance().Pcre2Regex(res, indexVecTmp.vecUrl);
	
	RetryDownImg(index);
}

void EnglishClass::ThreadDownImg(int index, const std::string& imgUrl)
{	
	_mutex.lock();
	CDownloader ttt;
	

	std::vector<char> vecUrl;

	bool rc = ttt.getUrlData(imgUrl.c_str(), vecUrl);
	if (vecUrl.empty())
	{
		_mutex.unlock();
		return;
	}
	log("%s",imgUrl.c_str());
	log("vecUrl size:%d", vecUrl.size());
	IndexVec& indexVecTmp = _mUrls[index];
	indexVecTmp.index = -1;
	std::string value;
	value.assign(vecUrl.begin(), vecUrl.end());
	GetUrl::GetInstance().Pcre2Regex(value, indexVecTmp.vecUrl);

	RetryDownImg(index);
	_mutex.unlock();
// 	for (int i = 0 ; i < _vecHttpDown.size(); ++i)
// 	{
// 		HTTPDOWNPTR& http= _vecHttpDown[i];
// 		if (http->Isbusy())
// 		{
// 			if (i == _vecHttpDown.size()-1)
// 			{
// 				i = 0;				
// 			}
// 			continue;
// 		}
// 		else
// 		{
// 			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackHtml, this));
// 			http->HttpGetTest(imgUrl);
// 		}
// 	}

// 	HTTPDOWNPTR httpDown(new HttpDown());
// 	httpDown->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackHtml, this));
// 	httpDown->HttpGetTest(imgUrl);



// 	HTTPDOWNPTR& http = _vecHttpDown[0];
// 	while (true)
// 	{
// 		if (!http->Isbusy())
// 		{
// 			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackHtml, this));
// 			http->HttpGetTest(imgUrl);
// 			break;
// 		}
// 	}
}

void EnglishClass::DownWordPicture()
{
	auto imgPath = FileUtils::getInstance()->getWritablePath();
	for (int i = 0 ; i < _vecWords.size();++i)
	{
		std::string img = imgPath + "/" + _vecWords[i] + ".jpg";
		if (!FileUtils::getInstance()->isFileExist(img))
		{
			//新启线程网络下载图片
			std::string searchWord=g_baiduimgPath + _vecWords[i];
			std::thread t(&EnglishClass::ThreadDownImg, this, i, searchWord);
			t.detach();			
		}

	}
}

void EnglishClass::LoadImg()
{	
	std::string wordPath = _stage + "/" + _sGrade + "/" + _vecWords[_indexWord] + ".jpg";
	if (!FileUtils::getInstance()->isFileExist(wordPath))
	{
		return;
	}
	CCImage img;
	img.initWithImageFile(wordPath);

	float Imgcale = img.getWidth() > img.getHeight() ? img.getWidth() / g_maxLen : img.getHeight() / g_maxLen;
	CCTexture2D texture;

	texture.initWithImage(&img);
	auto sprit = Sprite::createWithTexture(&texture);
	sprit->setPosition(Vec2(200, 200));
	sprit->setScale(1 / Imgcale);
	addChild(sprit);
}

void EnglishClass::onEnterContent()
{
	//Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(/*Size(visibleSize.width-1, visibleSize.height-1)*/visibleSize - Size(1,1));
	listView->addEventListener([=](Ref *pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			int index = listView->getCurSelectedIndex();
			switch (index)
			{
			case 0://上个单词
				_indexWord = (_indexWord + _vecWords.size() - 1) % _vecWords.size();
				break;
			case 5:
			case 1://发音
			{
				std::string voicePath = _stage + "/" + _sGrade + "/" + _vecWords[_indexWord] + ".wav";
				if (!FileUtils::getInstance()->isFileExist(voicePath))
				{
					log("file %s is not exists", voicePath.c_str());
					break;
				}
				auto effect = SimpleAudioEngine::getInstance();
				effect->preloadEffect(voicePath.c_str());
				effect->setEffectsVolume(1);
				effect->playEffect(voicePath.c_str());
				break;
			}				
			case 2://下个单词
				_indexWord = (_indexWord + 1) % _vecWords.size();
				break;
			case 3://完成本节单词
				_index = StringUtils::format("%d", _vecWords.size() + atoi(_index.c_str()));
				_indexWord = 0;
				//启动线程完成网络图下载，加载图片
				//...
				LoadImg();
				break;
			case 4://返回年级选择
			{
				auto chlContent = getChildByTag(g_contentTag);
				if (chlContent)
				{
					chlContent->setVisible(false);
					removeChildByTag(g_contentTag);
					//onEnterGrade();
				}
				_bGradeFlag = true;
				break;
			}
// 				
			
			default:
				break;
			}

// 			if (index < _vecGrade.size())
// 			{
// 				std::string grade = _vecGrade[index];
// 				std::string gradeIndex;
// 				GetValueForKey(grade, gradeIndex, defaultStr);
// 				std::vector<int> vecIndex;
// 				GetVec(gradeIndex, vecIndex);
// 				_vecWords.clear();
// 				SearchSqlite::GetInstance().SearchValue(vecIndex, grade, _vecWords);
// 				//切换展示内容;
// 				_bGradeFlag = true;
// 			}

			
		}
		default:
			break;
		}
	});

	for (int i = 0; i < sizeof(contentMenu)/sizeof(contentMenu[0]); ++i)
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName(_vecGrade[i]);
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(contentMenu[i].name);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);

		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);

	}
	{
		// 创建一个Button  单词显示
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("exit");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(_vecWords[_indexWord]);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);

		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}

	listView->setTag(g_gradeTag);
	addChild(listView);

}

void EnglishClass::onEnter()
{
	Layer::onEnter();
	onEnterGrade();	
}
void EnglishClass::update(float delta)
{
	Node::update(delta);

	if (_bGradeFlag)
	{
		onEnterGrade();
	}
	else
	{
		onEnterContent();
	}
}
// 
// void EnglishClass::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
// {
// 	//Layer::draw();
// // 	if (_bGradeFlag)
// // 	{
// // 		onEnterGrade();
// // 	}
// // 	else
// // 	{
// // 		onEnterContent();
// // 	}
// }
