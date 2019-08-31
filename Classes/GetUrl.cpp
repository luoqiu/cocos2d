//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "GetUrl.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "win32-specific/icon/include/iconv.h"
#else
#include "../cocos2d/libiconv/include/iconv.h"
#endif

#include <stdlib.h>  
#include <stdio.h>  

#include <fcntl.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <stdio.h>
#include <string.h>

// extern "C"
// {
#include <pcre2/pcre2posix.h>
/*}*/
static const std::string g_head = "class=\"se-head-tabcover\"";
static size_t g_headLen = g_head.size();
static const std::string pattern = "http:((?!http:).)+\\.jpg";
static const std::regex expImg(pattern);
static const int g_urlMaxLen = 256;
static GetUrl g_instance;

GetUrl& GetUrl::GetInstance()
{
	return g_instance;
}

void GetUrl::getUrlRegex(const std::string& res, std::vector<std::string>& vUrls)
{
// 	size_t pos = res.find(g_head);
// 	if (pos == std::string::npos)
// 	{
// 		return;
// 	}
// 
// 	pos += g_headLen;
// 	std::string tmp(&res[pos]);
// 
// 	const size_t nmatch = 10;
// 	regmatch_t pm[10];
// 	int z = REG_NOERROR;
// 	regex_t reg;
// 	
// 	z = regcomp(&reg, pattern.c_str(), REG_EXTENDED | REG_NOSUB);
// 	const char *p = tmp.c_str();
// 	while (z != REG_NOMATCH)
// 	{
// 		z = regexec(&reg, p, nmatch, pm, REG_NOTBOL);
// 		if (z == REG_NOMATCH || z != REG_NOERROR)
// 			break;
// 		std::string urlTmp;
// 		urlTmp.assign(p + pm[0].rm_so, pm[0].rm_eo);
// 		vUrls.push_back(urlTmp);
// 		p += pm[0].rm_eo;
// 	}
// 
// 	regfree(&reg);
}

void GetUrl::getUrl(const std::string& res, std::vector<std::string>& vUrls)
{
	size_t pos = res.find(g_head);
	if (pos == std::string::npos)
	{
		return;
	}

	pos += g_headLen;

	std::string tmp(&res[pos]);
	std::smatch mdata;

	std::smatch::iterator it;
	std::string::const_iterator iterStart = tmp.begin();
	std::string::const_iterator iterEnd = tmp.end();

	while (std::regex_search(iterStart, iterEnd, mdata, expImg)) 
	{
		std::string urlImg(mdata[0]);
		size_t nPos = urlImg.find('\\');
		while (nPos != std::string::npos)
		{
			urlImg.replace(nPos, 1, "");
			nPos = urlImg.find('\\');
		}

		vUrls.push_back(urlImg);
		//break;
		iterStart = mdata[0].second;
	}
}

// #c---  
/*****************************************************************************
 * ��һ���ַ���Unicode(UCS-2��UCS-4)����ת����UTF-8����.
 *
 * ����:
 *    unic     �ַ���Unicode����ֵ
 *    pOutput  ָ����������ڴ洢UTF8����ֵ�Ļ�������ָ��
 *    outsize  pOutput����Ĵ�С
 *
 * ����ֵ:
 *    ����ת������ַ���UTF8������ռ���ֽ���, ��������򷵻� 0 .
 *
 * ע��:
 *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��;
 *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����;
 *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ)
 *     2. �뱣֤ pOutput �������������� 6 �ֽڵĿռ��С!
 ****************************************************************************/
int GetUrl::enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,	int outSize)
{
	assert(pOutput != NULL);
	assert(outSize >= 6);

	if (unic <= 0x0000007F)
	{
		// * U-00000000 - U-0000007F:  0xxxxxxx  
		*pOutput = (unic & 0x7F);
		return 1;
	}
	else if (unic >= 0x00000080 && unic <= 0x000007FF)
	{
		// * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx  
		*(pOutput + 1) = (unic & 0x3F) | 0x80;
		*pOutput = ((unic >> 6) & 0x1F) | 0xC0;
		return 2;
	}
	else if (unic >= 0x00000800 && unic <= 0x0000FFFF)
	{
		// * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx  
		*(pOutput + 2) = (unic & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 6) & 0x3F) | 0x80;
		*pOutput = ((unic >> 12) & 0x0F) | 0xE0;
		return 3;
	}
	else if (unic >= 0x00010000 && unic <= 0x001FFFFF)
	{
		// * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  
		*(pOutput + 3) = (unic & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 12) & 0x3F) | 0x80;
		*pOutput = ((unic >> 18) & 0x07) | 0xF0;
		return 4;
	}
	else if (unic >= 0x00200000 && unic <= 0x03FFFFFF)
	{
		// * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
		*(pOutput + 4) = (unic & 0x3F) | 0x80;
		*(pOutput + 3) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 12) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 18) & 0x3F) | 0x80;
		*pOutput = ((unic >> 24) & 0x03) | 0xF8;
		return 5;
	}
	else if (unic >= 0x04000000 && unic <= 0x7FFFFFFF)
	{
		// * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
		*(pOutput + 5) = (unic & 0x3F) | 0x80;
		*(pOutput + 4) = ((unic >> 6) & 0x3F) | 0x80;
		*(pOutput + 3) = ((unic >> 12) & 0x3F) | 0x80;
		*(pOutput + 2) = ((unic >> 18) & 0x3F) | 0x80;
		*(pOutput + 1) = ((unic >> 24) & 0x3F) | 0x80;
		*pOutput = ((unic >> 30) & 0x01) | 0xFC;
		return 6;
	}

	return 0;
}
// #c---end  
// #c---  
/*****************************************************************************
 * ��һ���ַ���UTF8����ת����Unicode(UCS-2��UCS-4)����.
 *
 * ����:
 *    pInput      ָ�����뻺����, ��UTF-8����
 *    Unic        ָ�����������, �䱣������ݼ���Unicode����ֵ,
 *                ����Ϊunsigned long .
 *
 * ����ֵ:
 *    �ɹ��򷵻ظ��ַ���UTF8������ռ�õ��ֽ���; ʧ���򷵻�0.
 *
 * ע��:
 *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��;
 *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����;
 *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ)
 ****************************************************************************/
