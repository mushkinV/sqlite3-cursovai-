#include "sql.h"
#include <iostream>
#include <sqlite3.h>

bool SQL::executeQuery(const std::string& query) {
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    char* errMsg;
    rc = sqlite3_exec(db, query.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при выполнении SQL-запроса: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}