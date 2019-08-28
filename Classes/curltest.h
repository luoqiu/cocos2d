
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

		// ���ڴӷ������ϻ�ȡӦ������Ҫ�õ�������
		bool getUrlData(const char* szUrl, std::vector<char> & strContent);

		// �����ع����е����ݽ��д���
		static size_t getUrlDataCallback(uint8_t* ptrData, size_t size, size_t number, void* pData);
		static const char* _szUrl;
	};
}
#endif
