//
//  ButtonTest.cpp
//  UITest
//
//  Created by apple on 14-8-27.
//
//

#include "ButtonTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* ButtonTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = ButtonTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void ButtonTest::onEnter()
{
    Layer::onEnter();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 提示信息
    message = Label::createWithSystemFont("请触摸按钮", "", 32);
    message->setPosition(visibleSize.width/2, visibleSize.height*0.7);
    this->addChild(message);
    
    // 创建一个Button对象
    auto button = Button::create("button_n.png");
    // 设置规模大小
    button->setScale(1.8);
    // 设置Button上显示的文本
    button->setTitleText("Text Button");
    // 设置Button上显示的文本的字体
    button->setTitleFontName("微软雅黑");
    // 设置Button上显示的文本的字体大小
    button->setTitleFontSize(14);
    // 设置Button的坐标位置
    button->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    /**
     添加触碰监听
     第一个参数是触发事件的对象
     第二个参数是触发事件的类型，分别为BEGAN、MOVED、ENDED和CANCELED
     */
    button->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
        switch (type) {
            case Widget::TouchEventType::BEGAN:
                message->setString("触摸事件类型：BEGAN");
                break;
            case Widget::TouchEventType::MOVED:
                message->setString("触摸事件类型：MOVED");
                break;
            case Widget::TouchEventType::ENDED:
                message->setString("触摸事件类型：ENDED");
                break;
            case Widget::TouchEventType::CANCELED:
                message->setString("触摸事件类型：CANCELED");
                break;
            default:
                break;
        }
    });
    this->addChild(button);
    
}

std::string ButtonTest::getTitle() const
{
    return "Button（按钮） Test ";
}
