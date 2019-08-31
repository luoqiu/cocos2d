//
//  ListViewTest.cpp
//  UITest
//
//  Created by apple on 14-9-5.
//
//
//#include "ContentLayer.h"
#include "contentLayer.h"

 std::string ContentLayer::_grade;

cocos2d::Scene * ContentLayer::createScene(const std::string& grade)
{
	_grade = grade;
	auto scence = Scene::create();
	auto layer = ContentLayer::create();
	scence->addChild(layer);
	return scence;
}

void ContentLayer::onEnter()
{
	Layer::onEnter();
}
