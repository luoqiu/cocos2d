#include "Bt.h"
#include "TouchTest.h"
#include "ui/CocosGUI.h"
#include "LayoutTest.h"
#include "ListViewTest.h"

USING_NS_CC;
using namespace ui;

// ①结构体
typedef struct _Controller
{
	// 菜单项名称
	const std::string itemName;
	// C++11中std::function，使用它可以实现类似函数指针的功能，这里是单击菜单项时返回的场景对象
	std::function<Scene*()> callback;
}Controller;

_Controller itemNames[] =
{
	{ "1. Button Test", []() { return LayoutTest::createScene(); } },
	{ "2. Text  Test", []() { return LayoutTest::createScene(); } },
	{ "3. TextField  Test", []() { return LayoutTest::createScene(); } },
	{ "4. CheckBox Test", []() { return LayoutTest::createScene(); } },
	{ "5. ImageView Test", []() { return LayoutTest::createScene(); } },
	{ "6. LoadingBar Test", []() { return LayoutTest::createScene(); } },
	{ "7. Slider Test", []() { return LayoutTest::createScene(); } },
	{ "8. ListViewTest Test", []() { return ListViewTest::createScene(); } },
};

cocos2d::Scene * Bt::createScene()
{
	auto scene = Scene::create();
	auto layer = Bt::create();
	scene->addChild(layer);
	return scene;
}

static int itemCount = sizeof(itemNames) / sizeof(itemNames[0]);




// ⑦触碰每一个菜单时调用的函数
void Bt::menuBtCallback(Ref * sender)
{
	// 获得触碰的菜单项
	auto menuItem = static_cast<MenuItem *>(sender);
	// 获得之前设置的tag，用于判断触碰的菜单在itemNames中的下标
	int index = menuItem->getTag();
	// 获得对于的场景
	auto scene = itemNames[index].callback();
	// 切换场景
	if (scene)
	{
		Director::getInstance()->replaceScene(scene);
	}
}

bool Bt::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 关闭菜单
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Bt::menuCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

	// 循环添加菜单项
	for (int i = 0; i < itemCount; ++i)
	{
		// 创建Label
		auto label = Label::createWithSystemFont(itemNames[i].itemName, "", 30);
		// 创建menuItemLabel,触碰时调用menuCallback函数
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(Bt::menuBtCallback, this));
		// 设置tag，用于menuCallback中判断触碰的菜单在itemNames中的下标
		menuItem->setTag(i);
		// 将菜单项添加到菜单
		menu->addChild(menuItem);
		// 设置菜单项位置
		menuItem->setPosition(Vec2(label->getContentSize().width/2+50, (visibleSize.height - (i + 1) * 30)));
	}

    
    return true;
}

void Bt::onEnter()
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	message = Label::createWithSystemFont("touch", "", 32);
	message->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7/ 10));
	addChild(message);

	auto button = Button::create("button_n.png");
	//button->setScale(5);
	button->setTitleText("text Button");
	button->setTitleFontSize(14);

	button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	button->addTouchEventListener([=](Ref* p, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			message->setString("BEGAN");
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			message->setString("MOVED");
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			message->setString("ENDED");
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			message->setString("CANCELED");
			break;
		default:
			break;
		}
	});

	addChild(button);

}


void Bt::menuCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TouchTest::CreateScene());
}

std::string Bt::getTitle() const
{
	return std::string("base_title");
}
