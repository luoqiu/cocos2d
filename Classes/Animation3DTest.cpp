//
//  Animation3DTest.cpp
//  Sprite3DTest
//
//  Created by apple on 14-8-16.
//
//

#include "Animation3DTest.h"

USING_NS_CC;

Scene* Animation3DTest::CreateScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Animation3DTest::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void Animation3DTest::newMenu()
{
	auto label = Label::createWithSystemFont("MenuItemLabel", "Marker Felt", 32);
	// 创建MenuItemLabel菜单项，第一个参数是菜单项中显示的标签对象，第二个参数是玩家点击时调用的回调函数。
	auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	labelItem->setPosition(Vec2(rand() % (unsigned)visibleSize.width, rand() % (unsigned)visibleSize.height));

	auto menu = Menu::create();
	menu->addChild(labelItem);

	auto label1 = Label::createWithSystemFont("MenuItemLabel", "Marker Felt", 32);
	// 创建MenuItemLabel菜单项，第一个参数是菜单项中显示的标签对象，第二个参数是玩家点击时调用的回调函数。
	auto labelItem1 = MenuItemLabel::create(label1, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	labelItem1->setPosition(Vec2(rand() % (unsigned)visibleSize.width, rand() % (unsigned)visibleSize.height));
	menu->addChild(labelItem1);


	// 设置菜单项在屏幕的位置
	menu->setPosition(Vec2::ZERO);
	menu->setName("menu");
	// 将菜单添加到当前层的子节点
	this->addChild(menu);
}

void Animation3DTest::menuPrintCallback() {
	log("callback menuPrintCallback-->");
	
	auto menu = this->getChildByName("menu");
	this->detachChild(menu, 0, true);
	newMenu();
}
// 点击MenuItemToggle菜单项的回调函数
void Animation3DTest::menuItemToggle(Ref* pSender) {
	// 获得点击的菜单项的索引，默认情况下，On=1，Off=0
	log("selected index:%d",
		dynamic_cast<MenuItemToggle*>(pSender)->getSelectedIndex());
}


// on "init" you need to initialize your instance
bool Animation3DTest::init()
{

	// 调用父类的init函数
	if (!Layer::init())
	{
		return false;
	}

	// 获得设备支持的可见OpenGL视图大小（即窗口大小）。
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ①标签菜单项（MenuItemLabel）的使用
	auto label = Label::createWithSystemFont("MenuItemLabel", "Marker Felt", 32);
	// 创建MenuItemLabel菜单项，第一个参数是菜单项中显示的标签对象，第二个参数是玩家点击时调用的回调函数。
	auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	labelItem->setPosition(visibleSize.width / 2, visibleSize.height*0.9);

	// ②标签菜单项（MenuItemFont）的使用
	MenuItemFont::setFontName("Courier New"); // 设置字体
	MenuItemFont::setFontSize(64);  // 设置大小
	// 创建MenuItemFont菜单项，第一个参数是菜单项中显示的文字内容，第二个参数是玩家点击时调用的回调函数。
	auto fontItem = MenuItemFont::create("MenuItemFont", CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	fontItem->setPosition(visibleSize.width / 2, visibleSize.height*0.7);

	// ③精灵菜单项（MenuItemSprite）的使用
	auto closeNormal = Sprite::create("CloseNormal.png"); // 创建正常状态精灵对象
	auto closeSelected = Sprite::create("CloseSelected.png"); // 创建选择状态精灵对象
	// 创建MenuItemSprite菜单项，
	// 第一个参数是正常状态的精灵对象，第二个参数是选择状态下的精灵对象，第三个参数是回调函数。
	auto closeSpriteItem = MenuItemSprite::create(closeNormal, closeSelected, CC_CALLBACK_1(Animation3DTest::menuCloseCallback, this));
	closeSpriteItem->setPosition(visibleSize.width / 2, visibleSize.height*0.5);

	// ④图片菜单项（MenuItemImage）的使用
	// 创建MenuItemImage菜单项，
	// 第一个参数是正常状态的纹理图片，第二个参数是选择状态下的纹理图片，第三个参数是回调函数。
	// 关闭菜单
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Animation3DTest::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// ⑤触发器菜单项（MenuItemToggle）的使用
	// 创建MenuItemToggle菜单项，
	// 第一个参数是回调函数，第二个参数和第三个参数都是MenuItem对象
	auto toggleItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Animation3DTest::menuItemToggle, this),
		MenuItemFont::create("On"),
		MenuItemFont::create("Off"),
		NULL);
	toggleItem->setPosition(visibleSize.width / 2, visibleSize.height*0.1);

	// ⑥创建一个菜单（Menu），用来装载各种菜单项
	auto menu = Menu::create(labelItem, fontItem, closeSpriteItem, closeItem, toggleItem, NULL);
	// 设置菜单项在屏幕的位置
	menu->setPosition(Vec2::ZERO);
	menu->setName("menu");
	// 将菜单添加到当前层的子节点
	this->addChild(menu);
	
	return true;

	/*

	auto sea = Sprite::create("sea.png");
	sea->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(sea);

	std::string fileName = "tortoise.c3b";
	// ①创建3D精灵对象，设置缩放和位置
	_sprite = Sprite3D::create(fileName);
	_sprite->setScale(0.3f);
	_sprite->setPosition(Vec2(visibleSize.width * 4.f / 5.f, visibleSize.height / 2.f));
	this->addChild(_sprite);

	// ②创建3D动画
	auto animation = Animation3D::create(fileName);
	if (animation)
	{
		// ③创建游泳的3D动画动作
		_swim = Animate3D::create(animation, 0.f, 1.9f);
		// ④3D精灵不断重复执行游泳的动作
		_sprite->runAction(RepeatForever::create(_swim));
	}
	// ⑤创建MoveTo动作
	_moveAction = MoveTo::create(4.f, Vec2(visibleSize.width / 5.f, visibleSize.height / 2.f));
	// ⑥创建Sequence组合动作，当MoveTo动作执行完后调用reachEndCallBack函数
	auto seq = Sequence::create(_moveAction,
		CallFunc::create(CC_CALLBACK_0(Animation3DTest::reachEndCallBack, this)), nullptr);
	// 设置Sequence组合动作的tag，用于之后通过tag停止动作
	seq->setTag(100);
	// ⑦3D精灵运行Sequnce组合动作
	_sprite->runAction(seq);

	return true;

	*/
}

// 3D精灵回调函数
void Animation3DTest::reachEndCallBack()
{
	// 根据tag停止3D精灵正在运行的动作
	_sprite->stopActionByTag(100);
	// 反转_moveAction动作
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto moveAction = MoveTo::create(4.f, Vec2(visibleSize.width / 5.f, visibleSize.height / 2.f));
	// RotateBy动作，使3D精灵调转180度方向
	auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
	// Sequence组合动作，顺序执行rot和_moveAction动作，动作执行完之后再次调用reachEndCallBack函数
	auto seq = Sequence::create(rot, moveAction, CallFunc::create(CC_CALLBACK_0(Animation3DTest::reachEndCallBack, this)), nullptr);
	// 设置Sequence组合动作的tag，用于之后通过tag停止动作
	seq->setTag(100);
	// 3D精灵运行Sequnce组合动作
	_sprite->runAction(seq);
}

void Animation3DTest::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Animation3DTest::menuCallback(Ref* pSender)
{
	auto label = Label::createWithSystemFont("menuitemlabel", "Marker Felt", 32);
	auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_1(Animation3DTest::menuCallback, this));
	labelItem->setPosition(Vec2(rand() % 300, rand() % 500));
	this->addChild(labelItem,1);
	log("asdfsf");	
}

