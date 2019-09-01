//
//  BaseDemo.h
//  PhysicsTest
//
//  Created by Jason on 14-3-9.
//
//

#ifndef __UITest__BaseTest__
#define __UITest__BaseTest__
#include "logger/logger.h"
#include "cocos2d.h"
USING_NS_CC;
#define BT_WIDE 70
#define BT_HEIGHT 30

class BaseTest : public cocos2d::Layer
{
public:
    
    // init������ɹ��ܣ� 1.��ʾ���⹦�� 2.���ز˵�ѡ�񳡾�����
    virtual bool init();
    
    // ��ʾ���⣬�ú���Ӧ����������д
    virtual std::string getTitle() const;
    
    // ���ز˵�
    virtual void backCallback(Ref* pSender);

	void addLog(const std::string& logTmp);
    
};


#endif /* defined(__UITest__BaseTest__) */
