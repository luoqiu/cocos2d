#include "searchSqlite.h"
#include "cocos2d.h"
extern "C"
{
#include "sqlite3.h"
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
		//log("%d = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		if (argv[i])
		{
			vecValue->push_back(argv[i]);
		}
	}

	return 0;
}

bool SearchSqlite::OpenDB(const std::string & dbPath)
{
// 	sqlite3 *db;
// 	int rc = sqlite3_open(dbPath.c_str(), &db);
// 
// 	if (rc)
// 	{
// 		log("Can't open database: %s\n", sqlite3_errmsg(db));
// 		return false;
// 	}
// 	
// 	sqlite3_close(db);
// 
 	return true;
}

void SearchSqlite::SearchValue(const std::vector<int>& vecIndex, const std::string& table, std::vector<std::string>& vecValue)
{
	_mutex.lock();
	sqlite3 *db;
	int rc = sqlite3_open("demo.db", &db);

	if (rc)
	{
		log("Can't open database: %s\n", sqlite3_errmsg(db));
		_mutex.unlock();
		return ;
	}
	static char sql[256];
	for (int i = 0;i < vecIndex.size(); ++i)
	{
		sprintf(sql, "select * from %s where rowid=%d;", table.c_str(), vecIndex[i]);
		//sprintf(sql, "select * from sqlite_master where type=\"table\";");
		
		char *zErrMsg = NULL;
		rc = sqlite3_exec(db, sql, callback, (void*)&vecValue, &zErrMsg);

		if (rc != SQLITE_OK) {
			log("SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			log("Operation done successfully\n");
		}
	}	

	sqlite3_close(db);
	_mutex.unlock();
}
