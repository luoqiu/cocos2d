//
//  ListViewTest.h
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#ifndef __GRADE__LAYER__
#define __GRADE__LAYER__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"
#include "ui/CocosGUI.h"

#include <vector>

class GradeLayer : public BaseTest
{
protected:
    // 文本
    cocos2d::ui::Text* _displayValueLabel;
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static cocos2d::Scene* createScene(const std::string& subject);
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(GradeLayer);
	virtual bool init() override;
    virtual void onEnter() override;
private:
	std::vector<std::string> _vecGrade;
	static std::string _subject;
	std::string _grade;
};



#endif /* defined(__UITest__ListViewTest__) */
