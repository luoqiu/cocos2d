//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//
#include "HttpDown.h"

void HttpDown::HttpGetTest(const std::string& url,int urlType) 
{	
	auto request = new HttpRequest();
	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setTag("get");
	if (urlType == 0)
	{
		request->setResponseCallback(CC_CALLBACK_2(HttpDown::htmlResponsecall, this));//返回html
	}
	else
	{
		request->setResponseCallback(CC_CALLBACK_2(HttpDown::jpgResponsecall, this));//返回html
	}
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpDown::SetBackCall(int index, ResBackCall resBackCall)
{
// 	_metux.lock();
// 	_busy = true;

	_resBackCall = resBackCall;
	_index = index;
}

bool HttpDown::Isbusy()
{
	return _busy;
}

void HttpDown::htmlResponsecall(HttpClient* client, HttpResponse* response)
{
	if (!response)
	{
// 		_busy = false;
// 		_metux.unlock();

		return ;
	}
	
	// 输出响应码 200：响应成功   -1：响应失败S
	long res = response->getResponseCode();
	if (res != 200)
	{
// 		_busy = false;
// 		_metux.unlock();

		return;
	}

	if (!response->isSucceed())
	{
// 		_busy = false;
// 		_metux.unlock();

		return ;
	}


	// 获取响应的报文，督导缓冲区中
	std::vector<char>* vecRes = response->getResponseData();

//	_resBackCall(vecRes, _index);

// 	_busy = false;
// 	_metux.unlock();
}



void HttpDown::jpgResponsecall(HttpClient* client, HttpResponse* response)
{
	if (!response)
	{
		// 		_busy = false;
		// 		_metux.unlock();

		return;
	}

	// 输出响应码 200：响应成功   -1：响应失败S
	long res = response->getResponseCode();
	if (res != 200)
	{
		// 		_busy = false;
		// 		_metux.unlock();

		return;
	}

	if (!response->isSucceed())
	{
		// 		_busy = false;
		// 		_metux.unlock();

		return;
	}


	// 获取响应的报文，督导缓冲区中
	std::vector<char>* vecRes = response->getResponseData();

	//_resBackCall(vecRes, _index);

	// 	_busy = false;
	// 	_metux.unlock();
}


