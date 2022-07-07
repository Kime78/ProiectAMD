#include "users.hpp"
#include <algorithm>
#include <fstream>

Account::Account(std::string user, std::string pass, AccountType type) {
    this->username = user;
    this->password = pass;
    this->type = type;
}

Account AccountDatabase::get_user_by_id(uint64_t id) {
    if(id > account_database.size() || id < 0)
        exit(EXIT_FAILURE);
    return account_database[id];
}

const std::vector<Account> AccountDatabase::get_users_by_name(std::string user) {
    std::vector<Account> lista_conturi;
    for(size_t i = 0; i < account_database.size(); i++) {
        if(account_database[i].username == user)
            lista_conturi.push_back(account_database[i]);
    }
    return lista_conturi;
}

const std::vector<Account> AccountDatabase::get_users() {
    return account_database;
}

Account AccountDatabase::auth(std::string user, std::string pass) {
    for(size_t i = 0; i < account_database.size(); i++) {
        if(account_database[i].username == user && account_database[i].password == pass)
            return account_database[i];
    }
    return Account("", "", AccountType::InvalidUser);
}

void AccountDatabase::add_user(std::string user, std::string pass, AccountType type = AccountType::User) { 
    //https://stackoverflow.com/questions/6932409/writing-a-string-to-the-end-of-a-file-c
    std::ofstream accounts;
    accounts.open("./.secrets/accounts.txt", std::ios::app);
    if(type == AccountType::User)
        accounts << user << "\t" << pass << "\t" << "User" << '\n';
    else
        accounts << user << "\t" << pass << "\t" << "Admin" << '\n';
    account_database.push_back(Account(user, pass, type));
}

void ShoppingCart::add_product(uint64_t id) {
    cart.push_back(id);
}

void ShoppingCart::remove_product(uint64_t id) {
    //https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
    cart.erase(std::remove(cart.begin(), cart.end(), id), cart.end());
}

const std::vector<uint64_t> ShoppingCart::get_products() {
    return cart;
}