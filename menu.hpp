#pragma once
#include "users.hpp"
#include "products.hpp"

struct Menu {
    virtual void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) = 0;
};

struct AdminMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct UserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct ShopMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct CartMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct AddUserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct RemoveUserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct AddProductMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct RemoveProductMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct LoginMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct MainMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct SignupMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};

struct MakeAdminMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) override;
};