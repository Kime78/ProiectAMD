#include <iostream>
#include "menu.hpp"
#include "users.hpp"
#include "products.hpp"
#include <time.h>

int main() {
    srand(time(NULL));
    AccountDatabase acc_database;
    ProductDatabase prod_database;
    acc_database.load_users_from_file();
    prod_database.load_products_from_file();
    Menu* menu = new MainMenu;
    menu->draw(acc_database, prod_database);
    delete menu;
    return 0;
}