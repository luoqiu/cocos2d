//
//  BaseDemo.h
//  PhysicsTest
//
//  Created by Jason on 14-3-9.
//
//

#ifndef __UITest__BaseTest__
#define __UITest__BaseTest__

#include "cocos2d.h"
USING_NS_CC;

class BaseTest : public cocos2d::Layer
{
public:
    
    // init函数完成功能： 1.显示标题功能 2.返回菜单选择场景功能
    virtual bool init();
    
    // 显示标题，该函数应该由子类重写
    virtual std::string getTitle() const;
    
    // 返回菜单
    virtual void backCallback(Ref* pSender);
    
};


#endif /* defined(__UITest__BaseTest__) */
