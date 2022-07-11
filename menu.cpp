#include "menu.hpp"
#include <iostream>

void AdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    int optiune;
    //std::cout << "[admin]" << user << ":\n\n"; //vezi mai tarz
    std::cout << "1) Add Item\n2) Remove Item\n3) Add User\n4) Ban User\n5) Make Admin\n6) Logout\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new AddProductMenu;
        menu->draw(accounts, products);
        
        break;
    case 2:
        menu = new RemoveProductMenu;
        menu->draw(accounts, products);
        
        break;
    case 3:
        menu = new AddUserMenu;
        menu->draw(accounts, products);
        
        break;
    case 4:
        menu = new RemoveUserMenu;
        menu->draw(accounts, products);
        
        break;
    case 5:
        menu = new MakeAdminMenu;
        menu->draw(accounts, products);
        
        break;
    case 6:
        menu = new MainMenu;
        menu->draw(accounts, products);
        
        break;
    
    default:
        break;
    }
}

void UserMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    int optiune;
    std::cout << "1) View Cart\n2) Browse the shop\n3) Logout\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new CartMenu;
        menu->draw(accounts, products);
        
        break;
    case 2:
        menu = new ShopMenu;
        menu->draw(accounts, products);
        
        break;
    case 3:
        menu = new MainMenu;
        menu->draw(accounts, products);
        
        break;
    
    default:
        break;
    }
}

void AddUserMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    std::string user, pass;
    bool admin;
    std::cout << "user: ";
    std::cin >> user;
    std::cout << "pass: ";
    std::cin >> pass;
    std::cout << "admin: ";
    std::cin >> admin;

    if(admin)
        accounts.add_user(user, pass, AccountType::Admin);
    else
        accounts.add_user(user, pass, AccountType::User);
    Menu* menu = new AdminMenu;
    menu->draw(accounts, products);
    
}

void RemoveUserMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    uint64_t id;
    std::cout << "ID of user to be deleted: ";
    std::cin >> id;
    accounts.remove_user(id);
    Menu* menu = new AdminMenu;
    menu->draw(accounts, products);
}

void AddProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void RemoveProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void MakeAdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void MainMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    int optiune;
    //std::cout << "[admin]" << user << ":\n\n"; //vezi mai tarz
    std::cout << "1) Login\n2) Signup\n3) Exit\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new LoginMenu;
        menu->draw(accounts, products);   
        break;
    case 2:
        menu = new SignupMenu;
        menu->draw(accounts, products);
    case 6:
        return;
        break;
    
    default:
        break;
    }
}

void CartMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void ShopMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void SignupMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {

}

void LoginMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    
}