int GetUrl::enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
	assert(pInput != NULL && Unic != NULL);

	// b1 ��ʾUTF-8�����pInput�еĸ��ֽ�, b2 ��ʾ�θ��ֽ�, ...  
	char b1, b2, b3, b4, b5, b6;

	*Unic = 0x0; // �� *Unic ��ʼ��Ϊȫ��  
	int utfbytes = enc_get_utf8_size(*pInput);
	unsigned char *pOutput = (unsigned char *)Unic;

	switch (utfbytes)
	{
	case 0:
		*pOutput = *pInput;
		utfbytes += 1;
		break;
	case 2:
		b1 = *pInput;
		b2 = *(pInput + 1);
		if ((b2 & 0xE0) != 0x80)
			return 0;
		*pOutput = (b1 << 6) + (b2 & 0x3F);
		*(pOutput + 1) = (b1 >> 2) & 0x07;
		break;
	case 3:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b2 << 6) + (b3 & 0x3F);
		*(pOutput + 1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
		break;
	case 4:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b3 << 6) + (b4 & 0x3F);
		*(pOutput + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
		*(pOutput + 2) = ((b1 << 2) & 0x1C) + ((b2 >> 4) & 0x03);
		break;
	case 5:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b4 << 6) + (b5 & 0x3F);
		*(pOutput + 1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
		*(pOutput + 2) = (b2 << 2) + ((b3 >> 4) & 0x03);
		*(pOutput + 3) = (b1 << 6);
		break;
	case 6:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		b6 = *(pInput + 5);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
			|| ((b6 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b5 << 6) + (b6 & 0x3F);
		*(pOutput + 1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
		*(pOutput + 2) = (b3 << 2) + ((b4 >> 4) & 0x03);
		*(pOutput + 3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
		break;
	default:
		return 0;
		break;
	}

	return utfbytes;
}

int GetUrl::enc_get_utf8_size(const unsigned char pInput)
{
	unsigned char c = pInput;
	// 0xxxxxxx ����0
	// 10xxxxxx ������
	// 110xxxxx ����2
	// 1110xxxx ����3
	// 11110xxx ����4
	// 111110xx ����5
	 // 1111110x ����6
	if (c < 0x80) return 0;
	if (c >= 0x80 && c < 0xC0) return -1;
	if (c >= 0xC0 && c < 0xE0) return 2;
	if (c >= 0xE0 && c < 0xF0) return 3;
	if (c >= 0xF0 && c < 0xF8) return 4;
	if (c >= 0xF8 && c < 0xFC) return 5;
	if (c >= 0xFC) return 6;
}

// #c---end 



int GetUrl::code_convert(char *from_charset, char *to_charset,const char *inbuf, size_t inlen,	char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
		return -1;
	iconv_close(cd);
	**pout = '\0';

	return 0;
}

int GetUrl::u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

int GetUrl::g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

void GetUrl::Pcre2Regex(const std::string& res, std::vector<std::string>& vUrls)
{
	int resLen = res.size();
	size_t pos = res.find(g_head);
	if (pos == std::string::npos)
	{
		pos = 0;
	}
	else
	{
		pos += g_headLen;
	}
	
	resLen -= pos;
	const size_t nmatch = 10;
	regmatch_t pm[nmatch];
	int z = 0;
	regex_t reg;
	
	z = regcomp(&reg, pattern.c_str(), 0);
	const char *p = &res[pos];
	while (resLen >0)
	{
		z = regexec(&reg, p, nmatch, pm, 0);
		if (z != 0)
			break;
		char urlTmp[g_urlMaxLen] = { 0 };

		int len = pm[0].rm_eo - pm[0].rm_so;
		if (0 < len && len <= g_urlMaxLen)
		{
			strncpy(urlTmp, p + pm[0].rm_so, len);

			std::string imgUrlStr(urlTmp);
			size_t nPos = imgUrlStr.find('\\');
			while (nPos != std::string::npos)
			{
				imgUrlStr.replace(nPos, 1, "");
				nPos = imgUrlStr.find('\\');
			}

			vUrls.push_back(imgUrlStr);
		}
		
		p += pm[0].rm_eo;
		resLen -= pm[0].rm_eo;
	}

	regfree(&reg);
}