#include "database_operations.h"
#include "connect_bd.h"


bool DatabaseOperations::addData(const std::string& name) {
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    std::string insertQuery = "INSERT INTO table_name (column_name) VALUES ('" + name + "');";
    char* errMsg;
    rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

bool DatabaseOperations::deleteData(int id) {
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string deleteQuery = "DELETE FROM table_name WHERE ID = " + std::to_string(id) + ";";
    char* errMsg;
    rc = sqlite3_exec(db, deleteQuery.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при удалении данных: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

bool DatabaseOperations::updateData(int id, const std::string& newName) {
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при открытии базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string updateQuery = "UPDATE table_name SET column_name = '" + newName + "' WHERE ID = " + std::to_string(id) + ";";
    char* errMsg;
    rc = sqlite3_exec(db, updateQuery.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка при обновлении данных: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}