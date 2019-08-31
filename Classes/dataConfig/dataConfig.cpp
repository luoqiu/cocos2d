#include "dataConfig.h"
#include <ui/CocosGUI.h>

using namespace cocos2d;
DataConfig & DataConfig::getInstance()
{
	// TODO: �ڴ˴����� return ���
	static DataConfig dataConfig;
	return dataConfig;
}



void DataConfig::GetValueForKey(const std::string& key, std::string& value, const std::string& defaultValue)
{
	value = UserDefault::getInstance()->getStringForKey(key.c_str());
	if (value.empty())
	{
		value = defaultValue;
		UserDefault::getInstance()->setStringForKey("stage", defaultValue);
		UserDefault::getInstance()->flush();
	}
}

void DataConfig::GetVec(const std::string& index, const  std::string& wordsOnce, std::vector<int>& vec)
{
	vec.clear();
	for (int i = atoi(index.c_str()); i < atoi(wordsOnce.c_str()); ++i)
	{
		vec.push_back(i);
	}
}