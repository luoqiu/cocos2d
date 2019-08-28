
// Downloader.h 

#ifndef FILE_DOWNLOADER_H
#define FILE_DOWNLOADER_H
#pragma once
#include <cocos2d.h>

namespace cocos2d
{
	class CDownloader
	{
	public:
		CDownloader(void);

		~CDownloader(void);

		// 用于从服务器上获取应用中需要用到的数据
		bool getUrlData(const char* szUrl, std::vector<char> & strContent);

		// 对下载过程中的数据进行处理
		static size_t getUrlDataCallback(uint8_t* ptrData, size_t size, size_t number, void* pData);
		static const char* _szUrl;
	};
}
#endif
