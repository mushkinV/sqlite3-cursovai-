#ifndef DATABASE_OPERATIONS_H
#define DATABASE_OPERATIONS_H

#include <string>

class DatabaseOperations {
public:
    DatabaseOperations();
    bool addData(const std::string& name);
    bool deleteData(int id);
    bool updateData(int id, const std::string& newName);

private:
    // Add any necessary private variables or helper functions here
};

#endif // DATABASE_OPERATIONS_H