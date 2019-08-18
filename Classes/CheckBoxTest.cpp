//
//  CheckBoxTest.cpp
//  UITest
//
//  Created by apple on 14-9-1.
//
//

#include "CheckBoxTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* CheckBoxTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = CheckBoxTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void CheckBoxTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 为了看的更清楚，添加一个背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);
    // 文本，用来显示进度条的值
    _displayValueLabel = Text::create("请触摸复选框", "fonts/Marker Felt.ttf", 32);
    _displayValueLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
    this->addChild(_displayValueLabel);
    // 创建一个CheckBox对象
    auto checkBox = CheckBox::create("check_box_normal.png",
                                          "check_box_normal_press.png",
                                          "check_box_active.png",
                                          "check_box_normal_disable.png",
                                          "check_box_active_disable.png");
    checkBox->setScale(2);
    checkBox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    // // 添加事件监听器
    checkBox->addEventListener([=](Ref* pSender,CheckBox::EventType type){
        switch (type)
        {
            case CheckBox::EventType::SELECTED:
                _displayValueLabel->setString("Selected（选中）");
                break;
                
            case CheckBox::EventType::UNSELECTED:
                _displayValueLabel->setString("Unselected（未选中）");
                break;
                
            default:
                break;
        }

    });
    this->addChild(checkBox);
}

std::string CheckBoxTest::getTitle() const
{
    return "CheckBox（复选框） Test ";
}