//
//  TextTest.h
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#ifndef __CONFIG_DATA__
#define __CONFIG_DATA__

#include "BaseTest.h"
#include <iostream>
#include <vector>

class EnglishClass : public BaseTest
{
protected:
	// 文本
public:
	/**
	 * 静态函数，创建Scene场景
	 * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”,建议返回类实例的指针
	 */
	static cocos2d::Scene* createScene();
	void GetValueForKey(const std::string & key, std::string & value, const std::string & defaultValue);
	void GetVec(std::string & index, std::vector<int>& vec);
	virtual bool init();
	void onEnterGrade();
	void onEnterContent();
	virtual void onEnter() override;

private:
	std::string _stage;
	std::string _sGrade;
	std::string _index;
	std::string _wordsOnce;	//每次选择练习单词数
	std::vector<int> _vecSerialumber;
	std::vector<std::string> _vecWords;
	std::vector<std::string> _vecGrade;
	bool _bGradeFlag;		//
};

#endif /* defined(__UITest__TextTest__) */
