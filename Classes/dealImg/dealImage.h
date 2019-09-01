
#ifndef __IMAGE_DEAL__
#define __IMAGE_DEAL__

#include <iostream>
#include "cocos2d.h"
#include <queue>
#include <map>

USING_NS_CC;

class imageDeal
{
	typedef struct _IndexVec
	{
		unsigned int index;//vecUrl���±����jpg
		std::string word;
		std::vector<std::string> vecUrl;
		_IndexVec() :index(0) {};
	}IndexVec;

public:
	void AddThread();//�����߳���������
	static imageDeal& GetInstance();
	void AddTask(const std::vector<std::string>& vecWords);
private:
	void run();
	void TryDownImg(int index);
private:
	std::mutex _mutex;
	std::queue<std::string> _queWords;//�����صĵ���img
	std::string _currentWord;	//��ǰ����img�ĵ���
	std::map<int, IndexVec> _mUrls;
};

#endif /* defined(__UITest__TextTest__) */
