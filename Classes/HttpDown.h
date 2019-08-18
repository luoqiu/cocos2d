//
//  TextTest.h
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#ifndef __HTTP_DOWN__
#define __HTTP_DOWN__

#include <iostream>
#include "cocos2d.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
USING_NS_CC;

using namespace network;

typedef std::function<void(std::vector<char>*)> ResBackCall;

typedef 
class HttpDown
{
public:
	static HttpDown& GetInstance();
	void HttpGetTest(const std::string& url);
	void SetBackCall(ResBackCall resBackCall);
private:
	void httpResponsecall(HttpClient* client, HttpResponse* response);
	ResBackCall _resBackCall;

};

#endif /* defined(__UITest__TextTest__) */
