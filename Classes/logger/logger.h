
#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Logger:public Layer
{
public:
	void ShowLog(const std::string & );
	static Logger&getInstance();
	CREATE_FUNC(Logger);
	virtual bool init() override;
private:
	std::string valuelog;
};

#endif /* defined(__UITest__TextTest__) */
