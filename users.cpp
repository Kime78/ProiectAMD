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
    Account acc(user, pass, type); 
    if(type == AccountType::User)
        accounts << acc.id << "\t" << user << "\t" << pass << "\t" << "User" << '\n';
    else
        accounts << acc.id << "\t" << user << "\t" << pass << "\t" << "Admin" << '\n';
    account_database.push_back(acc);
}

void AccountDatabase::remove_user(uint64_t id) {
    //todo: remove from file
    std::ifstream in("./.secrets/accounts.txt");
    std::ofstream out("./.secrets/accounts.txt");
    std::string line;
    std::string delete_line;
    Account acc = get_user_by_id(id);
    if(acc.type == AccountType::Admin)
        delete_line = std::to_string(acc.id) + "\t" + acc.username + "\t" + acc.password + "\t" + "Admin";
    else
        delete_line = std::to_string(acc.id) + "\t" + acc.username + "\t" + acc.password + "\t" + "User";
    while (getline(in, line)) {
        line.replace(line.find(delete_line), delete_line.length(), "");
        //out << line << std::endl;
    }
    
    for(auto i = account_database.begin(); i != account_database.end(); i++) {
        if((*i).id == id) {
            account_database.erase(i);
            break;
        }
    }
}

void AccountDatabase::make_admin(uint64_t id) {
    for(size_t i = 0; i < account_database.size(); i++) {
        if(account_database[i].id == id) {
            account_database[i].type = AccountType::Admin;
        }
    }
}

void AccountDatabase::load_users_from_file() {
    std::ifstream account_file("./.secrets/accounts.txt");
    std::string user, pass;
    std::string admin;

    uint64_t id;

    while(account_file >> id >> user >> pass >> admin) {
        if(admin == "Admin") {
            Account acc(user, pass, AccountType::Admin);
            acc.id = id;
            account_database.push_back(acc);
        }
        else if(admin == "User"){
            Account acc(user, pass, AccountType::User);
            acc.id = id;
            account_database.push_back(acc);
        }
        else
            account_database.push_back(Account("", "", AccountType::InvalidUser));
    }
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