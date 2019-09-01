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

	// ���ز˵�������ʱ����backCallback����
	auto backMenuItem = MenuItemImage::create("backNormal.png", "backNormal.png", CC_CALLBACK_1(BaseTest::backCallback, this));

	backMenuItem->setPosition(Vec2(visibleSize.width - backMenuItem->getContentSize().width / 2,
		backMenuItem->getContentSize().height / 2));
	
	auto menu = Menu::create(backMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 300);

	return true;
}

// ��ȡ���Ա��⺯�������ﷵ�ص�ֻ��һ���򵥵��ַ������ú���Ӧ����������д
std::string BaseTest::getTitle() const
{
	return "base_title";
}

// ���ز˵�ѡ�񳡾�
void BaseTest::backCallback(Ref *pSender)
{
	//Director::getInstance()->replaceScene(Bt::createScene());
}

void BaseTest::addLog(const std::string & logTmp)
{
	CCTexture2D* texture = new CCTexture2D();
	static int i = 1;

	texture->initWithString(logTmp.c_str(), "", 15);
	auto sprit = Sprite::createWithTexture(texture);
	sprit->setPosition(Vec2(200, i++ * 20));
	addChild(sprit,5);
}

