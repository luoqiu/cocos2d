//
//  ImageViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#include "ImageViewTest.h"
#include "ContentLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* ImageViewTest::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = ImageViewTest::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}


void ImageViewTest::onEnter()
{
    Layer::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 添加背景
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background);

    // 创建一个ImageView
    auto imageView = ImageView::create("ccicon.png");
    imageView->setScale(2);
    imageView->setPosition(Vec2(visibleSize.width / 2,
                                visibleSize.height / 2));
    this->addChild(imageView);

}

std::string ImageViewTest::getTitle() const
{
    return "ImageView（图片） Test ";
}
