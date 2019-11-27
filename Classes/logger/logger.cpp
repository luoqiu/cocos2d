#include "logger/logger.h"

using namespace cocos2d;

void Logger::ShowLog(const std::string &log)
{
	valuelog = StringUtils::format("%s %s %d %s", __FILE__, __FUNCTION__, __LINE__, log.c_str());
	

	auto scence = Scene::create();
	auto layer = Logger::create();
	scence->addChild(layer);
	Director::getInstance()->replaceScene(scence);
}

Logger & Logger::getInstance()
{
	// TODO: 在此处插入 return 语句
	static Logger log;
	return log;
}

bool Logger::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	CCTexture2D* texture = new CCTexture2D();
	
	texture->initWithString(valuelog.c_str(), "", 15);
	auto sprit = Sprite::createWithTexture(texture);
	sprit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(sprit,5);
	return true;
}
