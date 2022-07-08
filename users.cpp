#include "users.hpp"
#include <algorithm>
#include <fstream>

Account::Account(std::string user, std::string pass, AccountType type) {
    this->username = user;
    this->password = pass;
    this->type = type;
    this->id = random();
}

Account AccountDatabase::get_user_by_id(uint64_t id) {
    for(size_t i = 0; i < account_database.size(); i++)
        if(account_database[i].id == id)
            return account_database[i];
    return Account("", "", AccountType::InvalidUser);
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
    for(size_t i = 0; i < account_database.size(); i++) {
        if(account_database[i].username == user && account_database[i].password == pass) //an account cannot be added twice
            return;
    }
    if(type == AccountType::User)
        accounts << '\n' << user << "\t" << pass << "\t" << "User" << '\n';
    else
        accounts << '\n' << user << "\t" << pass << "\t" << "Admin" << '\n';
    account_database.push_back(Account(user, pass, type));
}

void AccountDatabase::remove_user(uint64_t id) {
    //todo: remove from file
    std::ifstream in("./.secrets/accounts.txt");
    std::ofstream out("./.secrets/accounts.txt");
    std::string line;
    std::string delete_line;
    Account acc = get_user_by_id(id);
    if(acc.type == AccountType::Admin)
        delete_line = acc.username + "\t" + acc.password + "\t" + "Admin";
    else
        delete_line = acc.username + "\t" + acc.password + "\t" + "User";
    while (getline(in, line)) {
        line.replace(line.find(delete_line), delete_line.length(), "");
    }
    
    //account_database.erase(std::remove(account_database.begin(), account_database.end(), id), account_database.end());
}

void AccountDatabase::load_users_from_file() {
    std::ifstream account_file("./.secrets/accounts.txt");
    std::string user, pass;
    std::string admin;

    while(account_file >> user >> pass >> admin) {
        if(admin == "Admin")
            account_database.push_back(Account(user, pass, AccountType::Admin));
        else if(admin == "User")
            account_database.push_back(Account(user, pass, AccountType::User));
        else
            account_database.push_back(Account("", "", AccountType::InvalidUser));
    }
    
}

void ShoppingCart::add_product(uint64_t id) {
    cart.push_back(id);
}

void ShoppingCart::remove_product(uint64_t id) {
    //https://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
    //cart.erase(std::remove(cart.begin(), cart.end(), id), cart.end());
}

const std::vector<uint64_t> ShoppingCart::get_products() {
    return cart;
}