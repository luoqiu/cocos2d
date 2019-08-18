//
//  PageViewTest.h
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#ifndef __UITest__PageViewTest__
#define __UITest__PageViewTest__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"
#include "ui/CocosGUI.h"

class PageViewTest : public BaseTest
{
protected:
    // 文本
    cocos2d::ui::Text* _displayValueLabel;
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static cocos2d::Scene* createScene();
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(PageViewTest);
    
    virtual void onEnter() override;
    
    // 标题，重写父类BaseTest的函数
    virtual std::string getTitle() const override;
};

#endif /* defined(__UITest__PageViewTest__) */
