//
//  ScrollViewTest.h
//  UITest
//
//  Created by apple on 14-9-6.
//
//

#ifndef __UITest__ScrollViewTest__
#define __UITest__ScrollViewTest__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"

class ScrollViewTest : public BaseTest
{
public:
    /**
     * ��̬����������Scene����
     * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
     */
    static cocos2d::Scene* createScene();
    
    /**
     * ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
     */
    CREATE_FUNC(ScrollViewTest);
    
    virtual void onEnter() override;
    
    // ���⣬��д����BaseTest�ĺ���
    virtual std::string getTitle() const override;
};

#endif /* defined(__UITest__ScrollViewTest__) */
