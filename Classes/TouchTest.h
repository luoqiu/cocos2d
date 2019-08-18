#pragma once
#include <iostream>
#include "cocos2d.h"

class TouchTest :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(TouchTest);
protected:

};

