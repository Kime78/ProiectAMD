#include "menu.hpp"
#include <iostream>

void AdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    int optiune;
    //std::cout << "[admin]" << user << ":\n\n"; //vezi mai tarz
    std::cout << "1) Add Item\n2) Remove Item\n3) Add User\n4) Ban User\n5) Make Admin\n6) Logout\n\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new AddProductMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 2:
        menu = new RemoveProductMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 3:
        menu = new AddUserMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 4:
        menu = new RemoveUserMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 5:
        menu = new MakeAdminMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 6:
        menu = new MainMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    
    default:
        break;
    }
}

void UserMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    int optiune;
    std::cout << "1) View Cart\n2) Browse the shop\n3) Logout\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new CartMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 2:
        menu = new ShopMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    case 3:
        menu = new MainMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
        
        break;
    
    default:
        break;
    }
}

void AddUserMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
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
    system("clear");
    menu->draw(accounts, products, logged_id);
    
}

void RemoveUserMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    uint64_t id;
    std::cout << "ID of user to be deleted: ";
    std::cin >> id;
    accounts.remove_user(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products, logged_id);
}

void AddProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    std::string name;
    uint64_t id;
    uint32_t price;

    double weight;
    double height;
    uint8_t nms;
    double tdp;
    uint32_t memory;
    uint32_t clock;

    std::string type;

    uint16_t cores;
    uint16_t threads;
    std::string socket;

    uint32_t max_vertical_res;
    uint32_t max_horizontal_res;
    std::string tech;

    std::cout << "Name of the product: ";
    std::cin >> name;
    std::cout << "Price of the product: ";
    std::cin >> price;
    std::cout << "Type of the product: ";
    std::cin >> type;

    std::cout << "weight: ";
    std::cin >> weight;
    std::cout << "height: ";
    std::cin >> height;
    std::cout << "nms: ";
    std::cin >> nms;
    std::cout << "tdp: ";
    std::cin >> tdp;
    std::cout << "memory: ";
    std::cin >> memory;
    std::cout << "clock: ";
    std::cin >> clock;
    if(type == "CPU") {
        std::cout << "cores: ";
        std::cin >> cores;
        std::cout << "threads: ";
        std::cin >> threads;
        std::cout << "socket: ";
        std::cin >> socket;

        Product* prod = new Product(name, price);
        
        prod->cpu = new CPU(cores, threads, socket);
        prod->cpu->set_weight(weight);
        prod->cpu->set_height(height);
        prod->cpu->set_nms(nms);
        prod->cpu->set_tdp(tdp);
        prod->cpu->set_memory(memory);
        prod->cpu->set_clock(clock);
        prod->type = ProductType::CPU;

        products.add_product(*prod);

        delete prod;
    }
    if(type == "GPU") {
        std::cout << "max horizontal resolution: ";
        std::cin >> max_horizontal_res;
        std::cout << "max vertical resolution: ";
        std::cin >> max_vertical_res;
        std::cout << "Supported Technologies: ";
        std::cin >> tech;

        Product* prod= new Product(name, price);
        SupportedTechnologies s_tech;
        if(tech == "OpenGL") {
            s_tech = SupportedTechnologies::OpenGL;
        }
        if(tech == "DirectX") {
            s_tech = SupportedTechnologies::DirectX;
        }
        if(tech == "Vulkan") {
            s_tech = SupportedTechnologies::Vulkan;
        }
        if(tech == "OpenGL&DirectX") {
            s_tech = SupportedTechnologies::OpenGL_DirectX;
        }
        if(tech == "OpenGL&Vulkan") {
            s_tech = SupportedTechnologies::OpenGL_Vulkan;
        }
        if(tech == "Vulkan&DirectX") {
            s_tech = SupportedTechnologies::Vulkan_DirectX;
        }
        if(tech == "OpenGL&Vulkan&DirectX") {
            s_tech = SupportedTechnologies::OpenGL_Vulkan_DirectX;
        }
        prod->gpu = new GPU(max_vertical_res, max_horizontal_res, s_tech);
        prod->gpu->set_weight(weight);
        prod->gpu->set_height(height);
        prod->gpu->set_nms(nms);
        prod->gpu->set_tdp(tdp);
        prod->gpu->set_memory(memory);
        prod->gpu->set_clock(clock);
        prod->type = ProductType::GPU;

        products.add_product(*prod);

        delete prod;
    }
    if(type == "APU") {
        std::cout << "cores: ";
        std::cin >> cores;
        std::cout << "threads: ";
        std::cin >> threads;
        std::cout << "socket: ";
        std::cin >> socket;

        std::cout << "max horizontal resolution: ";
        std::cin >> max_horizontal_res;
        std::cout << "max vertical resolution: ";
        std::cin >> max_vertical_res;
        std::cout << "Supported Technologies: ";
        std::cin >> tech;

        Product* prod = new Product(name, price);
        SupportedTechnologies s_tech;
        if(tech == "OpenGL") {
            s_tech = SupportedTechnologies::OpenGL;
        }
        if(tech == "DirectX") {
            s_tech = SupportedTechnologies::DirectX;
        }
        if(tech == "Vulkan") {
            s_tech = SupportedTechnologies::Vulkan;
        }
        if(tech == "OpenGL&DirectX") {
            s_tech = SupportedTechnologies::OpenGL_DirectX;
        }
        if(tech == "OpenGL&Vulkan") {
            s_tech = SupportedTechnologies::OpenGL_Vulkan;
        }
        if(tech == "Vulkan&DirectX") {
            s_tech = SupportedTechnologies::Vulkan_DirectX;
        }
        if(tech == "OpenGL&Vulkan&DirectX") {
            s_tech = SupportedTechnologies::OpenGL_Vulkan_DirectX;
        }
        prod->apu = new APU();
        prod->apu->CPU::set_weight(weight);
        prod->apu->CPU::set_height(height);
        prod->apu->CPU::set_nms(nms);
        prod->apu->CPU::set_tdp(tdp);
        prod->apu->CPU::set_memory(memory);
        prod->apu->CPU::set_clock(clock);

        prod->apu->set_cores(cores);
        prod->apu->set_threads(cores);
        prod->apu->set_socket(socket);
        
        prod->apu->set_max_horizontal_res(max_horizontal_res);
        prod->apu->set_max_vertical_res(max_vertical_res);
        prod->apu->set_supported_tech(s_tech);

        prod->type = ProductType::APU;

        products.add_product(*prod);

        delete prod;
    }
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products, logged_id);
}

void RemoveProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    uint64_t id;
    std::cout << "ID of product to be deleted: ";
    std::cin >> id;
    products.remove_product(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products, logged_id);
}

void MakeAdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    uint64_t id;
    std::cout << "ID of user to be promoted to ADMIN: ";
    std::cin >> id;
    accounts.make_admin(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products, logged_id);
}

void MainMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    int optiune;
    //std::cout << "[admin]" << user << ":\n\n"; //vezi mai tarz
    std::cout << "1) Login\n2) Signup\n3) Exit\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new LoginMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);   
        break;
    case 2:
        menu = new SignupMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
    case 3:
        return;
        break;
    
    default:
        break;
    }
}

void CartMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    Account acc = accounts.get_user_by_id(logged_id);
    if(acc.type == AccountType::InvalidUser) {
        std::cout << "ERROR: INVALID USER";
        exit(EXIT_FAILURE);
    }

    std::vector<uint64_t> cart = acc.cart.get_products();
    Menu* menu;
    if(cart.size() == 0) {
        std::cout << acc.username << ", your shopping cart is empty. Press enter to go back to the menu.";
        std::cin.get();
        menu = new UserMenu;
        system("clear");
        menu->draw(accounts, products, logged_id);
    }
    else {
        size_t index = 0;
        if(cart.size() < 10) {
            for(; index < cart.size(); index++) {
                std::cout << index + 1 << ") " << products.get_product_by_id(cart[index]).name << '\n';
            }
            size_t option;
            std::cout << "\nType a number to select the desired product to buy or 0 to buy them all or E to exit the shop: ";
            std::cin >> option;

            Menu* menu;
            if(option == 'E') {
                menu = new UserMenu;
                menu->draw(accounts, products, logged_id);
            } 
            else if(option == '0') {
                for(size_t i = 0; i < cart.size(); i++) {
                    acc.cart.remove_product(cart[i]);
                }
                menu = new UserMenu;
                menu->draw(accounts, products, logged_id);
            }

            acc.cart.remove_product(cart[option - 1]);
            menu = new UserMenu;
            menu->draw(accounts, products, logged_id);
        }
        else {
            size_t num_pages = cart.size() / 10;
            size_t products_on_last_page = cart.size() % 10;
            size_t selected_page;
            std::cout << "Select a page to view [1 - " << num_pages + 1 << "]: ";
            std::cin >> selected_page;
            selected_page--;
            if(selected_page != num_pages) // if it's not the last page
                for(size_t i = 10 * selected_page; i < 10 * selected_page + 10; i++) {
                    std::cout << i + 1 << ") " << products.get_product_by_id(cart[index]).name << '\n';
                }
            else {
                for(size_t i = 10 * selected_page; i < 10 * selected_page + products_on_last_page; i++) {
                    std::cout << i + 1 << ") " << products.get_product_by_id(cart[index]).name << '\n';
                }
            }
            int option;
            std::cout << "\nType a number to select the desired product to buy or 0 to buy them all or B to select another page or E to exit the shop: ";
            std::cin >> option;

            Menu* menu;

            //solve this
            if(option == 'E') {
                menu = new UserMenu;
                menu->draw(accounts, products, logged_id);
            } 
            else if(option == 'B') {
                menu = new ShopMenu;
                menu->draw(accounts, products, logged_id);
            }
            else if(option == '0') {
                for(size_t i = 0; i < cart.size(); i++) {
                    acc.cart.remove_product(cart[i]);
                }
                menu = new UserMenu;
                menu->draw(accounts, products, logged_id);
            }

            acc.cart.remove_product(cart[option - 1]);
            menu = new UserMenu;
            menu->draw(accounts, products, logged_id);
        }
    }
}

void ShopMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    size_t index = 0;
    //select filter
    std::vector<Product> prod = products.get_products();
    if(prod.size() < 10) {
        for(; index < prod.size(); index++) {
            std::cout << index + 1 << ") " << prod[index].name << '\n';
        }
        size_t option;
        std::cout << "\nType a number to select the desired product or E to exit the shop: ";
        std::cin >> option;

        Menu* menu;
        if(option == 'E') {
            menu = new UserMenu;
            menu->draw(accounts, products, logged_id);
        } 
        else {
            //view product menu - 1
        }
    }
    else {
        size_t num_pages = prod.size() / 10;
        size_t products_on_last_page = prod.size() % 10;
        size_t selected_page;
        std::cout << "Select a page to view [1 - " << num_pages + 1 << "]: ";
        std::cin >> selected_page;
        selected_page--;
        if(selected_page != num_pages) // if it's not the last page
            for(size_t i = 10 * selected_page; i < 10 * selected_page + 10; i++) {
                std::cout << i + 1 << ") " << prod[i].name << '\n';
            }
        else {
            for(size_t i = 10 * selected_page; i < 10 * selected_page + products_on_last_page; i++) {
                std::cout << i + 1 << ") " << prod[i].name << '\n';
            }
        }
        int option;
        std::cout << "\nType a number to select the desired product or type B to select another page or E to exit the shop: ";
        std::cin >> option;

        Menu* menu;

        //solve this
        if(option == 'E') {
            menu = new UserMenu;
            menu->draw(accounts, products, logged_id);
        } 
        else if(option == 'B') {
            menu = new ShopMenu;
            menu->draw(accounts, products, logged_id);
        }
        else {
            //view products - 1
            Account& acc = accounts.get_user_by_id(logged_id);
            acc.cart.add_product(prod[option - 1].id); 
            menu = new UserMenu;
            menu->draw(accounts, products, logged_id);
        }
    }
}

void SignupMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    std::string user, pass;
    std::cout << "user: ";
    std::cin >> user;
    std::cout << "pass: ";
    std::cin >> pass;

    accounts.add_user(user, pass, AccountType::User);
    std::cout << "Your account has been succcesfully created, you may login now.\n\n";

    Menu* menu = new UserMenu;
    
    logged_id = accounts.get_users_by_name(user)[0].id;
    menu->draw(accounts, products, logged_id);
}

void LoginMenu::draw(AccountDatabase& accounts, ProductDatabase& products, uint64_t logged_id) {
    std::string user, pass;
    std::cout << "user: ";
    std::cin >> user;
    std::cout << "pass: ";
    std::cin >> pass;

    Account a = accounts.auth(user, pass);
    Menu* menu;
    switch (a.type) {
    case AccountType::InvalidUser:
        std::cout << "Invalid username or password! Please try again.\n\n";
        menu = new LoginMenu;
        menu->draw(accounts, products, logged_id);
        break;
    case AccountType::User:
        system("clear");
        std::cout << "Welcome " << a.username << "!\n\n";
        menu = new UserMenu;
        system("clear");
        logged_id = a.id;
        menu->draw(accounts, products, logged_id);
        break;

    case AccountType::Admin:
        system("clear");
        std::cout << "Welcome " << a.username << "!\n\n";
        menu = new AdminMenu;
        system("clear");
        logged_id = a.id;
        menu->draw(accounts, products, logged_id);
        break;

    default:
        break;
    }
}