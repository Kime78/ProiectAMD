#pragma once
#include <string>
#include <vector>
//to do: read users and products from a hidden text file

enum class AccountType {
    InvalidUser = 0, User, Admin
};

struct ShoppingCart {
private:
    std::vector<uint64_t> cart;
public:
    void add_product(uint64_t id);
    void remove_product(uint64_t id);
    const std::vector<uint64_t> get_products();
};
struct Account {
    ShoppingCart cart;
    std::string username;
    std::string password;
    uint64_t id;
    AccountType type;
    Account(std::string username, std::string password, AccountType type);
};

class AccountDatabase {
    std::vector<Account> account_database;
public:

    uint64_t logged_user_id = 0;
    Account& get_user_by_id(uint64_t id);

    const std::vector<Account> get_users_by_name(std::string user);

    const std::vector<Account> get_users();

    Account auth(std::string user, std::string pass);

    void add_user(std::string user, std::string pass, AccountType type);

    void remove_user(uint64_t id);

    void make_admin(uint64_t id);

    void load_users_from_file();
};