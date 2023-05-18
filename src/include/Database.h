#ifndef DATABASE_H
#define DATABASE_H


#include <iostream>
#include <pqxx/pqxx>

#include "Config.h"

using namespace std;


class Database {
private:
    Config config = Config();

    pqxx::connection connection = pqxx::connection("dbname=postgres user=postgres password=" + config.get_db_pass() + " hostaddr=127.0.0.1 port=5432");
    pqxx::work worker = pqxx::work(connection);

public:
    Database() {
        if (connection.is_open()) {
            cout << "Opened database successfully: " << connection.dbname() << endl;
        }
        else {
            cout << "Can't open database" << endl;
        }
    }

    void do_something();
};


#endif