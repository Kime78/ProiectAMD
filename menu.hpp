#pragma once
#include "users.hpp"
#include "products.hpp"

struct Menu {
    virtual void draw(AccountDatabase& accounts, ProductDatabase& products) = 0;
};

struct AdminMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct UserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct ShopMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct CartMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct AddUserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct RemoveUserMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct AddProductMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct RemoveProductMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct LoginMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct MainMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct SignupMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};

struct MakeAdminMenu : public Menu {
    void draw(AccountDatabase& accounts, ProductDatabase& products) override;
};