#ifndef _DBMANAGER_
#define _DBMANAGER_

#include "../../dependencies/sqlite/sqlite3.h"

class DBManager {
private:
	sqlite3* db;

public:
	DBManager();
	DBManager(char* dbName);
	~DBManager();

	bool verifyUser(char* username, char* password);
	void addNewUser(char* username, char* password);
	void updateUserWin(char* userId);
	void updateUserLose(char* userId);
	bool userExists(char* username);
	
};

#endif // !_DBMANAGER_
