//
//  ListViewTest.h
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#ifndef __UITest__ListViewTest__
#define __UITest__ListViewTest__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"
#include "ui/CocosGUI.h"

class ListViewTest : public BaseTest
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
    CREATE_FUNC(ListViewTest);
    
    virtual void onEnter() override;
    
    // 标题，重写父类BaseTest的函数
    virtual std::string getTitle() const override;
	bool ShowImage(std::string& p);
	void ShowResImg(std::vector<char>* p);
	void GetImgRes();
	void GetRes(std::vector<char>* p);
	void ShowError(const std::string& error);
	bool ShowLocalImage(std::string & p);
	void onHttpRequestCompleted(cocos2d::CCNode *sender, void *data);
	void onMenuGetTestClicked(cocos2d::CCObject *sender);

private:
	std::vector<std::string> vUrls;
	size_t index;
	std::string sFileName;
};



#endif /* defined(__UITest__ListViewTest__) */
