//
//  TextTest.h
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#ifndef __GET_URL__
#define __GET_URL__

#include <iostream>
#include <regex>
#include <external\json\internal\regex.h>

class GetUrl
{
public:
	static GetUrl& GetInstance();
	void getUrlRegex(const std::string & res, std::vector<std::string>& vUrls);
	void getUrl(const std::string& res, std::vector<std::string>& vUrls);
private:
};

#endif /* defined(__UITest__TextTest__) */
