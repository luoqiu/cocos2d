#include "dataConfig.h"
#include <ui/CocosGUI.h>

using namespace cocos2d;
DataConfig & DataConfig::getInstance()
{
	// TODO: 在此处插入 return 语句
	static DataConfig dataConfig;
	return dataConfig;
}



void DataConfig::GetValueForKey(const std::string& key, std::string& value, const std::string& defaultValue)
{
	value = UserDefault::getInstance()->getStringForKey(key.c_str());
	if (value.empty())
	{
		value = defaultValue;
		UserDefault::getInstance()->setStringForKey(key.c_str(), defaultValue);
		UserDefault::getInstance()->flush();
	}
}

void DataConfig::GetVec(int index, int wordsOnce, std::vector<int>& vec)
{
	vec.clear();
	for (int i = index ; i < index+ wordsOnce; ++i)
	{
		vec.push_back(i);
	}
}