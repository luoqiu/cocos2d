//
//  BaseTest.cpp
//  PhysicsTest
//
//  Created by Jason on 14-3-9.
//
//

#include "BaseTest.h"
#include "Bt.h"

USING_NS_CC;

bool BaseTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 返回菜单，触碰时调用backCallback函数
	auto backMenuItem = MenuItemImage::create("backNormal.png", "backNormal.png", CC_CALLBACK_1(BaseTest::backCallback, this));

	backMenuItem->setPosition(Vec2(visibleSize.width - backMenuItem->getContentSize().width / 2,
		backMenuItem->getContentSize().height / 2));
	
	auto menu = Menu::create(backMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 300);

	return true;
}

// 获取测试标题函数，这里返回的只是一个简单的字符串，该函数应该由子类重写
std::string BaseTest::getTitle() const
{
	return "base_title";
}

// 返回菜单选择场景
void BaseTest::backCallback(Ref *pSender)
{
	//Director::getInstance()->replaceScene(Bt::createScene());
}

