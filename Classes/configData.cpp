//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "configData.h"
#include "searchSqlite.h"
#include "ui/CocosGUI.h"
#include <thread>
#include "GetUrl.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace ui;
static const std::string defaultStr = "1";
static const int g_gradeTag = 1;
static const int g_contentTag = 2;

static const std::string g_baiduimgPath = "https://m.baidu.com/sf/vsearch?pd=image_content&atn=page&fr=tab&tn=vsearch&ss=100&sa=tb&rsv_sug4=2235&inputT=2234&word=";

static const int g_maxLen = 200;//ͼƬ������200;

typedef struct _ContentMenu
{
	std::string name;
	//Scene* scene;
	Widget::ccWidgetTouchCallback callBack;
}ContentMenu;

ContentMenu contentMenu[] =
{
	{"��һ������",		[=](Ref* p, Widget::TouchEventType type) {}},
	{"�ظ�����",		[=](Ref* p, Widget::TouchEventType type) {}},
	{"��һ������",		[=](Ref* p, Widget::TouchEventType type) {}},
	{"��ɱ��ڵ���",	[=](Ref* p, Widget::TouchEventType type) {}},
	{"����ѡ���꼶",	[=](Ref* p, Widget::TouchEventType type) {}},
};

cocos2d::Scene * EnglishClass::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = EnglishClass::create();

	// ��HelloWorld����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
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
	if (_stage.empty())
	{
		_stage = "СѧӢ��";
		UserDefault::getInstance()->setStringForKey("stage", _stage);
		UserDefault::getInstance()->flush();
	}

	_sGrade = UserDefault::getInstance()->getStringForKey("grade");
	if (_sGrade.empty())
	{
		_sGrade = "�˽̵�һ��";
		UserDefault::getInstance()->setStringForKey("sGrade", _sGrade);
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
	for (int i = atoi(_index.c_str()) + 1; i < atoi(_wordsOnce.c_str()); ++i)
	{
		HTTPDOWNPTR httpDown(new HttpDown());
		_vecHttpDown.push_back(httpDown);
		_vecSerialumber.push_back(i);
	}

	SearchSqlite::GetInstance().SearchValue(_vecSerialumber, _sGrade, _vecWords);

	return true;
}


void EnglishClass::onEnterGrade()
{
	auto chl = getChildByTag(g_contentTag);
	if (chl)
	{
		removeChildByTag(g_contentTag, true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	// ����ListView�ı���ͼƬ
	listView->setBackGroundImage("green_edit.png");
	// ���ñ���ͼƬ��Ϊ�Ź������
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
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
				//�л�չʾ����;
				_bGradeFlag = false;
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
		// ����һ��Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// ����Button��Name
		custom_button->setName(_vecGrade[i]);
		// ����Button�Ƿ�Ź������
		custom_button->setScale9Enabled(true);
		// ����Button��ContentSize
		custom_button->setContentSize(Size(40, 20));
		// ����Button��TitleTextΪ��Ӧ_array���ı�����
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(_vecGrade[i]);
		// ����Button���ı������С
		custom_button->setTitleFontSize(12);
		
		// ����һ��Layout���������Button
		Layout *custom_item = Layout::create();
		// ����Layout��ContentSize��Button��ContentSizeһ��
		custom_item->setContentSize(custom_button->getContentSize());
		// ����Layout������λ��
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// ��Button���ΪLayout���ֽ�
		custom_item->addChild(custom_button);
		// ��Layout���ΪListView���ӽڵ�
		listView->addChild(custom_item);
		
	}
	{
		// ����һ��Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// ����Button��Name
		custom_button->setName("exit");
		// ����Button�Ƿ�Ź������
		custom_button->setScale9Enabled(true);
		// ����Button��ContentSize
		custom_button->setContentSize(Size(40, 20));
		// ����Button��TitleTextΪ��Ӧ_array���ı�����
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText("exit");
		// ����Button���ı������С
		custom_button->setTitleFontSize(12);

		// ����һ��Layout���������Button
		Layout *custom_item = Layout::create();
		// ����Layout��ContentSize��Button��ContentSizeһ��
		custom_item->setContentSize(custom_button->getContentSize());
		// ����Layout������λ��
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		// ��Button���ΪLayout���ֽ�
		custom_item->addChild(custom_button);
		// ��Layout���ΪListView���ӽڵ�
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
	
	float Imgcale = img.getWidth() > img.getHeight() ? img.getWidth() / g_maxLen : img.getHeight() / g_maxLen;
	std::string imgPath = FileUtils::getInstance()->getWritablePath() + "/" + _vecWords[index] + ".jpg";
	img.saveToFile(imgPath);

	_mUrls.erase(index);

	CCTexture2D texture;

	texture.initWithImage(&img);
	auto sprit = Sprite::createWithTexture(&texture);
	sprit->setPosition(Vec2(200, 200));
	sprit->setScale(1 / Imgcale);
	addChild(sprit);
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

	for (int i = 0; i < _vecHttpDown.size(); ++i)
	{
		HTTPDOWNPTR& http = _vecHttpDown[i];
		if (http->Isbusy())
		{
			if (i == _vecHttpDown.size() - 1)
			{
				i = 0;
			}
			continue;
		}
		else
		{
			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackImg, this));
			http->HttpGetTest(indexVec.vecUrl[indexVec.index]);
		}
	}
}

