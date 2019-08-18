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
    
    // init������ɹ��ܣ� 1.��ʾ���⹦�� 2.���ز˵�ѡ�񳡾�����
    virtual bool init();
    
    // ��ʾ���⣬�ú���Ӧ����������д
    virtual std::string getTitle() const;
    
    // ���ز˵�
    virtual void backCallback(Ref* pSender);
    
};


#endif /* defined(__UITest__BaseTest__) */
