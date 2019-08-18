//
//  ScrollViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-6.
//
//

#include "ScrollViewTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* ScrollViewTest::createScene()
{
    // ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto scene = Scene::create();
    
    // ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto layer = ScrollViewTest::create();
    
    // ��HelloWorld����Ϊ�ӽڵ���ӵ�����
    scene->addChild(layer);
    
    // ���س�������
    return scene;
}


void ScrollViewTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // ���һ������
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);
    Size backgroundSize = background->getContentSize();
    
    // ����һ��ScrollView����������
    ScrollView* scrollView = ScrollView::create();
    // �������������֮�󣬿��Ե�����
    scrollView->setBounceEnabled(true);
    // ����ê��
    scrollView->setAnchorPoint(Vec2::ZERO);
    // ���ù�������Ϊˮƽ�������
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    // ����ScrollView��ContentSize���ͱ���һ��
    scrollView->setContentSize(backgroundSize);
    // ���ù������������ڲ�������С
    scrollView->setInnerContainerSize(scrollView->getContentSize());
    // ���ù�����������λ������
    scrollView->setPosition(Vec2((visibleSize.width - backgroundSize.width) / 2.0f +
                                 (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                                 (visibleSize.height - backgroundSize.height) / 2.0f +
                                 (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
    // ���������������Ϊ��ǰ����ӽڵ�
    this->addChild(scrollView);
    // ����һ��ImageView
    ImageView* imageView = ImageView::create("ccicon.png");
    float innerWidth = scrollView->getContentSize().width + imageView->getContentSize().width;
    float innerHeight = scrollView->getContentSize().height;
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
    // ����һ��Button
    Button* button = Button::create("animationbuttonnormal.png", "animationbuttonpressed.png");
    button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                             scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
    // ��Button���Ϊ��ǰ����ӽڵ�
    scrollView->addChild(button);
    // ����һ��Button
    Button* titleButton = Button::create("backtotopnormal.png", "backtotoppressed.png");
    titleButton->setTitleText("Title Button");
    titleButton->setPosition(Vec2(button->getRightBoundary() + button->getContentSize().width / 2.0f,button->getBottomBoundary() - button->getContentSize().height / 2.0f));
    // ��Button���Ϊ��ǰ����ӽڵ�
    scrollView->addChild(titleButton);
    // ����һ��Button
    Button* button_scale9 = Button::create("button.png", "buttonHighlighted.png");
    // ���þŹ���
    button_scale9->setScale9Enabled(true);
    button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
    button_scale9->setPosition(Vec2(titleButton->getRightBoundary() + titleButton->getContentSize().width / 2.0f,titleButton->getBottomBoundary() - titleButton->getContentSize().height / 2.0f));
    // ��Button���Ϊ��ǰ����ӽڵ�
    scrollView->addChild(button_scale9);
    // ����ImageView��λ���ڵ�����Button֮��
    imageView->setPosition(Vec2(innerWidth - button_scale9->getPosition().x,
                                button_scale9->getBottomBoundary() - button_scale9->getContentSize().height / 2.0f));
    // ��ImageView���Ϊ��ǰ����ӽڵ�
    scrollView->addChild(imageView);
    
}

std::string ScrollViewTest::getTitle() const
{
    return "ScrollView Test ";
}


