#include <iostream>
#include "../../dependencies/sqlite/sqlite3.h"

#include <string.h>

#include "dbManager.h"
#include "idGenerator.h"

using namespace std;

DBManager::DBManager(char* dbName) {
    sqlite3_open(dbName, &this->db);

    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(id VARCHAR(36) PRIMARY KEY NOT NULL, name VARCHAR(100) UNIQUE NOT NULL, pass VARCHAR(100) NOT NULL, elo INT DEFAULT 800);", NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        cout << "F bro: " << err;
    }
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS history(id VARCHAR(36) PRIMARY KEY NOT NULL, id_whitePlayer VARCHAR(36) NOT NULL,"
        "id_blackPlayer VARCHAR(36) NOT NULL, winner INT, CHECK (winner=0 OR winner=1 OR winner=2),"
        "FOREIGN KEY(id_whitePlayer) REFERENCES user(id),FOREIGN KEY(id_blackPlayer) REFERENCES user(id)); ", NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "F bro en tabla history: " << err;
    }
}

DBManager::~DBManager() {
    sqlite3_close(this->db);
}

bool DBManager::verifyUser(char* username, char* password) {
    sqlite3_stmt* stmt;
    sqlite3_stmt* stmt;
    char* err;

    char* sql1 = "select user_id from user where username = ? and pass = ?;"; // Sentencia SQL

    int rc = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 1 ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC); // Introducir username
    if (rc != SQLITE_OK) std::cout << "BIND 1 ERROR" << std::endl;
    rc = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC); // Introducir password
    if (rc != SQLITE_OK) std::cout << "BIND 2 ERROR" << std::endl;

    rc = sqlite3_step(stmt); // Ejecutar query
    sqlite3_finalize(stmt);
    return rc == SQLITE_ROW;
}
void DBManager::addNewUser(char* username, char* password) {
    sqlite3_stmt* stmt;
    char* err;
    
    string query = "insert into user VALUES (" + generateUUID() + " , " + username + " , " + password + " , " + ", 800);";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        cout << "ERROR EN INSERT: " << err;
    }
   
}
bool DBManager::userExists(char* username) {
    sqlite3_stmt* stmt;
    char* err;
    sqlite3_prepare_v2(db, "select name from user;", -1, &stmt, 0);
    bool noNameFound = true;
    while (sqlite3_step(stmt) != SQLITE_NULL && noNameFound == true) {
        char* name = (char*)sqlite3_column_text(stmt, 0);
        if (strcmp(username, name) == 0) {
            return true;
        }
    }
    return false;
}
void DBManager::updateUserWin(char* userName) {
    sqlite3_stmt* stmt;
    char* err;
    int rc;
    char* queri = "update user set elo = elo + 8 where name = ?";

    rc = sqlite3_prepare_v2(db, queri, strlen(queri) + 1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 3 ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt, 1, userName, strlen(userName), SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 6 ERROR" << std::endl;
    sqlite3_step(stmt);
    
}
void DBManager::updateUserLose(char* userName) {
    sqlite3_stmt* stmt;
    char* err;
    int rc;
    char* queri = "update user set elo = elo - 8 where name = ?";

    rc = sqlite3_prepare_v2(db, queri, strlen(queri) + 1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 3 ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt, 1, userName, strlen(userName), SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 6 ERROR" << std::endl;
    sqlite3_step(stmt);
}


/*
const unsigned char* getUserId(sqlite3* db, sqlite3_stmt* stmt, const char name);
const unsigned char* getUserName(sqlite3* db, sqlite3_stmt* stmt, const char id);
const unsigned char* getUserPass(sqlite3* db, sqlite3_stmt* stmt, const char name);
const unsigned char* getUserElo(sqlite3* db, sqlite3_stmt* stmt, const char name);

int main()
{
    char* err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("myDB.db", &db);
    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(id VARCHAR(36) PRIMARY KEY NOT NULL, name VARCHAR(100) UNIQUE NOT NULL, pass VARCHAR(100) NOT NULL, elo INT DEFAULT 800);", NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        cout << "F bro: " << err;
    }
    else
        cout << "TODO OK" << endl;

    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS history(id VARCHAR(36) PRIMARY KEY NOT NULL, id_whitePlayer VARCHAR(36) NOT NULL,"
        "id_blackPlayer VARCHAR(36) NOT NULL, winner INT, CHECK (winner=0 OR winner=1 OR winner=2),"
        "FOREIGN KEY(id_whitePlayer) REFERENCES user(id),FOREIGN KEY(id_blackPlayer) REFERENCES user(id)); ", NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "F bro en tabla history: " << err;
    }
    else
        cout << "TODO OK" << endl;


    // string query = "insert into user VALUES ('4324dsdsds123123', 'DelFox', 'awa', 800);";
    //cout << query << "\n";
    //  rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);

    if (rc != SQLITE_OK) {
        cout << "ERROR EN INSERT: " << err;
    }
    sqlite3_prepare_v2(db, "select id, name, pass from user where name = 'DelFox'", -1, &stmt, 0);
    const unsigned char* name, * id, * pass;
    sqlite3_step(stmt);
    id = sqlite3_column_text(stmt, 0);
    name = sqlite3_column_text(stmt, 1);
    pass = sqlite3_column_text(stmt, 2);
    cout << "La id es: " << id << " Nombre: " << name << " Pass: " << pass << endl;
    //para elegir filas distintas:
    //while(sqlite3_step(stmt) != SQLITE_NONE)
    sqlite3_close(db);
}

const unsigned char* getUserId(sqlite3* db, sqlite3_stmt* stmt, const char name) {
    const unsigned char* idR;
    sqlite3_prepare_v2(db, "select name from user where name = " + name, -1, &stmt, 0);
    sqlite3_step(stmt);
    idR = sqlite3_column_text(stmt, 0);

    return idR;

}

const unsigned char* getUserName(sqlite3* db, sqlite3_stmt* stmt, const char id) {
    const unsigned char* nameR;
    sqlite3_prepare_v2(db, "select id from user where name = " + id, -1, &stmt, 0);
    sqlite3_step(stmt);
    nameR = sqlite3_column_text(stmt, 1);

    return nameR;

}

const unsigned char* getUserPass(sqlite3* db, sqlite3_stmt* stmt, const char name) {
    const unsigned char* passR;
    const char* consulta = "select pass from user where name = " + name;
    sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);
    sqlite3_step(stmt);
    passR = sqlite3_column_text(stmt, 2);

    return passR;

}

const unsigned char* getUserElo(sqlite3* db, sqlite3_stmt* stmt, const char name) {
    const unsigned char* eloR;
    const char* consulta = "select id from user where name = " + name;
    sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);
    sqlite3_step(stmt);
    eloR = sqlite3_column_text(stmt, 3);

    return eloR;

}


const unsigned char* getMatchId(sqlite3* db, sqlite3_stmt* stmt, const char idPlayer) {
    const unsigned char* eloM;
    const char* consulta = "select id from history where id_whitePlayer = " + idPlayer;
    sqlite3_prepare_v2(db, consulta, -1, &stmt, 0);
    sqlite3_step(stmt);
    eloM = sqlite3_column_text(stmt, 3);

    return eloM;

}
*/