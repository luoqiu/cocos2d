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
	// �ı�
public:
	/**
	 * ��̬����������Scene����
	 * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
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
	std::string _wordsOnce;	//ÿ��ѡ����ϰ������
	std::vector<int> _vecSerialumber;
	std::vector<std::string> _vecWords;
	std::vector<std::string> _vecGrade;
	bool _bGradeFlag;		//
};

#endif /* defined(__UITest__TextTest__) */
