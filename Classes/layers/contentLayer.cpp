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

using namespace CocosDenshion;
using namespace ui;
std::string ContentLayer::_grade;
static int g_contentLayerTag = 2;

static std::string contentMenu[] =
{
	"上一个单词",
	"重复发音",
	"下一个单词",
	"完成本节单词",
	"返回选择年级",
};


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

	imageDeal::GetInstance().init();
	imageDeal::GetInstance().AddTask(_vecWords);

	return true;
}



void ContentLayer::onEnter()
{
	Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::HORIZONTAL);
	// 设置ListView的背景图片
	listView->setBackGroundImage("green_edit.png");
	// 设置背景图片作为九宫格填充
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(/*Size(visibleSize.width-1, visibleSize.height-1)*/visibleSize - Size(1, 1));
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
				break;
			}
			case 5:
			case 1://发音
			{
				std::string voicePath = "voice/" + _vecWords[_vecWordIndex] + ".wav";
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
			{
				_vecWordIndex = (_vecWordIndex + 1) % _vecWords.size();
				break;
			}
			case 3://完成本节单词
			{
				_gradeWordIndex += _wordsOnce;

				std::vector<int> vecWords;
				DataConfig::getInstance().GetVec(_gradeWordIndex, _wordsOnce, vecWords);
				SearchSqlite::GetInstance().SearchValue(vecWords, _grade, _vecWords);
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
	});

	for (int i = 0; i < sizeof(contentMenu) / sizeof(contentMenu[0]); ++i)
	{
		// 创建一个Button
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("menu");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
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
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, visibleSize.height-40));
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
		custom_button->setTitleText(_vecWords[_vecWordIndex]);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);

		// 创建一个Layout，用来添加Button
		Layout *custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, visibleSize.height - 40));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}

	listView->setTag(g_contentLayerTag);
	addChild(listView);
}