//
//  ListViewTest.h
//  UITest
//
//  Created by apple on 14-9-5.
//
//

#ifndef __CONTENT_LAYER__
#define __CONTENT_LAYER__

#include <iostream>
#include "cocos2d.h"
#include "BaseTest.h"
#include "ui/CocosGUI.h"

class ContentLayer : public BaseTest
{
protected:
    // 文本
    cocos2d::ui::Text* _displayValueLabel;
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
     */
    static cocos2d::Scene* createScene(const std::string& grade);
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(ContentLayer);
    
	void wordVoice();

	void onEnterContent();

	virtual void onEnter() override;
	virtual bool init() override;
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
private:
	static std::string _grade;
	int _gradeWordIndex;
	int _wordsOnce;
	int _vecWordIndex;
	std::vector<std::string> _vecWords;

	CCImage _wordImg;
	CCTexture2D _textureImg;
	CCTexture2D _textureTitle;
};



#endif /* defined(__UITest__ListViewTest__) */
