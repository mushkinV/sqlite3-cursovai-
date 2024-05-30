#include "connect_bd.h"
#include <iostream>

Database::Database() : db(nullptr) {}

bool Database::openDatabase(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Ошибка открытия базы данных SQLite: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    else {
        std::cout << "База данных SQLite успешно открыта" << std::endl;
        return true;
    }
}

bool Database::createTestDatabase(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Ошибка создания базы данных SQLite: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    else {
        std::cout << "База данных SQLite успешно создана" << std::endl;
        return true;
    }
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    // Реализуем функцию обратного вызова для запросов к SQLite
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}