#include "Bt.h"
#include "TouchTest.h"
#include "ui/CocosGUI.h"
#include "LayoutTest.h"
#include "ListViewTest.h"

USING_NS_CC;
using namespace ui;

// �ٽṹ��
typedef struct _Controller
{
	// �˵�������
	const std::string itemName;
	// C++11��std::function��ʹ��������ʵ�����ƺ���ָ��Ĺ��ܣ������ǵ����˵���ʱ���صĳ�������
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




// �ߴ���ÿһ���˵�ʱ���õĺ���
void Bt::menuBtCallback(Ref * sender)
{
	// ��ô����Ĳ˵���
	auto menuItem = static_cast<MenuItem *>(sender);
	// ���֮ǰ���õ�tag�������жϴ����Ĳ˵���itemNames�е��±�
	int index = menuItem->getTag();
	// ��ö��ڵĳ���
	auto scene = itemNames[index].callback();
	// �л�����
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
    
    // ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �رղ˵�
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Bt::menuCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

	// ѭ����Ӳ˵���
	for (int i = 0; i < itemCount; ++i)
	{
		// ����Label
		auto label = Label::createWithSystemFont(itemNames[i].itemName, "", 30);
		// ����menuItemLabel,����ʱ����menuCallback����
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(Bt::menuBtCallback, this));
		// ����tag������menuCallback���жϴ����Ĳ˵���itemNames�е��±�
		menuItem->setTag(i);
		// ���˵�����ӵ��˵�
		menu->addChild(menuItem);
		// ���ò˵���λ��
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
