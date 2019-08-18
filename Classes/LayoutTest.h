//
//  LayoutTest.h
//  UITest
//
//  Created by apple on 14-9-7.
//
//

#ifndef __UITest__LayoutTest__
#define __UITest__LayoutTest__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"

class LayoutTest : public BaseTest
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
    CREATE_FUNC(LayoutTest);
    
    virtual void onEnter() override;
    
    // ���⣬��д����BaseTest�ĺ���
    virtual std::string getTitle() const override;
};



#endif /* defined(__UITest__LayoutTest__) */
