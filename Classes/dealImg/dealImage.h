
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
		unsigned int index;//vecUrl中下标访问jpg
		std::string word;
		std::vector<std::string> vecUrl;
		_IndexVec() :index(0) {};
	}IndexVec;

public:
	void AddThread();//创建线程下载数据
	static imageDeal& GetInstance();
	void AddTask(const std::vector<std::string>& vecWords);
private:
	void run();
	void TryDownImg(int index);
private:
	std::mutex _mutex;
	std::queue<std::string> _queWords;//待下载的单词img
	std::string _currentWord;	//当前下载img的单词
	std::map<int, IndexVec> _mUrls;
};

#endif /* defined(__UITest__TextTest__) */
