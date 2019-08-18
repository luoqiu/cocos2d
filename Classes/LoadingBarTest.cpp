//
//  LoadingBarTest.cpp
//  UITest
//
//  Created by apple on 14-9-1.
//
//

#include "LoadingBarTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* LoadingBarTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = LoadingBarTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void LoadingBarTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 为了看的更清楚，添加一个背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);
    // 文本，用来显示进度条的值
    _displayValueLabel = Text::create("Percent = 0","Marker Felt.ttf",48);
    _displayValueLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.8));
    this->addChild(_displayValueLabel);
    // 创建一个LoadingBar
    auto loadingBar = LoadingBar::create("loadingbar.png");
    // 设置进度条从左向右递增
    loadingBar->setDirection(LoadingBar::Direction::LEFT);
    // 设置tag值，之后在update函数中可以通过getChildByTag函数获取这个LoadingBar对象
    loadingBar->setTag(100);
    // 设置坐标位置
    loadingBar->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    // 将LoadingBar添加为当前层的子节点
    this->addChild(loadingBar);
    // 启用定时器回调更新函数
    this->scheduleUpdate();
    
}

// update函数
void LoadingBarTest::update(float delta)
{
    // 自增
    _count++;
    // 当_count变量的值大于100，归零
    if (_count > 100) {
        _count = 0;
    }
    // 通过tag值获得LoadingBar对象
    auto loadingBar = static_cast<LoadingBar*>(this->getChildByTag(100));
    // 修改LoadingBar对象的进度
    loadingBar->setPercent(_count);
    // 在文本中显示LoadingBar对象当前的进度
    _displayValueLabel->setString(StringUtils::format("Percent = %0.0f",loadingBar->getPercent()));
}

std::string LoadingBarTest::getTitle() const
{
    return "LoadingBar（进度条） Test ";
}

