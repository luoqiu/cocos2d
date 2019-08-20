
#ifndef __SEARCH_SQILTE__
#define __IMAGE__SEARCH_SQILTE___DEAL__

#include <iostream>
#include <mutex>
#include <vector>
#include "sqlite3.h"


class SearchSqlite
{
public:
	SearchSqlite & GetInstance();
	bool OpenDB(const std::string& dbPath);
	void SearchValue(const std::vector<int>& vecIndex, const std::string& table, std::vector<std::string>& vecValue);
private:
	std::mutex _mutex;
};

#endif /* defined(__UITest__TextTest__) */
