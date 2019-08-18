//
//  ButtonTest.h
//  UITest
//
//  Created by apple on 14-8-27.
//
//

#ifndef __UITest__ButtonTest__
#define __UITest__ButtonTest__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"

class ButtonTest : public BaseTest
{
protected:
    cocos2d::Label* message;
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static cocos2d::Scene* createScene();
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(ButtonTest);
    
    virtual void onEnter() override;
    
    // 标题，重写父类BaseTest的函数
    virtual std::string getTitle() const override;
};

#endif /* defined(__UITest__ButtonTest__) */
