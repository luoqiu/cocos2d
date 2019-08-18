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
    // �ı�
    cocos2d::ui::Text* _displayValueLabel;
public:
    /**
     * ��̬����������Scene����
     * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
     */
    static cocos2d::Scene* createScene();
    
    /**
     * ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
     */
    CREATE_FUNC(PageViewTest);
    
    virtual void onEnter() override;
    
    // ���⣬��д����BaseTest�ĺ���
    virtual std::string getTitle() const override;
};

#endif /* defined(__UITest__PageViewTest__) */
