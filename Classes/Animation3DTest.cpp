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
	// ����MenuItemLabel�˵����һ�������ǲ˵�������ʾ�ı�ǩ���󣬵ڶ�����������ҵ��ʱ���õĻص�������
	auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	labelItem->setPosition(Vec2(rand() % (unsigned)visibleSize.width, rand() % (unsigned)visibleSize.height));

	auto menu = Menu::create();
	menu->addChild(labelItem);

	auto label1 = Label::createWithSystemFont("MenuItemLabel", "Marker Felt", 32);
	// ����MenuItemLabel�˵����һ�������ǲ˵�������ʾ�ı�ǩ���󣬵ڶ�����������ҵ��ʱ���õĻص�������
	auto labelItem1 = MenuItemLabel::create(label1, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	labelItem1->setPosition(Vec2(rand() % (unsigned)visibleSize.width, rand() % (unsigned)visibleSize.height));
	menu->addChild(labelItem1);


	// ���ò˵�������Ļ��λ��
	menu->setPosition(Vec2::ZERO);
	menu->setName("menu");
	// ���˵���ӵ���ǰ����ӽڵ�
	this->addChild(menu);
}

void Animation3DTest::menuPrintCallback() {
	log("callback menuPrintCallback-->");
	
	auto menu = this->getChildByName("menu");
	this->detachChild(menu, 0, true);
	newMenu();
}
// ���MenuItemToggle�˵���Ļص�����
void Animation3DTest::menuItemToggle(Ref* pSender) {
	// ��õ���Ĳ˵����������Ĭ������£�On=1��Off=0
	log("selected index:%d",
		dynamic_cast<MenuItemToggle*>(pSender)->getSelectedIndex());
}


// on "init" you need to initialize your instance
bool Animation3DTest::init()
{

	// ���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	// ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �ٱ�ǩ�˵��MenuItemLabel����ʹ��
	auto label = Label::createWithSystemFont("MenuItemLabel", "Marker Felt", 32);
	// ����MenuItemLabel�˵����һ�������ǲ˵�������ʾ�ı�ǩ���󣬵ڶ�����������ҵ��ʱ���õĻص�������
	auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	labelItem->setPosition(visibleSize.width / 2, visibleSize.height*0.9);

	// �ڱ�ǩ�˵��MenuItemFont����ʹ��
	MenuItemFont::setFontName("Courier New"); // ��������
	MenuItemFont::setFontSize(64);  // ���ô�С
	// ����MenuItemFont�˵����һ�������ǲ˵�������ʾ���������ݣ��ڶ�����������ҵ��ʱ���õĻص�������
	auto fontItem = MenuItemFont::create("MenuItemFont", CC_CALLBACK_0(Animation3DTest::menuPrintCallback, this));
	fontItem->setPosition(visibleSize.width / 2, visibleSize.height*0.7);

	// �۾���˵��MenuItemSprite����ʹ��
	auto closeNormal = Sprite::create("CloseNormal.png"); // ��������״̬�������
	auto closeSelected = Sprite::create("CloseSelected.png"); // ����ѡ��״̬�������
	// ����MenuItemSprite�˵��
	// ��һ������������״̬�ľ�����󣬵ڶ���������ѡ��״̬�µľ�����󣬵����������ǻص�������
	auto closeSpriteItem = MenuItemSprite::create(closeNormal, closeSelected, CC_CALLBACK_1(Animation3DTest::menuCloseCallback, this));
	closeSpriteItem->setPosition(visibleSize.width / 2, visibleSize.height*0.5);

	// ��ͼƬ�˵��MenuItemImage����ʹ��
	// ����MenuItemImage�˵��
	// ��һ������������״̬������ͼƬ���ڶ���������ѡ��״̬�µ�����ͼƬ�������������ǻص�������
	// �رղ˵�
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Animation3DTest::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// �ݴ������˵��MenuItemToggle����ʹ��
	// ����MenuItemToggle�˵��
	// ��һ�������ǻص��������ڶ��������͵�������������MenuItem����
	auto toggleItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Animation3DTest::menuItemToggle, this),
		MenuItemFont::create("On"),
		MenuItemFont::create("Off"),
		NULL);
	toggleItem->setPosition(visibleSize.width / 2, visibleSize.height*0.1);

	// �޴���һ���˵���Menu��������װ�ظ��ֲ˵���
	auto menu = Menu::create(labelItem, fontItem, closeSpriteItem, closeItem, toggleItem, NULL);
	// ���ò˵�������Ļ��λ��
	menu->setPosition(Vec2::ZERO);
	menu->setName("menu");
	// ���˵���ӵ���ǰ����ӽڵ�
	this->addChild(menu);
	
	return true;

	/*

	auto sea = Sprite::create("sea.png");
	sea->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(sea);

	std::string fileName = "tortoise.c3b";
	// �ٴ���3D��������������ź�λ��
	_sprite = Sprite3D::create(fileName);
	_sprite->setScale(0.3f);
	_sprite->setPosition(Vec2(visibleSize.width * 4.f / 5.f, visibleSize.height / 2.f));
	this->addChild(_sprite);

	// �ڴ���3D����
	auto animation = Animation3D::create(fileName);
	if (animation)
	{
		// �۴�����Ӿ��3D��������
		_swim = Animate3D::create(animation, 0.f, 1.9f);
		// ��3D���鲻���ظ�ִ����Ӿ�Ķ���
		_sprite->runAction(RepeatForever::create(_swim));
	}
	// �ݴ���MoveTo����
	_moveAction = MoveTo::create(4.f, Vec2(visibleSize.width / 5.f, visibleSize.height / 2.f));
	// �޴���Sequence��϶�������MoveTo����ִ��������reachEndCallBack����
	auto seq = Sequence::create(_moveAction,
		CallFunc::create(CC_CALLBACK_0(Animation3DTest::reachEndCallBack, this)), nullptr);
	// ����Sequence��϶�����tag������֮��ͨ��tagֹͣ����
	seq->setTag(100);
	// ��3D��������Sequnce��϶���
	_sprite->runAction(seq);

	return true;

	*/
}

// 3D����ص�����
void Animation3DTest::reachEndCallBack()
{
	// ����tagֹͣ3D�����������еĶ���
	_sprite->stopActionByTag(100);
	// ��ת_moveAction����
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto moveAction = MoveTo::create(4.f, Vec2(visibleSize.width / 5.f, visibleSize.height / 2.f));
	// RotateBy������ʹ3D�����ת180�ȷ���
	auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
	// Sequence��϶�����˳��ִ��rot��_moveAction����������ִ����֮���ٴε���reachEndCallBack����
	auto seq = Sequence::create(rot, moveAction, CallFunc::create(CC_CALLBACK_0(Animation3DTest::reachEndCallBack, this)), nullptr);
	// ����Sequence��϶�����tag������֮��ͨ��tagֹͣ����
	seq->setTag(100);
	// 3D��������Sequnce��϶���
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

