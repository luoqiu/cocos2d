#include "searchSqlite.h"
#include "cocos2d.h"
#include "GetUrl.h"
#include "logger/logger.h"
extern "C"
{
#include "sqlite3/sqlite3.h"
}
USING_NS_CC;
static SearchSqlite g_instance;

SearchSqlite& SearchSqlite::GetInstance()
{
	return g_instance;
}

static int callback(void *data, int argc, char **argv, char **azColName) 
{
	int i;
	std::vector<std::string>* vecValue = (std::vector<std::string>*)data;

	for (i = 0; i < argc; i++) 
	{
		if (argv[i])
		{
			char value[64] = {0}, gbValue[64] = { 0 };
			GetUrl::GetInstance().u2g(argv[i], strlen(argv[i]), value, sizeof(value));
			//GetUrl::GetInstance().u2g(value, 64, gbValue, 64);
			vecValue->push_back(value);
		}
	}

	std::string num = StringUtils::format("argc:%d", argc);
	//Logger::getInstance().ShowLog(num);

	return 0;
}

void SearchSqlite::SearchValue(const std::vector<int>& vecIndex, const std::string& table, std::vector<std::string>& vecValue)
{
	_mutex.lock();

	std::string dbPath = FileUtils::getInstance()->getWritablePath()+"/demo.db";

	if (!FileUtils::getInstance()->isFileExist(dbPath))
	{
		auto data = FileUtils::getInstance()->getDataFromFile("demo.db");
		if (!FileUtils::getInstance()->writeDataToFile(data, dbPath))
		{
			std::string num = StringUtils::format("getInstance()->writeDataToFile(data, dbPath):");
			//Logger::getInstance().ShowLog(num);
			return;
		}		
	}

	sqlite3 *db;
	int rc = sqlite3_open(dbPath.c_str(), &db);

	if (rc)
	{
		log("Can't open database: %s\n", sqlite3_errmsg(db));
		//Logger::getInstance().ShowLog("open db failed");
		_mutex.unlock();
		return ;
	}
	static char sql[256];
	static char sqlUTF8[256 * 6];
	for (int i = 0; i < vecIndex.size(); ++i)
	{
		//std::string sql = StringUtils::format("select * from %s where rowid=%d;", table.c_str(), vecIndex[i]);

		sprintf(sql, "select * from %s where rowid=%d;", table.c_str(), vecIndex[i]);
		int sqlLen = strlen(sql);
		int uft8Len = sizeof(sqlUTF8);
		
		GetUrl::GetInstance().g2u(sql, sqlLen, sqlUTF8, uft8Len);
		
		char *zErrMsg = NULL;
		rc = sqlite3_exec(db, sqlUTF8, callback, (void*)&vecValue, &zErrMsg);

		if (rc != SQLITE_OK) {
			log("SQL error: %s\n", zErrMsg);
			//Logger::getInstance().ShowLog("SQL error:");
			sqlite3_free(zErrMsg);
		}
		else {
			log("Operation done successfully\n");
		}
	}	

	sqlite3_close(db);
	_mutex.unlock();
}
