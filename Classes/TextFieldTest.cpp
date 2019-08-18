//
//  TextFieldTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "TextFieldTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* TextFieldTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = TextFieldTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void TextFieldTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 添加一个Text，用于显示文本框事件类型
    _displayValueLabel = Text::create("请触摸文本框","Marker Felt.ttf",48);
    _displayValueLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.8));
    this->addChild(_displayValueLabel);
    // 添加一个Text，当数据输入结束时，显示输入的数据
    _messageValueLabel = Text::create("你没有输入数据","Marker Felt.ttf",48);
    _messageValueLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.7));
    this->addChild(_messageValueLabel);
    
    // 添加一个背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-80));
    this->addChild(background);
    
    // 创建文本框
    auto textField = TextField::create("请输入数据", "Arial", 48);
    textField->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2+50));
    // 添加文本框事件监听器
    textField->addEventListener([=](Ref *pSender, TextField::EventType type){
        // 根据文本框的事件类型执行相应的代码
        switch (type)
        {
            case TextField::EventType::ATTACH_WITH_IME:
                _displayValueLabel->setString("输入开始");
                break;
            case TextField::EventType::DETACH_WITH_IME:
            {
                _displayValueLabel->setString("输入完成");
                // 获得文本框输入的数据
                std::string value = textField->getStringValue();
                // 如果数据大于0，显示在_messageValueLabel当中
                if (value.length() > 0)
                {
                    _messageValueLabel->setString("你输入的数据:" + value);
                }
                else
                {
                    _messageValueLabel->setString("你没有输入数据");
                }
            }
                break;
            case TextField::EventType::INSERT_TEXT:
                _displayValueLabel->setString("插入数据");
                break;
            case TextField::EventType::DELETE_BACKWARD:
                _displayValueLabel->setString("删除数据");
                break;
            default:
                break;
        }

    });
    this->addChild(textField);
    
}

std::string TextFieldTest::getTitle() const
{
    return "TextField（文本框） Test ";
}

