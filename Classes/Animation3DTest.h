#pragma once
#include <iostream>
#include "cocos2d.h"

class Animation3DTest :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void reachEndCallBack();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCallback(Ref* pSender);
	void newMenu();
	void menuPrintCallback();
		// 点击MenuItemToggle菜单项的回调函数
		void menuItemToggle(Ref* pSender);
	CREATE_FUNC(Animation3DTest);
protected:
	cocos2d::Sprite3D* _sprite;
	cocos2d::MoveTo* _moveAction;
	cocos2d::Animate3D* _swim;
};

