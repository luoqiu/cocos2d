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
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = ScrollViewTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void ScrollViewTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 添加一个背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);
    Size backgroundSize = background->getContentSize();
    
    // 创建一个ScrollView滚动层容器
    ScrollView* scrollView = ScrollView::create();
    // 激活反弹，拉过了之后，可以弹回来
    scrollView->setBounceEnabled(true);
    // 设置锚点
    scrollView->setAnchorPoint(Vec2::ZERO);
    // 设置滚动方向为水平方向滚动
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    // 设置ScrollView的ContentSize，和背景一致
    scrollView->setContentSize(backgroundSize);
    // 设置滚动层容器的内部容器大小
    scrollView->setInnerContainerSize(scrollView->getContentSize());
    // 设置滚动层容器的位置坐标
    scrollView->setPosition(Vec2((visibleSize.width - backgroundSize.width) / 2.0f +
                                 (backgroundSize.width - scrollView->getContentSize().width) / 2.0f,
                                 (visibleSize.height - backgroundSize.height) / 2.0f +
                                 (backgroundSize.height - scrollView->getContentSize().height) / 2.0f));
    // 将滚动层容器添加为当前层的子节点
    this->addChild(scrollView);
    // 创建一个ImageView
    ImageView* imageView = ImageView::create("ccicon.png");
    float innerWidth = scrollView->getContentSize().width + imageView->getContentSize().width;
    float innerHeight = scrollView->getContentSize().height;
    scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));
    // 创建一个Button
    Button* button = Button::create("animationbuttonnormal.png", "animationbuttonpressed.png");
    button->setPosition(Vec2(button->getContentSize().width / 2.0f,
                             scrollView->getInnerContainerSize().height - button->getContentSize().height / 2.0f));
    // 将Button添加为当前层的子节点
    scrollView->addChild(button);
    // 创建一个Button
    Button* titleButton = Button::create("backtotopnormal.png", "backtotoppressed.png");
    titleButton->setTitleText("Title Button");
    titleButton->setPosition(Vec2(button->getRightBoundary() + button->getContentSize().width / 2.0f,button->getBottomBoundary() - button->getContentSize().height / 2.0f));
    // 将Button添加为当前层的子节点
    scrollView->addChild(titleButton);
    // 创建一个Button
    Button* button_scale9 = Button::create("button.png", "buttonHighlighted.png");
    // 设置九宫格
    button_scale9->setScale9Enabled(true);
    button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
    button_scale9->setPosition(Vec2(titleButton->getRightBoundary() + titleButton->getContentSize().width / 2.0f,titleButton->getBottomBoundary() - titleButton->getContentSize().height / 2.0f));
    // 将Button添加为当前层的子节点
    scrollView->addChild(button_scale9);
    // 设置ImageView的位置在第三个Button之后
    imageView->setPosition(Vec2(innerWidth - button_scale9->getPosition().x,
                                button_scale9->getBottomBoundary() - button_scale9->getContentSize().height / 2.0f));
    // 将ImageView添加为当前层的子节点
    scrollView->addChild(imageView);
    
}

std::string ScrollViewTest::getTitle() const
{
    return "ScrollView Test ";
}


