//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "GetUrl.h"
#include <external/win32-specific/icon/include/iconv.h>  
#include <stdlib.h>  
#include <stdio.h>  

#include <fcntl.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <stdio.h>
#include <string.h>
#include "pcre/pcre2.h"
extern "C"
{
//#include "regex/regex.h"
// 	extern int regcomp(regex_t *preg, const char *pattern, int cflags);
// 	extern int	regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags);
// 	extern void	regfree(regex_t *preg);
}
static const std::string g_head = "class=\"se-head-tabcover\"";
static size_t g_headLen = g_head.size();
static const std::string pattern = "http:((?!http:).)+\\.jpg";
static const std::regex expImg(pattern);

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
		break;
		iterStart = mdata[0].second;
	}
}

// #c---  
/*****************************************************************************
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
 *
 * 参数:
 *    unic     字符的Unicode编码值
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
 *    outsize  pOutput缓冲的大小
 *
 * 返回值:
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
 *
 * 注意:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
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
 * 将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码.
 *
 * 参数:
 *    pInput      指向输入缓冲区, 以UTF-8编码
 *    Unic        指向输出缓冲区, 其保存的数据即是Unicode编码值,
 *                类型为unsigned long .
 *
 * 返回值:
 *    成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0.
 *
 * 注意:
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
 ****************************************************************************/
int GetUrl::enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic)
{
	assert(pInput != NULL && Unic != NULL);

	// b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...  
	char b1, b2, b3, b4, b5, b6;

	*Unic = 0x0; // 把 *Unic 初始化为全零  
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
	// 0xxxxxxx 返回0
	// 10xxxxxx 不存在
	// 110xxxxx 返回2
	// 1110xxxx 返回3
	// 11110xxx 返回4
	// 111110xx 返回5
	 // 1111110x 返回6
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

void GetUrl::PcreRegex(const std::string& res, std::vector<std::string>& vUrls)
{
// #define OVECCOUNT 30 // should be a multiple of 3 
// 	PCRE2_SPTR8;
// 	pcre  *re;
// 	const char *error;
// 	int  erroffset;
// 	int  ovector[OVECCOUNT];
// 	pcre2_compile();
	
}

/*
#define PCRE_STATIC // 静态库编译选项
#include <stdio.h>
#include <string.h>
#include <pcre.h>
#define OVECCOUNT 30 // should be a multiple of 3 
#define EBUFLEN 128
#define BUFLEN 1024

int main()
{
	pcre  *re;
	const char *error;
	int  erroffset;
	int  ovector[OVECCOUNT];
	int  rc, i;
	char  src[] = "111 <title>Hello World</title> 222";   // 要被用来匹配的字符串
	char  pattern[] = "<title>(.*)</(tit)le>";              // 将要被编译的字符串形式的正则表达式
	printf("String : %s/n", src);
	printf("Pattern: /"%s / "/n", pattern);
	re = pcre_compile(pattern,       // pattern, 输入参数，将要被编译的字符串形式的正则表达式
		0,            // options, 输入参数，用来指定编译时的一些选项
		&error,       // errptr, 输出参数，用来输出错误信息
		&erroffset,   // erroffset, 输出参数，pattern中出错位置的偏移量
		NULL);        // tableptr, 输入参数，用来指定字符表，一般情况用NULL
// 返回值：被编译好的正则表达式的pcre内部表示结构
	if (re == NULL) {                 //如果编译失败，返回错误信息
		printf("PCRE compilation failed at offset %d: %s/n", erroffset, error);
		return 1;
	}
	rc = pcre_exec(re,            // code, 输入参数，用pcre_compile编译好的正则表达结构的指针
		NULL,          // extra, 输入参数，用来向pcre_exec传一些额外的数据信息的结构的指针
		src,           // subject, 输入参数，要被用来匹配的字符串
		strlen(src),  // length, 输入参数， 要被用来匹配的字符串的指针
		0,             // startoffset, 输入参数，用来指定subject从什么位置开始被匹配的偏移量
		0,             // options, 输入参数， 用来指定匹配过程中的一些选项
		ovector,       // ovector, 输出参数，用来返回匹配位置偏移量的数组
		OVECCOUNT);    // ovecsize, 输入参数， 用来返回匹配位置偏移量的数组的最大大小
// 返回值：匹配成功返回非负数，没有匹配返回负数
	if (rc < 0) {                     //如果没有匹配，返回错误信息
		if (rc == PCRE_ERROR_NOMATCH) printf("Sorry, no match .../n");
		else printf("Matching error %d/n", rc);
		pcre_free(re);
		return 1;
	}
	printf("/nOK, has matched .../n/n");   //没有出错，已经匹配
	for (i = 0; i < rc; i++) {             //分别取出捕获分组 $0整个正则公式 $1第一个()
		char *substring_start = src + ovector[2 * i];
		int substring_length = ovector[2 * i + 1] - ovector[2 * i];
		printf("$%2d: %.*s/n", i, substring_length, substring_start);
	}
	pcre_free(re);                     // 编译正则表达式re 释放内存
	return 0;
}




*/