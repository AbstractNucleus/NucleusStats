#ifndef CONFIG_H
#define CONFIG_H

#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

class Config {
private:
    json config;

public:
    Config() {
        ifstream json_stream = ifstream("../config.json");
        json_stream >> config;
    }

    string get_token() { return config["token"]; };

    string get_db_pass() { return config["db_pass"]; };
};

#endif