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
	int enc_unicode_to_utf8_one(unsigned long unic, unsigned char * pOutput, int outSize);
	int enc_utf8_to_unicode_one(const unsigned char * pInput, unsigned long * Unic);
	int enc_get_utf8_size(const unsigned char pInput);
	int code_convert(char * from_charset, char * to_charset, const char * inbuf, size_t inlen, char * outbuf, size_t outlen);
	int u2g(char * inbuf, size_t inlen, char * outbuf, size_t outlen);
	int g2u(char * inbuf, size_t inlen, char * outbuf, size_t outlen);
private:
};

#endif /* defined(__UITest__TextTest__) */
