#pragma once
#include <string>
#include <vector>
//to do: read users and products from a hidden text file

enum class AccountType {
    InvalidUser = 0, User, Admin
};

struct Account {
    std::vector<uint64_t> shopping_cart; //to be redesigned later
    std::string username;
    std::string password;
    AccountType type;
    Account(std::string username, std::string password, AccountType type);
};

class AccountDatabase {
    std::vector<Account> database;
public:
    Account get_user_by_id(uint64_t id);

    std::vector<Account> get_users_by_name(std::string user);

    std::vector<Account> get_users();

    Account auth(std::string user, std::string pass);

    void add_user(std::string user, std::string pass, AccountType type);
};