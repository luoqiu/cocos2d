//
//  ContentLayer.h
//  TouchOneByOneTest
//
//  Created by Jason on 14-3-9.
//
//

#ifndef __PhysicsTest__ContentLayer__
#define __PhysicsTest__ContentLayer__

#include "cocos2d.h"

USING_NS_CC;

class ContentLayer : public cocos2d::Layer
{
protected:
    // 记录滑动的开始坐标
    Vec2 _beginPos;
    // 菜单
    Menu* _itemMenu;
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static Scene* createScene();
    /**
     * init函数，完成初始化操作。
     * 注意：init函数在Cocos2d-x中返回bool值，而不是返回Cocos2d-iPhone中的“id”
     */
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(ContentLayer);
    
    // 点击每一个菜单项时的回调函数
    void menuCallback(Ref * sender);
    
    // 触碰事件回调函数
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);

};

#endif /* defined(__TouchOneByOneTest__ContentLayer__) */
