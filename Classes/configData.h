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
#include <set>
#include "HttpDown.h"

typedef std::shared_ptr<HttpDown> HTTPDOWNPTR;

class EnglishClass : public BaseTest
{
	typedef struct _IndexVec
	{
		unsigned int index;//vecUrl���±����jpg
		std::vector<std::string> vecUrl;
		_IndexVec() :index(0) {};
	}IndexVec;
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
	void callBackImg(std::vector<char>* pRes, int index);
	void RetryDownImg(int index);
	void callBackHtml(std::vector<char>* pRes, int index);//�ص�������Ӧ��html��ҳ
	void ThreadDownImg(int index, const std::string & words);
	void DownWordPicture();
	void LoadImg();
	void onEnterContent();
	virtual void onEnter() override;
	virtual void update(float delta) override;
	//virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
	CREATE_FUNC(EnglishClass);
private:
	std::string _stage;
	std::string _sGrade;
	std::string _index;
	std::string _wordsOnce;	//ÿ��ѡ����ϰ������
	std::vector<int> _vecSerialumber;
	std::vector<std::string> _vecWords;
	std::vector<std::string> _vecGrade;
	bool _bGradeFlag;		//
	int _indexWord;
	std::vector<HTTPDOWNPTR> _vecHttpDown;
	std::map<int, IndexVec> _mUrls;
	std::mutex _mutex;

};

#endif /* defined(__UITest__TextTest__) */
