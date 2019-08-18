//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "TextTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* TextTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = TextTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void TextTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 使用系统字体创建一个Text
    auto text1 = Text::create("HelloWorld", "Arial", 48);
    text1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+100));
    this->addChild(text1);
    // 使用ttf文件创建一个字体
    auto text2 = Text::create("HelloWorld", "Marker Felt.ttf", 48);
    text2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-100));
    this->addChild(text2);
}

std::string TextTest::getTitle() const
{
    return "Text（文本） Test ";
}

