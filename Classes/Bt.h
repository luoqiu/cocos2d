#pragma once
#include <iostream>
#include "cocos2d.h"

class Bt :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter() override;
	void menuCallback(cocos2d::Ref* pSender);
	void menuBtCallback(Ref * sender);
	virtual std::string getTitle() const;
	CREATE_FUNC(Bt);
protected:
	cocos2d::Label* message;
};

