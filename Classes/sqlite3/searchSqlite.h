
#ifndef __SEARCH_SQILTE__
#define __SEARCH_SQILTE__

#include <iostream>
#include <mutex>
#include <vector>

class SearchSqlite
{
public:
	static SearchSqlite & GetInstance();
	void SearchValue(const std::vector<int>& vecIndex, const std::string& table, std::vector<std::string>& vecValue);
private:
	std::mutex _mutex;
};

#endif /* defined(__UITest__TextTest__) */
