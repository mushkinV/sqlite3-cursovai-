#include "connect_bd.h"
#include "database_operations.h"
#include "sql.h" // Добавляем заголовочный файл для класса SQL
#include <iostream>
#include <conio.h> // Для функции _getch()

int main() {
    setlocale(LC_ALL, "ru");

    std::string dbName;
    std::cout << "Введите имя базы данных: ";
    std::cin >> dbName;

    Database database;
    bool success = database.openDatabase(dbName);
    if (!success) {
        std::cout << "База данных с именем '" << dbName << "' не существует. Создание новой базы данных..." << std::endl;
        success = database.createTestDatabase(dbName);
        if (success) {
            std::cout << "Новая база данных с именем '" << dbName << "' успешно создана" << std::endl;
        }
        else {
            std::cerr << "Ошибка при создании базы данных с именем '" << dbName << "'" << std::endl;
            return 1;
        }
    }

    DatabaseOperations dbOperations;
    SQL sql; // Создаем объект класса SQL

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Добавить данные" << std::endl;
        std::cout << "2. Удалить данные" << std::endl;
        std::cout << "3. Изменить данные" << std::endl;
        std::cout << "4. Выполнить SQL-запрос" << std::endl; // Добавляем новое действие
        std::cout << "Нажмите ESC для выхода" << std::endl;

        char choice = _getch();
        switch (choice) {
        case '1': {
            std::string newData;
            std::cout << "Введите данные для добавления: ";
            std::cin >> newData;
            success = dbOperations.addData(newData);
            if (success) {
                std::cout << "Данные успешно добавлены" << std::endl;
            }
            else {
                std::cerr << "Ошибка при добавлении данных" << std::endl;
            }
            break;
        }
        case '2': {
            int idToDelete;
            std::cout << "Введите ID данных для удаления: ";
            std::cin >> idToDelete;
            success = dbOperations.deleteData(idToDelete);
            if (success) {
                std::cout << "Данные успешно удалены" << std::endl;
            }
            else {
                std::cerr << "Ошибка при удалении данных" << std::endl;
            }
            break;
        }
        case '3': {
            int idToUpdate;
            std::string updatedData;
            std::cout << "Введите ID данных для изменения: ";
            std::cin >> idToUpdate;
            std::cout << "Введите новые данные: ";
            std::cin >> updatedData;
            success = dbOperations.updateData(idToUpdate, updatedData);
            if (success) {
                std::cout << "Данные успешно изменены" << std::endl;
            }
            else {
                std::cerr << "Ошибка при изменении данных" << std::endl;
            }
            break;
        }
        case '4': { // Добавляем новый case для выполнения SQL-запроса
            std::string query;
            std::cout << "Введите SQL-запрос: ";
            std::cin.ignore();
            std::getline(std::cin, query);
            success = sql.executeQuery(query);
            if (success) {
                std::cout << "SQL-запрос успешно выполнен" << std::endl;
            }
            else {
                std::cerr << "Ошибка при выполнении SQL-запроса" << std::endl;
            }
            break;
        }
        case 27: // ASCII код для клавиши ESC
            std::cout << "До свидания!" << std::endl;
            return 0;
        default:
            std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
            break;
        }
    }

    return 0;
}




