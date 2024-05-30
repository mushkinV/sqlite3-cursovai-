#ifndef SQLITE_VISUAL_H
#define SQLITE_VISUAL_H

#include <iostream>
#include <string>
#include <sqlite3.h>

class Database {
public:
    Database();
    bool openDatabase(const std::string& dbName);
    bool createTestDatabase(const std::string& dbName);

private:
    sqlite3* db;
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

Database::Database() {
    db = nullptr;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

bool Database::openDatabase(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Ошибка при открытии/создании базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

bool Database::createTestDatabase(const std::string& dbName) {
    if (openDatabase(dbName)) {
        std::cerr << "База данных с именем '" << dbName << "' уже существует" << std::endl;
        sqlite3_close(db);
        return false;
    }

    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Ошибка при открытии/создании базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    char* errMsg;
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS test (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT);";
    rc = sqlite3_exec(db, createTableQuery, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при создании таблицы test: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    const char* insertDataQuery = "INSERT INTO test (Name) VALUES ('TestName1'), ('TestName2'), ('TestName3');";
    rc = sqlite3_exec(db, insertDataQuery, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при вставке тестовых данных: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    std::cout << "Тестовая бд 'test' с таблицей 'test' создана" << std::endl;
    return true;
}

#endif 