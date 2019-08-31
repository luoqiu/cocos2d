//
//  TextTest.h
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#ifndef __DATA_CONFIG__
#define __DATA_CONFIG__

#include <cocos2d.h>


class DataConfig 
{
public:
	static DataConfig& getInstance();

	void GetValueForKey(const std::string & key, std::string & value, const std::string & defaultValue);

	void GetVec(int index, int wordsOnce, std::vector<int>& vec);


};

#endif /* defined(__UITest__TextTest__) */
