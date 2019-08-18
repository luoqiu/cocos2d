//
//  TextTest.cpp
//  UITest
//
//  Created by apple on 14-8-31.
//
//

#include "GetUrl.h"

static const std::string g_head = "class=\"se-head-tabcover\"";
static size_t g_headLen = g_head.size();
static const std::regex expImg("http((?!jpg).)*\.(jpg|JPG)");

static GetUrl g_instance;

GetUrl& GetUrl::GetInstance()
{
	return g_instance;
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
	try
	{
		while (std::regex_search(iterStart, iterEnd, mdata, expImg)) {
			std::string urlImg(mdata[0]);
			size_t nPos = urlImg.find('\\');
			while (nPos != std::string::npos)
			{
				urlImg.replace(nPos, 1, "");
				nPos = urlImg.find('\\');
			}

			vUrls.push_back(urlImg);
			tmp = &*mdata[0].second;

			pos = tmp.find("http");
			if (pos == std::string::npos)
			{
				return;
			}

			tmp = tmp.substr(pos, tmp.size());
			iterStart = tmp.begin();
			iterEnd = tmp.end();
		}
	}
	catch (...)
	{
		
	}
}
