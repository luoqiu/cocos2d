//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "GetUrl.h"
#include "regex.h"
#include <stdio.h>
#include <string.h>

static const std::string g_head = "class=\"se-head-tabcover\"";
static size_t g_headLen = g_head.size();
static const std::string pattern = "http:((?!http:).)+\.jpg";
static const std::regex expImg(pattern);

static GetUrl g_instance;

GetUrl& GetUrl::GetInstance()
{
	return g_instance;
}

void GetUrl::getUrlRegex(const std::string& res, std::vector<std::string>& vUrls)
{
	size_t pos = res.find(g_head);
	if (pos == std::string::npos)
	{
		return;
	}

	pos += g_headLen;
	std::string tmp(&res[pos]);

	const size_t nmatch = 10;
	regmatch_t pm[10];
	int z = REG_NOERROR;
	regex_t reg;
	
	z = regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB);
	const char *p = tmp.c_str();
	while (z != REG_NOMATCH)
	{
		z = regexec(&reg, p, nmatch, pm, REG_NOTBOL);
		if (z == REG_NOMATCH || z != REG_NOERROR)
			break;
		std::string urlTmp;
		urlTmp.assign(p + pm[0].rm_so, pm[0].rm_eo);
		vUrls.push_back(urlTmp);
		p += pm[0].rm_eo;
	}

	regfree(&reg);
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

	while (std::regex_search(iterStart, iterEnd, mdata, expImg)) {
		std::string urlImg(mdata[0]);
		size_t nPos = urlImg.find('\\');
		while (nPos != std::string::npos)
		{
			urlImg.replace(nPos, 1, "");
			nPos = urlImg.find('\\');
		}

		vUrls.push_back(urlImg);
		iterStart = mdata[0].second;
	}
}
