#include <sstream>
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <pqxx/pqxx>
#include <iostream>

using json = nlohmann::json;

int main(int argc, char const* argv[])
{
    /* Setup the bot */
    json configdocument;
    std::ifstream configfile("../config.json");
    configfile >> configdocument;
    dpp::cluster bot(configdocument["token"]);

    /* Load database */
    std::string conn_string_1 = "dbname=postgres user=postgres password=";
    std::string conn_string_2 = configdocument["db_pass"];
    std::string conn_string_3 = " hostaddr=127.0.0.1 port=5432";
    std::string conn_string = conn_string_1 + conn_string_2 + conn_string_3;
    pqxx::connection c(conn_string);
    if (c.is_open()) {
        std::cout << "Opened database successfully: " << c.dbname() << std::endl;
    }
    else {
        std::cout << "Can't open database" << std::endl;
        return 1;
    }

    

    pqxx::work w(c);
    pqxx::result res = w.exec("SELECT * FROM pg_catalog.pg_tables");
    w.commit();
    for (auto const& row : res)
    {
        for (auto const& field : row) std::cout << field.c_str() << '\t';
        std::cout << std::endl;
    }

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle slash command */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
        });

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
        });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}
