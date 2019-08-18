#include "ShowAction.h"
USING_NS_CC;

cocos2d::Scene* ShowAction::CreateScene()
{
	auto scene = Scene::create();
	auto layer = ShowAction::create();
	scene->addChild(layer);

	return scene;
}
bool ShowAction::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto apple = Sprite::create("grossini_dance_11.png");
	apple->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	apple->setVisible(false);
	this->addChild(apple);

	auto show = Show::create();
	apple->runAction(show);
	auto hide = Hide::create();
	apple->runAction(hide);
	auto visibility = ToggleVisibility::create();
	apple->runAction(visibility);
	auto blink = Blink::create(2, 3);
	apple->runAction(blink);

	auto fadeIn = FadeIn::create(5);
	auto fadeInReverse = fadeIn->reverse();
	apple->runAction(Sequence::create(fadeIn, fadeInReverse, NULL));

	auto apple1 = Sprite::create("grossini_dance_12.png");
	apple1->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2));
	this->addChild(apple1);

	auto fadeOut = FadeOut::create(5);
	auto fadeoutreverse = fadeOut->reverse();
	apple1->runAction(Sequence::create(fadeOut, fadeoutreverse, NULL));

	auto apple2 = Sprite::create("grossini_dance_10.png");
	apple2->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2));
	this->addChild(apple2);

	auto tintTo = TintTo::create(5, 255, 255, 0);
	apple2->runAction(tintTo);

	auto moveTo = MoveBy::create(5, Vec2(860,320));
	apple2->runAction(moveTo);

	auto hero = Sprite::create("10001.png");
	hero->setPosition(Vec2(visibleSize.width + hero->getContentSize().width/2, visibleSize.height/2));
	this->addChild(hero);
	auto animation = Animation::create();
	for (int i = 46; i < 55; ++i)
	{
		animation->addSpriteFrameWithFile(StringUtils::format("100%d.png", i));
	}

	animation->setDelayPerUnit(3.0f / 15.0f);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);
	auto animate1 = Animate::create(animation);
	auto animate2 = Animate::create(animation);
	auto repeatanimate = RepeatForever::create(animate);
	auto moveTo1 = MoveTo::create(10.f, Vec2(hero->getContentSize().width/2, visibleSize.height/2));
	hero->runAction(repeatanimate);
	hero->runAction(moveTo1);
	
	auto boss = Sprite3D::create("boss.obj");
	boss->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	boss->setScale(10.f);
	boss->setTexture("boss.png");
	boss->setRotation3D(Vec3(90, 180, 90));
	this->addChild(boss);

	//hero->runAction(animate1);
	//hero->runAction(animate2);
	return true;
}
