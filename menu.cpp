#include "menu.hpp"
#include <iostream>

void AdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    std::cout << "Welcome " << accounts.get_user_by_id(accounts.logged_user_id).username << "!\n\n";
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
        menu->draw(accounts, products);
        delete menu;
        break;
    case 2:
        menu = new RemoveProductMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 3:
        menu = new AddUserMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 4:
        menu = new RemoveUserMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 5:
        menu = new MakeAdminMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 6:
        menu = new MainMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    
    default:
        break;
    }
}

void UserMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    std::cout << "Welcome " << accounts.get_user_by_id(accounts.logged_user_id).username << "!\n\n";
    int optiune;
    std::cout << "1) View Cart\n2) Browse the shop\n3) Logout\nChoose Option: ";
    std::cin >> optiune;
    switch (optiune)
    {
        Menu* menu;
    case 1:
        menu = new CartMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 2:
        menu = new ShopMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
        break;
    case 3:
        menu = new MainMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
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
    system("clear");
    menu->draw(accounts, products);
    delete menu;
}

void RemoveUserMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    uint64_t id;
    std::cout << "ID of user to be deleted: ";
    std::cin >> id;
    accounts.remove_user(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products);
    delete menu;
}

void AddProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    std::string name;
    uint64_t id;
    uint32_t price;

    uint16_t weight;
    uint16_t height;
    uint16_t nms;
    uint16_t tdp;
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
    menu->draw(accounts, products);
    delete menu;
}

void RemoveProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    uint64_t id;
    std::cout << "ID of product to be deleted: ";
    std::cin >> id;
    products.remove_product(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products);
    delete menu;
}

void MakeAdminMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    uint64_t id;
    std::cout << "ID of user to be promoted to ADMIN: ";
    std::cin >> id;
    accounts.make_admin(id);
    Menu* menu = new AdminMenu;
    system("clear");
    menu->draw(accounts, products);
    delete menu;
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
        system("clear");
        menu->draw(accounts, products);   
        delete menu;
        break;
    case 2:
        menu = new SignupMenu;
        system("clear");
        menu->draw(accounts, products);
        delete menu;
    case 3:
        return;
        break;
    
    default:
        break;
    }
}

void CartMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    Account acc = accounts.get_user_by_id(accounts.logged_user_id);
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
        menu->draw(accounts, products);
        delete menu;
    }
    else {
        size_t index = 0;
        if(cart.size() < 10) {
            for(; index < cart.size(); index++) {
                std::cout << index + 1 << ") " << products.get_product_by_id(cart[index]).name << '\n';
            }
            std::string option;
            std::cout << "\nType a number to select the desired product to buy or 0 to buy them all or E to exit the shop: ";
            std::cin >> option;

            Menu* menu;
            if(option == "E") {
                menu = new UserMenu;
                system("clear");
                menu->draw(accounts, products);
                delete menu;
            } 
            else if(option == "0") {
                for(size_t i = 0; i < cart.size(); i++) {
                    acc.cart.remove_product(cart[i]);
                }
                menu = new UserMenu;
                system("clear");
                menu->draw(accounts, products);
                delete menu;
            }

            acc.cart.remove_product(cart[std::stoi(option) - 1]);
            menu = new UserMenu;
            system("clear");
            menu->draw(accounts, products);
            delete menu;
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
            std::string option;
            std::cout << "\nType a number to select the desired product to buy or 0 to buy them all or B to select another page or E to exit the shop: ";
            std::cin >> option;

            Menu* menu;

            if(option == "E") {
                menu = new UserMenu;
                system("clear");
                menu->draw(accounts, products);
                delete menu;
            } 
            else if(option == "B") {
                menu = new ShopMenu;
                system("clear");
                menu->draw(accounts, products);
                delete menu;
            }
            else if(option == "0") {
                for(size_t i = 0; i < cart.size(); i++) {
                    acc.cart.remove_product(cart[i]);
                }
                menu = new UserMenu;
                system("clear");
                menu->draw(accounts, products);
                delete menu;
            }

            acc.cart.remove_product(cart[std::stoi(option) - 1]);
            menu = new UserMenu;
            system("clear");
            menu->draw(accounts, products);
            delete menu;
        }
    }
}

void ShopMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    size_t index = 0;
    Menu* menu;
    std::string filter;
    std::cout << "Available filters: none, type, name, price, weight, height, nms, tdp, memory, clock, cores, threads, socket, vertical, horizontal, tech.\n";
    std::cout << "Select a filter: ";
    std::cin >> filter;
    std::vector<Product> prod;
    if(filter == "none") {
        prod = products.get_products();
    }
    if(filter == "type") {
        std::string type;
        std::cout << "\nType to be filtered: ";
        std::cin >> type;
        if(type == "CPU")
            prod = products.get_products_with_type(ProductType::CPU);
        if(type == "GPU")
            prod = products.get_products_with_type(ProductType::GPU); 
        if(type == "APU")
            prod = products.get_products_with_type(ProductType::APU);
    }
    if(filter == "price") {
        uint32_t price;
        std::cout << "\nPrice to be filtered: ";
        std::cin >> price;
        prod = products.get_products_with_price(price);
    }
    if(filter == "weight") {
        uint16_t weight;
        std::cout << "\nWeight to be filtered: ";
        std::cin >> weight;
        prod = products.get_products_with_weight(weight);
    }
    if(filter == "height") {
        uint16_t height;
        std::cout << "\nHeight to be filtered: ";
        std::cin >> height;
        prod = products.get_products_with_height(height);
    }
    if(filter == "nms") {
        uint16_t nms;
        std::cout << "\nnms to be filtered: ";
        std::cin >> nms;
        prod = products.get_products_with_nms(nms);
    }
    if(filter == "tdp") {
        uint16_t tdp;
        std::cout << "\ntdp to be filtered: ";
        std::cin >> tdp;
        prod = products.get_products_with_tdp(tdp);
    }
    if(filter == "memory") {
        uint32_t memory;
        std::cout << "\nMemory to be filtered: ";
        std::cin >> memory;
        prod = products.get_products_with_memory(memory);
    }
    if(filter == "clock") {
        uint32_t clock;
        std::cout << "\nClock to be filtered: ";
        std::cin >> clock;
        prod = products.get_products_with_clock(clock);
    }
    if(filter == "cores") {
        uint16_t cores;
        std::cout << "\nCores to be filtered: ";
        std::cin >> cores;
        prod = products.get_products_with_cores(cores);
    }
    if(filter == "threads") {
        uint32_t threads;
        std::cout << "\nThreads to be filtered: ";
        std::cin >> threads;
        prod = products.get_products_with_threads(threads);
    }
    if(filter == "socket") {
        std::string socket;
        std::cout << "\nSocket to be filtered: ";
        std::cin >> socket;
        prod = products.get_products_with_socket(socket);
    }
    if(filter == "vertical") {
        uint32_t vert;
        std::cout << "\nMaximum vertical resolution to be filtered: ";
        std::cin >> vert;
        prod = products.get_products_with_max_vert_res(vert);
    }
    if(filter == "horizontal") {
        uint32_t hor;
        std::cout << "\nMaximum horizontal resolution to be filtered: ";
        std::cin >> hor;
        prod = products.get_products_with_max_hor_res(hor);
    }
    if(filter == "tech") {
        std::string tech;
        std::cout << "\nSupported technologies to be filtered: ";
        std::cin >> tech;
        if(tech == "OpenGL")
            prod = products.get_products_with_tech(SupportedTechnologies::OpenGL);
        if(tech == "DirectX")
            prod = products.get_products_with_tech(SupportedTechnologies::DirectX); 
        if(tech == "Vulkan")
            prod = products.get_products_with_tech(SupportedTechnologies::Vulkan);
        if(tech == "OpenGL&Vulkan")
            prod = products.get_products_with_tech(SupportedTechnologies::OpenGL_Vulkan);
        if(tech == "OpenGL&DirectX")
            prod = products.get_products_with_tech(SupportedTechnologies::OpenGL_DirectX); 
        if(tech == "Vulkan&DirectX")
            prod = products.get_products_with_tech(SupportedTechnologies::Vulkan_DirectX);
        if(tech == "OpenGL&Vulkan&DirectX")
            prod = products.get_products_with_tech(SupportedTechnologies::OpenGL_Vulkan_DirectX);
    }
    //select filter
    if(prod.size() < 10) {
        for(; index < prod.size(); index++) {
            std::cout << index + 1 << ") " << prod[index].name << '\n';
        }
        std::string option;
        std::cout << "\nType a number to select the desired product or E to exit the shop: ";
        std::cin >> option;

        Menu* menu;
        if(option == "E") {
            menu = new UserMenu;
            menu->draw(accounts, products);
            delete menu;
        } 
        else {
            products.selected_product_id = prod[std::stoi(option) - 1].id;
            menu = new ViewProductMenu;
            menu->draw(accounts, products);
            delete menu;
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
        std::string option;
        std::cout << "\nType a number to select the desired product or type B to select another page or E to exit the shop: ";
        std::cin >> option;

        if(option == "E") {
            menu = new UserMenu;
            system("clear");
            menu->draw(accounts, products);
            delete menu;
        } 
        else if(option == "B") {
            menu = new ShopMenu;
            system("clear");
            menu->draw(accounts, products);
            delete menu;
        }
        else {
            products.selected_product_id = prod[std::stoi(option) - 1].id;
            Account& acc = accounts.get_user_by_id(accounts.logged_user_id);
            menu = new ViewProductMenu;
            system("clear");
            menu->draw(accounts, products);
            delete menu;
        }
    }
}

void ViewProductMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    Product prod = products.get_product_by_id(products.selected_product_id);
    
    std::cout << "Name of the product: " << prod.name << '\n';
    std::cout << "Price of the product: " << prod.price << '\n';

    if(prod.type == ProductType::CPU) {
        std::cout << "Type of the product: CPU\n";

        std::cout << "weight: " << prod.cpu->get_weight() << '\n';
        std::cout << "height: " <<  prod.cpu->get_height() << '\n';
        std::cout << "nms: " << prod.cpu->get_nms() << '\n';
        std::cout << "tdp: " << prod.cpu->get_tdp() << '\n';
        std::cout << "memory: " << prod.cpu->get_memory() << '\n';
        std::cout << "clock: " << prod.cpu->get_clock() << '\n';

        std::cout << "cores: " << prod.cpu->get_cores() << '\n';
        std::cout << "threads: " << prod.cpu->get_threads() << '\n';
        std::cout << "socket: " << prod.cpu->get_socket() << '\n';

    }
    if(prod.type == ProductType::GPU) {
        std::cout << "Type of the product: GPU\n";

        std::cout << "weight: " << prod.gpu->get_weight() << '\n';
        std::cout << "height: " <<  prod.gpu->get_height() << '\n';
        std::cout << "nms: " << prod.gpu->get_nms() << '\n';
        std::cout << "tdp: " << prod.gpu->get_tdp() << '\n';
        std::cout << "memory: " << prod.gpu->get_memory() << '\n';
        std::cout << "clock: " << prod.gpu->get_clock() << '\n';

        std::cout << "max horizontal resolution: " << prod.gpu->get_max_horizontal_res() << '\n';
        std::cout << "max vertical resolution: " << prod.gpu->get_max_vertical_res() << '\n';
        std::cout << "Supported Technologies: ";

        switch(prod.gpu->get_supported_tech()) {
            case SupportedTechnologies::OpenGL:
                std::cout << "OpenGL";
                break;
            case SupportedTechnologies::Vulkan:
                std::cout << "Vulkan";
                break;
            case SupportedTechnologies::DirectX:
                std::cout << "DirectX";
                break;
            case SupportedTechnologies::OpenGL_Vulkan:
                std::cout << "OpenGL & Vulkan";
                break;
            case SupportedTechnologies::OpenGL_DirectX:
                std::cout << "OpenGL & DirectX";
                break;
            case SupportedTechnologies::OpenGL_Vulkan_DirectX:
                std::cout << "OpenGL & Vulkan & DirectX";
                break;          
        }
    }
    if(prod.type == ProductType::APU) {
        std::cout << "Type of the product: APU\n";

        std::cout << "weight: " << prod.apu->CPU::get_weight() << '\n';
        std::cout << "height: " <<  prod.apu->CPU::get_height() << '\n';
        std::cout << "nms: " << prod.apu->CPU::get_nms() << '\n';
        std::cout << "tdp: " << prod.apu->CPU::get_tdp() << '\n';
        std::cout << "memory: " << prod.apu->CPU::get_memory() << '\n';
        std::cout << "clock: " << prod.apu->CPU::get_clock() << '\n';

        std::cout << "cores: " << prod.apu->get_cores() << '\n';
        std::cout << "threads: " << prod.apu->get_threads() << '\n';
        std::cout << "socket: " << prod.apu->get_socket() << '\n';

        std::cout << "max horizontal resolution: " << prod.apu->get_max_horizontal_res() << '\n';
        std::cout << "max vertical resolution: " << prod.apu->get_max_vertical_res() << '\n';
        std::cout << "Supported Technologies: ";

        switch(prod.apu->get_supported_tech()) {
            case SupportedTechnologies::OpenGL:
                std::cout << "OpenGL";
                break;
            case SupportedTechnologies::Vulkan:
                std::cout << "Vulkan";
                break;
            case SupportedTechnologies::DirectX:
                std::cout << "DirectX";
                break;
            case SupportedTechnologies::OpenGL_Vulkan:
                std::cout << "OpenGL & Vulkan";
                break;
            case SupportedTechnologies::OpenGL_DirectX:
                std::cout << "OpenGL & DirectX";
                break;
            case SupportedTechnologies::OpenGL_Vulkan_DirectX:
                std::cout << "OpenGL & Vulkan & DirectX";
                break;          
        }
    }
    bool option;
    std::cout << "\n\nType 1 if you want to put this product in the shopping cart or 0 to leave: ";
    std::cin >> option;
    if(option) {
        Account acc = accounts.get_user_by_id(accounts.logged_user_id);
        acc.cart.add_product(products.selected_product_id);
    }
    Menu* menu = new ShopMenu;
    system("clear");
    menu->draw(accounts, products);
    delete menu;
}

void SignupMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
    std::string user, pass;
    std::cout << "user: ";
    std::cin >> user;
    std::cout << "pass: ";
    std::cin >> pass;

    accounts.add_user(user, pass, AccountType::User);
    std::cout << "Your account has been succcesfully created, you may login now.\n\n";

    Menu* menu = new UserMenu;
    
    accounts.logged_user_id = accounts.get_users_by_name(user)[0].id;
    menu->draw(accounts, products);
    delete menu;
}

void LoginMenu::draw(AccountDatabase& accounts, ProductDatabase& products) {
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
        menu->draw(accounts, products);
        delete menu;
        break;
    case AccountType::User:
        system("clear");
        menu = new UserMenu;
        system("clear");
        accounts.logged_user_id = a.id;
        menu->draw(accounts, products);
        delete menu;
        break;

    case AccountType::Admin:
        system("clear");
        menu = new AdminMenu;
        system("clear");
        accounts.logged_user_id = a.id;
        menu->draw(accounts, products);
        delete menu;
        break;

    default:
        break;
    }
}