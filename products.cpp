#include "products.hpp"
#include <fstream>
#include <algorithm>

Product ProductDatabase::get_product_by_id(uint64_t id) {
    for(size_t i = 0; i < product_database.size(); i++) {
        if(product_database[i].id == id) {
            return product_database[i];
        }
    }
    return Product(NULL);
}

void ProductDatabase::add_product(Product prod) { //to be worked on :(
    //https://stackoverflow.com/questions/6932409/writing-a-string-to-the-end-of-a-file-c
    std::ofstream products;
    products.open("./.secrets/products.txt", std::ios::app);
    // for(size_t i = 0; i < product_database.size(); i++) {
    //     if(product_database[i] == prod) //an product cannot be added twice
    //         return;
    // }
    // if(type == AccountType::User)
    //     products << '\n' << user << "\t" << pass << "\t" << "User" << '\n';
    // else
    //     products << '\n' << user << "\t" << pass << "\t" << "Admin" << '\n';
    product_database.push_back(Product(prod));
}

void load_products_from_file() { //to be worked on :(

}

void ProductDatabase::remove_product(uint64_t id) {
    //todo: remove from file
    //product_database.erase(std::remove(product_database.begin(), product_database.end(), id), product_database.end());
}

const std::vector<Product> ProductDatabase::get_products() {
    return product_database;
}

const std::vector<Product> ProductDatabase::get_products_with_type(ProductType type) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        if(product_database[i].type == type)
            ret.push_back(product_database[i]);
    }

    return product_database;
}