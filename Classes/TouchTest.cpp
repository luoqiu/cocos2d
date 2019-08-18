#include "TouchTest.h"

USING_NS_CC;

Scene* TouchTest::CreateScene()
{
    // ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto scene = Scene::create();
    
    // ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto layer = TouchTest::create();
    
    // ��HelloWorld����Ϊ�ӽڵ���ӵ�����
    scene->addChild(layer);
    
    // ���س�������
    return scene;
}

// on "init" you need to initialize your instance
bool TouchTest::init()
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
                                           CC_CALLBACK_1(TouchTest::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // ɾ������������
    auto removeAllTouchItem = MenuItemFont::create("delete all listener",
                                                   [this](Ref* sender){
                                                       auto senderItem = static_cast<MenuItemFont*>(sender);
                                                       senderItem->setString("delete success");
                                                       _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
                                                   });
    removeAllTouchItem->setPosition(visibleSize.width/2, visibleSize.height*0.2);
    // �����˵�
    auto menu = Menu::create(removeAllTouchItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // �����ǩ
    auto title = Label::createWithSystemFont("hit sence", "", 64);
    title->setPosition(visibleSize.width/2, visibleSize.height*0.9);
    this->addChild(title);
    
    // ��ʾ��ǩ
    auto subtitle = Label::createWithSystemFont("hit or move", "", 32);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height*0.8);
    this->addChild(subtitle);
    
    // ���������������
    auto sprite1 = Sprite::create("CyanSquare.png");
    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 80));
    addChild(sprite1, 10);
    
    auto sprite2 = Sprite::create("MagentaSquare.png");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(sprite2, 20);
    
    auto sprite3 = Sprite::create("YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, 1);
    
    // �ٴ���һ�����㴥���¼����������������¼��߼�
    auto listener1 = EventListenerTouchOneByOne::create();
    // �����Ƿ����´��ݴ���
    listener1->setSwallowTouches(true);
    // ͨ�� lambda ���ʽ ֱ��ʵ�ִ����¼�����Ӧ����
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        // ��õ�ǰ�¼�������Ŀ�����
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // ��õ�ǰ�Ĵ�����
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        // ��ô��������ContentSize
        Size s = target->getContentSize();
        // ���λ�þ���
        Rect rect = Rect(0, 0, s.width, s.height);
        // ���λ�þ��ΰ���������
        if (rect.containsPoint(locationInNode))
        {
            log("onTouchBegan... x = %f, y = %f", locationInNode.x, locationInNode.y);
            // ����͸����
            target->setOpacity(180);
            // �����û������¼��Ѿ�������������onTouchMoved��onTouchEnded��onTouchCancelled�������Ӧ�������¼��������򲻻���ȥ���м������δ����¼���
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // �ƶ������ľ���
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // ����͸����
        target->setOpacity(255);
        std::string name;
        if (target == sprite2)
        {
            name = "MagentaSquare.png";
            sprite1->setZOrder(100);
            subtitle->setString("set 100");
        }
        else if(target == sprite1)
        {
            name = "CyanSquare.png";
            sprite1->setZOrder(0);
            subtitle->setString("set 0");
        }else{
            name = "YellowSquare.png";
        }
        log("onTouchEnded.. you touch %s",name.c_str());
    };
    
    // ��ӳ��������¼���������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	// ��ע�⣺��ʹ��addEventListenerWithSceneGraphPriority����addEventListenerWithFixedPriority����ʱ��	��Ե�ǰʹ�õ��¼����������һ����ע��ı�ǣ���ʹ�������ܹ�����Ӷ�Ρ����Ե������ٴ�ʹ��listener1��ʱ����Ҫʹ��clone()��������һ���µĿ�¡��
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    
    return true;
}


void TouchTest::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
