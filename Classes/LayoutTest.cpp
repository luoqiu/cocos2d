//
//  LayoutTest.cpp
//  UITest
//
//  Created by apple on 14-9-7.
//
//

#include "LayoutTest.h"
#include "Bt.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* LayoutTest::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = LayoutTest::create();

	// ��HelloWorld����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
	return scene;
}


void LayoutTest::onEnter()
{
	Layer::onEnter();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ��ߵı���
	auto background_Left = Sprite::create("background.png");
	background_Left->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	background_Left->setPosition(Vec2(0, visibleSize.height / 2));
	this->addChild(background_Left, 0);

	// ������ߵ�Layout
	Layout* layout_Left = Layout::create();
	// ����Layout�Ĳ�������Ϊƽ����Բ���
	layout_Left->setLayoutType(LayoutType::RELATIVE);
	// ����Layout��ContentSize
	layout_Left->setContentSize(Size(280, 150));
	// ����Layout��ê��
	layout_Left->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	// ����Layout�ı�����ɫ����Ϊ��һ�̶���ɫ
	layout_Left->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	// ����Layout�ı�����ɫΪ��ɫ
	layout_Left->setBackGroundColor(Color3B::GREEN);
	// ����Layout��λ��
	layout_Left->setPosition(Vec2(layout_Left->getContentSize().width, visibleSize.height / 2));
	// ��Layout���Ϊ��ǰ����ӽڵ�
	this->addChild(layout_Left, 1);

	// ����һ��Button����������Layout�����Ͻ�
	Button* button_TopLeft = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_TopLeft);
	RelativeLayoutParameter* rp_TopLeft = RelativeLayoutParameter::create();
	rp_TopLeft->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
	button_TopLeft->setLayoutParameter(rp_TopLeft);

	// ����һ��Button����������Layout���Ϸ��м�λ��
	Button* button_TopCenter = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_TopCenter);
	RelativeLayoutParameter* rp_TopCenter = RelativeLayoutParameter::create();
	rp_TopCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
	button_TopCenter->setLayoutParameter(rp_TopCenter);

	// ����һ��Button����������Layout�����Ͻ�
	Button* button_TopRight = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_TopRight);
	RelativeLayoutParameter* rp_TopRight = RelativeLayoutParameter::create();
	rp_TopRight->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
	button_TopRight->setLayoutParameter(rp_TopRight);

	// ����һ��Button����������Layout���м�λ�õ����
	Button* button_LeftCenter = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_LeftCenter);
	RelativeLayoutParameter* rp_LeftCenter = RelativeLayoutParameter::create();
	rp_LeftCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_CENTER_VERTICAL);
	button_LeftCenter->setLayoutParameter(rp_LeftCenter);


	// ����һ��Button����������Layout���м�λ��
	Button* buttonCenter = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(buttonCenter);
	RelativeLayoutParameter* rpCenter = RelativeLayoutParameter::create();
	rpCenter->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
	buttonCenter->setLayoutParameter(rpCenter);


	// ����һ��Button����������Layout���м�λ�õ��ұ�
	Button* button_RightCenter = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_RightCenter);
	RelativeLayoutParameter* rp_RightCenter = RelativeLayoutParameter::create();
	rp_RightCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_CENTER_VERTICAL);
	button_RightCenter->setLayoutParameter(rp_RightCenter);


	// ����һ��Button����������Layout�����½�
	Button* button_LeftBottom = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_LeftBottom);
	RelativeLayoutParameter* rp_LeftBottom = RelativeLayoutParameter::create();
	rp_LeftBottom->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM);
	button_LeftBottom->setLayoutParameter(rp_LeftBottom);

	// ����һ��Button����������Layout�ĵײ����м�λ��
	Button* button_BottomCenter = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_BottomCenter);
	RelativeLayoutParameter* rp_BottomCenter = RelativeLayoutParameter::create();
	rp_BottomCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
	button_BottomCenter->setLayoutParameter(rp_BottomCenter);

	// ����һ��Button����������Layout�����½�
	Button* button_RightBottom = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	layout_Left->addChild(button_RightBottom);
	RelativeLayoutParameter* rp_RightBottom = RelativeLayoutParameter::create();
	rp_RightBottom->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM);
	button_RightBottom->setLayoutParameter(rp_RightBottom);

	/******************************************/

	// �ұߵı���
	auto background_Right = Sprite::create("background.png");
	background_Right->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	background_Right->setPosition(Vec2(visibleSize.width - background_Right->getContentSize().width, visibleSize.height / 2));
	this->addChild(background_Right);

	// �����ұߵ�Layout
	Layout* layout_Right = Layout::create();
	// ����Layout�Ĳ�������Ϊƽ����Բ���
	layout_Right->setLayoutType(LayoutType::RELATIVE);
	layout_Right->setContentSize(Size(280, 150));
	layout_Right->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	// ����Layout��λ��
	layout_Right->setPosition(Vec2(visibleSize.width - layout_Right->getContentSize().width - 100, visibleSize.height / 2));
	this->addChild(layout_Right,1);

	// ����һ��ͼƬ����Layout���м�λ��
	ImageView* imageView_Center = ImageView::create("scrollviewbg.png");
	layout_Right->addChild(imageView_Center);
	RelativeLayoutParameter* rp_Center = RelativeLayoutParameter::create();
	rp_Center->setRelativeName("rp_Center");
	rp_Center->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
	imageView_Center->setLayoutParameter(rp_Center);

	// ����һ��ͼƬ����Layout���м�λ�õ��Ϸ�
	ImageView* imageView_AboveCenter = ImageView::create("animationbuttonnormal.png");
	layout_Right->addChild(imageView_AboveCenter);
	RelativeLayoutParameter* rp_AboveCenter = RelativeLayoutParameter::create();
	rp_AboveCenter->setRelativeToWidgetName("rp_Center");
	rp_AboveCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_ABOVE_CENTER);
	imageView_AboveCenter->setLayoutParameter(rp_AboveCenter);

	// ����һ��ͼƬ����Layout���м�λ�õ��·�
	ImageView* imageView_BelowCenter = ImageView::create("animationbuttonnormal.png");
	layout_Right->addChild(imageView_BelowCenter);
	RelativeLayoutParameter* rp_BelowCenter = RelativeLayoutParameter::create();
	rp_BelowCenter->setRelativeToWidgetName("rp_Center");
	rp_BelowCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER);
	imageView_BelowCenter->setLayoutParameter(rp_BelowCenter);

	// ����һ��ͼƬ����Layout���м�λ�õ����
	ImageView* imageView_LeftCenter = ImageView::create("animationbuttonnormal.png");
	layout_Right->addChild(imageView_LeftCenter);
	RelativeLayoutParameter* rp_LeftOfCenter = RelativeLayoutParameter::create();
	rp_LeftOfCenter->setRelativeToWidgetName("rp_Center");
	rp_LeftOfCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_LEFT_OF_CENTER);
	imageView_LeftCenter->setLayoutParameter(rp_LeftOfCenter);

	// ����һ��ͼƬ����Layout���м�λ�õ��ұ�
	ImageView* imageView_RightCenter = ImageView::create("animationbuttonnormal.png");
	layout_Right->addChild(imageView_RightCenter);
	RelativeLayoutParameter* rp_RightOfCenter = RelativeLayoutParameter::create();
	rp_RightOfCenter->setRelativeToWidgetName("rp_Center");
	rp_RightOfCenter->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_RIGHT_OF_CENTER);
	imageView_RightCenter->setLayoutParameter(rp_RightOfCenter);

}

std::string LayoutTest::getTitle() const
{
	return "Layout  Test ";
}