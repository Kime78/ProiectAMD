#include <iostream>
#include "menu.hpp"
#include "users.hpp"
#include "products.hpp"
#include <time.h>

int main() {
    srand(time(NULL));
    AccountDatabase acc_database;
    ProductDatabase prod_database;
    prod_database.add_product(Product("Hello", 69));
    acc_database.load_users_from_file();
    Menu* menu = new MainMenu;
    menu->draw(acc_database, prod_database);
    
    return 0;
}