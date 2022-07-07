#include <iostream>
#include "users.hpp"

int main() {
    AccountDatabase database;
    //.add_user("Mihai2002", "1234", AccountType::Admin);
    //database.add_user("Matei2003", "5678", AccountType::User);

    bool is_logged = 0;
    do {
        std::string user, pass;
        std::cout << "user: ";
        std::cin >> user;
        std::cout << "\n";
        std::cout << "pass: ";
        std::cin >> pass;
        std::cout << "\n";
        bool admin;
        std::cout << "admin: ";
        std::cin >> admin;

        if(admin)
            database.add_user(user, pass, AccountType::Admin);
        else 
            database.add_user(user, pass, AccountType::User);
        // if(database.auth(user, pass).type != AccountType::InvalidUser) {
        //     switch (database.auth(user, pass).type)
        //     {
        //     case AccountType::Admin:
        //         is_logged = 1;
        //         //trb ca functie a unei clase AdminMenu care da override la interfata IMenu
        //         int optiune;
        //         std::cout << "[admin]" << user << ":\n\n";
        //         std::cout << "1) Add Item\n2) Remove Item\n3) Add User\n4) Ban User\n5) Logout\nChoose Option: ";
        //         std::cin >> optiune;
        //         break;
            
        //     case AccountType::User:
        //         is_logged = 1;
        //         //trb ca functie a unei clase UserMenu care da override la interfata IMenu
        //         std::cout << "[admin]" << user << ":\n\n";
        //         std::cout << "1) View Cart\n2) Browse the shop\n3) Logout\nChoose Option: ";
        //         std::cin >> optiune;
        //         break;
        //     default:
        //         break;
        //     }
        // }
    // if(!is_logged)
    //     std::cout << "Wrong username or password. Please try again.\n";
    } while(!is_logged);
    return 0;
}