void EnglishClass::callBackHtml(std::vector<char>* pRes, int index)
{
	//���ҿ���ʹ�õ�ͼƬ
	IndexVec& indexVecTmp = _mUrls[index];
	indexVecTmp.index = -1;

	std::string res(pRes->begin(), pRes->end());
	GetUrl::GetInstance().getUrl(res, indexVecTmp.vecUrl);
	
	RetryDownImg(index);
}

void EnglishClass::ThreadDownImg(int index, const std::string& imgUrl)
{	
	for (int i = 0 ; i < _vecHttpDown.size(); ++i)
	{
		HTTPDOWNPTR& http= _vecHttpDown[i];
		if (http->Isbusy())
		{
			if (i == _vecHttpDown.size()-1)
			{
				i = 0;				
			}
			continue;
		}
		else
		{
			http->SetBackCall(index, CC_CALLBACK_2(EnglishClass::callBackHtml, this));
			http->HttpGetTest(imgUrl);
		}
	}

}

void EnglishClass::ShowWord()
{
	auto imgPath = FileUtils::getInstance()->getWritablePath();
	for (int i = 0 ; i < _vecWords.size();++i)
	{
		std::string img = imgPath + "/" + _vecWords[i] + ".jpg";
		if (!FileUtils::getInstance()->isFileExist(img))
		{
			//�����߳���������ͼƬ
			std::string searchWord=g_baiduimgPath + _vecWords[i];
			std::thread t(&EnglishClass::ThreadDownImg, this, i, img);
			t.detach();
		}

	}
}

void EnglishClass::onEnterContent()
{
	auto chl = getChildByTag(g_gradeTag);
	if (chl)
	{
		removeChildByTag(g_gradeTag, true);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	// ����ListView�ı���ͼƬ
	listView->setBackGroundImage("green_edit.png");
	// ���ñ���ͼƬ��Ϊ�Ź������
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
	listView->addEventListener([=](Ref *pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			int index = listView->getCurSelectedIndex();
			switch (index)
			{
			case 0://�ϸ�����
				_indexWord = (_indexWord + _vecWords.size() - 1) % _vecWords.size();
				break;
			case 1://����
			{
				std::string imgPath = _stage + "/" + _sGrade + "/" + _vecWords[index] + ".wav";
				auto effect = SimpleAudioEngine::getInstance();
				effect->preloadEffect(imgPath.c_str());
				effect->setEffectsVolume(1);
				effect->playEffect(imgPath.c_str());
				break;
			}				
			case 2://�¸�����
				_indexWord = (_indexWord + 1) % _vecWords.size();
				break;
			case 3://��ɱ��ڵ���
				_index = StringUtils::format("%d", _vecWords.size() + atoi(_index.c_str()));
				_indexWord = 0;
				//�����߳��������ͼ���أ�����ͼƬ
				//...
				break;
			case 4://�����꼶ѡ��
// 				auto chlContent = getChildByTag(g_contentTag);
 				if (getChildByTag(g_contentTag))
				{
					removeChildByTag(g_contentTag);
				}
				_bGradeFlag = true;
				break;
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
// 				//�л�չʾ����;
// 				_bGradeFlag = true;
// 			}

			
		}
		default:
			break;
		}
	});

}

void EnglishClass::onEnter()
{
	Layer::onEnter();

	if (_bGradeFlag)
	{
		onEnterGrade();
	}
	else
	{
		onEnterContent();
	}
}
