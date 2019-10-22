//
//  ListViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//
//#include "ContentLayer.h"
#include "contentLayer.h"
#include "dataConfig/dataConfig.h"
#include "sqlite3/searchSqlite.h"
#include "dealImg/dealImage.h"
#include "SimpleAudioEngine.h"
#include "logger/logger.h"

using namespace CocosDenshion;
using namespace ui;
std::string ContentLayer::_grade;
static int g_contentLayerTag = 2;
static int g_spriteWordImgTag = 3;
static int g_labelWordImgTag = 4;

static std::string contentMenu[] =
{
	"上一个单词",
	"重复发音",
	"下一个单词",
	"完成本节单词",
	"返回选择年级",
};

static int menuNum = sizeof(contentMenu) / sizeof(contentMenu[0]);

cocos2d::Scene * ContentLayer::createScene(const std::string& grade)
{
	_grade = grade;
	auto scence = Scene::create();
	auto layer = ContentLayer::create();
	scence->addChild(layer);
	return scence;
}


bool ContentLayer::init()
{
	_wordImg = new CCImage();
	_textureTitle = new CCTexture2D();
	_textureImg = new CCTexture2D();

	if (!Layer::init())
	{
		return false;
	}

	_vecWordIndex = 0;

	std::string tmpValue;
	DataConfig::getInstance().GetValueForKey(_grade, tmpValue, "1");
	_gradeWordIndex = atoi(tmpValue.c_str());

	DataConfig::getInstance().GetValueForKey("_wordsOnce", tmpValue, "5");
	_wordsOnce= atoi(tmpValue.c_str());

	std::vector<int> vecWords;
	DataConfig::getInstance().GetVec(_gradeWordIndex, _wordsOnce, vecWords);
	SearchSqlite::GetInstance().SearchValue(vecWords, _grade, _vecWords);

	imageDeal::GetInstance().AddThread();
	imageDeal::GetInstance().AddTask(_vecWords);

	auto effect = SimpleAudioEngine::getInstance();
	effect->setEffectsVolume(1);
	for (int i=0;i< _vecWords.size();++i)
	{
		std::string voicePath = "voice/" + _vecWords[i] + ".wav";
		if (!FileUtils::getInstance()->isFileExist(voicePath))
		{
			log("file %s is not exists", voicePath.c_str());
			continue;;
		}
		effect->preloadEffect(voicePath.c_str());
	}


	return true;
}


void ContentLayer::wordVoice()
{
	std::string voicePath = "voice/" + _vecWords[_vecWordIndex] + ".wav";
	if (!FileUtils::getInstance()->isFileExist(voicePath))
	{
		log("file %s is not exists", voicePath.c_str());
		return;
	}
	auto effect = SimpleAudioEngine::getInstance();

	effect->playEffect(voicePath.c_str());
}

void ContentLayer::onEnterContent()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(/*Size(visibleSize.width-1, visibleSize.height-1)*/visibleSize);
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
			{
				_vecWordIndex = (_vecWordIndex + _vecWords.size() - 1) % _vecWords.size();
				wordVoice();
				break;
			}
			case 5:
			case 1://发音
			{
				wordVoice();
				break;
			}
			case 2://下个单词
			{
				_vecWordIndex = (_vecWordIndex + 1) % _vecWords.size();
				wordVoice();
				break;
			}
			case 3://完成本节单词
			{
				_gradeWordIndex += _wordsOnce;
				_vecWordIndex = 0;
				UserDefault::getInstance()->setIntegerForKey(_grade.c_str(), _gradeWordIndex);
				std::vector<int> vecWords;
				DataConfig::getInstance().GetVec(_gradeWordIndex, _wordsOnce, vecWords);

				_vecWords.clear();
				SearchSqlite::GetInstance().SearchValue(vecWords, _grade, _vecWords);
				if (_vecWords.size() < _wordsOnce)
				{
					_gradeWordIndex = 1;
					vecWords.clear();
					DataConfig::getInstance().GetVec(_gradeWordIndex, _wordsOnce, vecWords);

					_vecWords.clear();
					SearchSqlite::GetInstance().SearchValue(vecWords, _grade, _vecWords);
				}
				imageDeal::GetInstance().AddTask(_vecWords);

				break;
			}
			case 4://返回年级选择
			{
				Director::getInstance()->popScene();
				break;
			}
			// 				

			default:
				break;
			}
			
		}
		default:
			break;
		}
		this->scheduleUpdate();
	});

	for (int i = 0; i < sizeof(contentMenu) / sizeof(contentMenu[0]); ++i)
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setTag(i);
		custom_button->setName("menu");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(BT_WIDE + 20, BT_HEIGHT));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(contentMenu[i]);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);
		
		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, visibleSize.height / 2));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}


	listView->setPosition(Vec2::ZERO);
	listView->setTag(g_contentLayerTag);
	addChild(listView);
}

void ContentLayer::onEnter()
{
	Layer::onEnter();

	onEnterContent();
}

void ContentLayer::imgCallBack()
{
	log("asfdasfd");
}

void ContentLayer::update(float delta)
{
	Node::update(delta);

	auto winsize = Director::getInstance()->getVisibleSize();
	auto lbtmp = getChildByTag(g_labelWordImgTag);
	if (lbtmp)
	{
		removeChildByTag(g_labelWordImgTag);
		lbtmp->release();
	}

	auto lb = Label::createWithSystemFont(_vecWords[_vecWordIndex], "", 20);
	
	lb->setPosition(Size(winsize.width/2, winsize.height-60));
	lb->setTag(g_labelWordImgTag);
	addChild(lb);

	std::string path = FileUtils::getInstance()->getWritablePath()+ _vecWords[_vecWordIndex] + ".jpg";
	if (FileUtils::getInstance()->isFileExist(path))
	{		
		auto sp = (MenuItemImage*)getChildByTag(g_spriteWordImgTag);
		if (sp)
		{
			sp->removeAllChildrenWithCleanup(true);
			removeChild(sp);
		}
		_wordImg->initWithImageFile(path);
		float scale = _wordImg->getWidth() > _wordImg->getHeight() ? _wordImg->getWidth() / 160 : _wordImg->getHeight() / 160;
		
		
		_textureImg->initWithImage(_wordImg);
		auto sprit = Sprite::createWithTexture(_textureImg);	
		sprit->setContentSize(sprit->getContentSize()/ scale);
		//sprit->setScale(1 / scale);
		//sprit->setTag(g_spriteWordImgTag);
		sprit->setPosition(Vec2(winsize.width/2,sprit->getContentSize().height/ 2));
		//addChild(sprit, 5);	

		auto imgmenuTmp = getChildByTag(g_spriteWordImgTag);
		if (imgmenuTmp)
		{
			removeChildByTag(g_spriteWordImgTag);
			imgmenuTmp->release();
		}
		
		auto imgItem = MenuItemImage::create();
		_textureTitle->initWithString("hahaha", "", 40);
		auto spriteMean = Sprite::createWithTexture(_textureTitle);
		spriteMean->setPosition(Vec2(winsize.width / 2, sprit->getContentSize().height / 2));
		imgItem->initWithNormalSprite(sprit, spriteMean,NULL,CC_CALLBACK_0(ContentLayer::imgCallBack,this));
		imgItem->setTag(g_spriteWordImgTag);
		
		addChild(imgItem, 5);

	}
}
