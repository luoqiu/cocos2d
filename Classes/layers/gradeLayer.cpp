#include "gradelayer.h"
#include "dataConfig/dataConfig.h"
#include "sqlite3/searchSqlite.h"
#include "layers/contentLayer.h"
#include "GetUrl.h"

using namespace cocos2d;
using namespace ui;

std::string GradeLayer::_subject = "";

cocos2d::Scene * GradeLayer::createScene(const std::string& subject)
{
	_subject = subject;
	auto scence = Scene::create();
	auto layer = GradeLayer::create();
	scence->addChild(layer);
	return scence;
}

bool GradeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	DataConfig::getInstance().GetValueForKey(_subject, _grade, "RJ_1");
	std::vector<int> vecGrade;
	DataConfig::getInstance().GetVec(1, 10, vecGrade);
	SearchSqlite::GetInstance().SearchValue(vecGrade, _subject, _vecGrade);
	//addLog(_subject);
	return true;
}

void GradeLayer::onEnter()
{
	Layer::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	listView->setBackGroundImage("green_edit.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(visibleSize);
	listView->setPosition(Vec2::ZERO);
	listView->addEventListener([=](Ref* pSender, ListView::EventType type) {
		switch (type)
		{
		case ListView::EventType::ON_SELECTED_ITEM_START:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			break;
		}
		case ListView::EventType::ON_SELECTED_ITEM_END:
		{
			ListView* listView = static_cast<ListView*>(pSender);
			size_t index = listView->getCurSelectedIndex();
			if (index >= _vecGrade.size())
			{
				Director::getInstance()->popScene();				
			}
			else
			{
				auto content = ContentLayer::createScene(_vecGrade[index]);
				Director::getInstance()->pushScene(content);
			}

			break;
		}
		default:
			break;
		}

	});

	this->addChild(listView);

	for (size_t i = 0; i < _vecGrade.size(); ++i)
	{
		std::string btLable;
		DataConfig::getInstance().GetChName(_vecGrade[i], btLable);
		char btLabelChr[64];
		GetUrl::GetInstance().g2u((char*)btLable.c_str(), btLable.size(), btLabelChr, sizeof(btLabelChr));

		auto custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("Title Button");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(BT_WIDE, BT_HEIGHT));
		// 设置Button的TitleText为对应_array的文本内容
		custom_button->setTitleText(btLabelChr);
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);
		// 创建一个Layout，用来添加Button
		auto custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(visibleSize.width / 2, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		//custom_item->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}
	{
		auto custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("Title Button");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(BT_WIDE, BT_HEIGHT));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText("返回上层");
		// 设置Button的文本字体大小
		custom_button->setTitleFontSize(12);
		// 创建一个Layout，用来添加Button
		auto custom_item = Layout::create();
		// 设置Layout的ContentSize和Button的ContentSize一致
		custom_item->setContentSize(custom_button->getContentSize());
		// 设置Layout的坐标位置
		custom_button->setPosition(Vec2(visibleSize.width / 2, custom_item->getContentSize().height / 2.0f));
		// 将Button添加为Layout的字节
		custom_item->addChild(custom_button);
		//custom_item->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		// 将Layout添加为ListView的子节点
		listView->addChild(custom_item);
	}
	listView->setPosition(Vec2::ZERO);
}
