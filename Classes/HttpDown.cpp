//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "HttpDown.h"

static HttpDown g_instance;

HttpDown& HttpDown::GetInstance()
{
	return g_instance;
}


void HttpDown::HttpGetTest(const std::string& url) 
{
	auto request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setTag("get");
	request->setResponseCallback(CC_CALLBACK_2(HttpDown::httpResponsecall, this));
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpDown::SetBackCall(ResBackCall resBackCall)
{
	_resBackCall = resBackCall;
}

void HttpDown::httpResponsecall(HttpClient* client, HttpResponse* response)
{
	if (!response)
	{
		return ;
	}
	
	// 输出响应码 200：响应成功   -1：响应失败
	long res = response->getResponseCode();
	if (res != 200)
	{
		return ;
	}

	if (!response->isSucceed())
	{
		return ;
	}
	// 获取响应的报文，督导缓冲区中
	std::vector<char>* vecRes = response->getResponseData();
	_resBackCall(vecRes);
}


