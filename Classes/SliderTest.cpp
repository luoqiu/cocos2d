//
//  SliderTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#include "SliderTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* SliderTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = SliderTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void SliderTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 添加背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);
    // 文本，用来显示滑动条的值
    _displayValueLabel = Text::create("请滑动滑动条","Marker Felt.ttf",48);
    _displayValueLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.8));
    this->addChild(_displayValueLabel);
    // 创建一个滑动条
    auto slider = Slider::create();
    // 设置滑动条的纹理
    slider->loadBarTexture("sliderTrack.png");
    // 设置滑动条的滚轮纹理
    slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
    // 设置处理滑动条的进度条纹理
    slider->loadProgressBarTexture("sliderProgress.png");
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    // 添加事件监听器
    slider->addEventListener([=](Ref* pSender,Slider::EventType type){
        // 当滑块的百分比发生变化时
        if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            // 获得滑动条百分比
            std::string value = StringUtils::format("Percent = %d",slider->getPercent());
            // 设置到TextLabel当中显示
            _displayValueLabel->setString(value);
        }
    });
    this->addChild(slider);

}

std::string SliderTest::getTitle() const
{
    return "Slider（滑动条） Test ";
}
