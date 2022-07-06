#include "users.hpp"

Account::Account(std::string user, std::string pass, AccountType type) {
    this->username = user;
    this->password = pass;
    this->type = type;
}

Account AccountDatabase::get_user_by_id(uint64_t id) {
    if(id > database.size() || id < 0)
        exit(EXIT_FAILURE);
    return database[id];
}

std::vector<Account> AccountDatabase::get_users_by_name(std::string user) {
    std::vector<Account> lista_conturi;
    for(size_t i = 0; i < database.size(); i++) {
        if(database[i].username == user)
            lista_conturi.push_back(database[i]);
    }
    return lista_conturi;
}

std::vector<Account> AccountDatabase::get_users() {
    return database;
}

Account AccountDatabase::auth(std::string user, std::string pass) {
    for(size_t i = 0; i < database.size(); i++) {
        if(database[i].username == user && database[i].password == pass)
            return database[i];
    }
    return Account("", "", AccountType::InvalidUser);
}

void AccountDatabase::add_user(std::string user, std::string pass, AccountType type = AccountType::User) {
    database.push_back(Account(user, pass, type));
}