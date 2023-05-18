#include <iostream>
#include <pqxx/pqxx>

#include "Database.h"

void Database::do_something() {
    pqxx::result res = worker.exec("SELECT * FROM pg_catalog.pg_tables");
    for (auto const& row : res)
    {
        for (auto const& field : row) cout << field.c_str() << '\t';
        cout << endl;
    }
}