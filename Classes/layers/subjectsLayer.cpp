#include "subjectsLayer.h"
#include "gradeLayer.h"

using namespace cocos2d;
using namespace ui;

typedef std::function<void(const std::string&)> menuCallBack;

typedef struct _SubLayerMenu
{
	std::string name;
	menuCallBack callBack;
}SubLayerMenu;

std::string MainMenuName[] =
{
	"小学英语",
	"小学数学",
	"关于",
	"退出",
};

SubLayerMenu menu[] =
{
	{MainMenuName[0], [](const std::string& subName) {auto scence = GradeLayer::createScene(subName);Director::getInstance()->pushScene(scence);	}},
	{MainMenuName[1],  [](const std::string& subName) {} },
	{MainMenuName[2], [](const std::string& subName) {}},
	{MainMenuName[3], [](const std::string& subName) {Director::getInstance()->end(); }},
};

static size_t items = sizeof(menu) / sizeof(menu[0]);

cocos2d::Scene * SubjectsLayer::createScene()
{
	auto scence = Scene::create();
	auto layer = SubjectsLayer::create();
	scence->addChild(layer);
	return scence;
}

void SubjectsLayer::onEnter()
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
			if (index > items - 1)
			{
				break;
			}
			menu[index].callBack(menu[index].name);
		}
		default:
			break;
		}

	});

	this->addChild(listView);

	for (int i = 0; i < items; ++i)
	{
		auto custom_button = Button::create("button.png", "buttonHighlighted.png");
		// 设置Button的Name
		custom_button->setName("Title Button");
		// 设置Button是否九宫格填充
		custom_button->setScale9Enabled(true);
		// 设置Button的ContentSize
		custom_button->setContentSize(Size(40, 20));
		// 设置Button的TitleText为对应_array的文本内容
		//custom_button->setTitleText(StringUtils::format("listview_item_%d", i));
		custom_button->setTitleText(menu[i].name);
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
}
