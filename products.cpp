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

    products << prod.id << " " << prod.price;

    switch (prod.type)
    {
    case ProductType::CPU:
        products << prod.prod_cpu.get_weight() << "\t" << prod.prod_cpu.get_height() << "\t" << prod.prod_cpu.get_nms() << "\t" << prod.prod_cpu.get_tdp() << "\t" << prod.prod_cpu.get_memory() << "\t" << prod.prod_cpu.get_clock() << "\tCPU\t";
        products << prod.prod_cpu.get_cores() << "\t" << prod.prod_cpu.get_threads() << "\t" << prod.prod_cpu.get_socket();
        break;
    case ProductType::GPU:
        products << prod.prod_cpu.get_weight() << "\t" << prod.prod_cpu.get_height() << "\t" << prod.prod_cpu.get_nms() << "\t" << prod.prod_cpu.get_tdp() << "\t" << prod.prod_cpu.get_memory() << "\t" << prod.prod_cpu.get_clock() << "\tGPU\t";
        products << prod.prod_gpu.get_max_horizontal_res() << "\t" << prod.prod_gpu.get_max_vertical_res() << "\t";
        switch (prod.prod_gpu.get_supported_tech())
        {
        case SupportedTechnologies::OpenGL:
            products << "OpenGL";
            break;
        case SupportedTechnologies::DirectX:
            products << "DirectX";
            break;
        case SupportedTechnologies::Vulkan:
            products << "Vulkan";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            products << "OpenGL & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            products << "OpenGL & Vulkan";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            products << "Vulkan & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            products << "OpenGL & Vulkan & DirectX";
            break;
        
        default:
            break;
        }
    case ProductType::APU:
        products << prod.prod_cpu.get_weight() << "\t" << prod.prod_cpu.get_height() << "\t" << prod.prod_cpu.get_nms() << "\t" << prod.prod_cpu.get_tdp() << "\t" << prod.prod_cpu.get_memory() << "\t" << prod.prod_cpu.get_clock() << "\tAPU\t";
        products << prod.prod_cpu.get_cores() << "\t" << prod.prod_cpu.get_threads() << "\t" << prod.prod_cpu.get_socket() << "\t";
        products << prod.prod_gpu.get_max_horizontal_res() << "\t" << prod.prod_gpu.get_max_vertical_res() << "\t";
        switch (prod.prod_gpu.get_supported_tech())
        {
        case SupportedTechnologies::OpenGL:
            products << "OpenGL";
            break;
        case SupportedTechnologies::DirectX:
            products << "DirectX";
            break;
        case SupportedTechnologies::Vulkan:
            products << "Vulkan";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            products << "OpenGL & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            products << "OpenGL & Vulkan";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            products << "Vulkan & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            products << "OpenGL & Vulkan & DirectX";
            break;
        
        default:
            break;
        }
    default:
        break;
    } 
    product_database.push_back(Product(prod));
}
void ProductDatabase::load_products_from_file() { //to be worked on :(
    std::ifstream product_file("./.secrets/products.txt");

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

    while(product_file >> weight >> height >> nms >> tdp >> memory >> clock >> type) {
        if(type == "CPU") {
            product_file >> cores;
            product_file >> threads;
            product_file >> socket;

            Product* prod= new Product(1000 + rand() % 3000);
            prod->prod_cpu = CPU(cores, threads, socket);
            prod->prod_cpu.set_weight(weight);
            prod->prod_cpu.set_height(height);
            prod->prod_cpu.set_nms(nms);
            prod->prod_cpu.set_tdp(tdp);
            prod->prod_cpu.set_memory(memory);
            prod->prod_cpu.set_clock(clock);

            product_database.push_back(*prod);

            delete prod;
        }
        if(type == "GPU") {
            product_file >> max_horizontal_res;
            product_file >> max_vertical_res;
            product_file >> tech;

            Product* prod= new Product(1000 + rand() % 3000);
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
            prod->prod_gpu = GPU(max_vertical_res, max_horizontal_res, s_tech);
            prod->prod_gpu.set_weight(weight);
            prod->prod_gpu.set_height(height);
            prod->prod_gpu.set_nms(nms);
            prod->prod_gpu.set_tdp(tdp);
            prod->prod_gpu.set_memory(memory);
            prod->prod_gpu.set_clock(clock);

            product_database.push_back(*prod);

            delete prod;
        }
        if(type == "APU") {
            product_file >> cores;
            product_file >> threads;
            product_file >> socket;

            product_file >> max_horizontal_res;
            product_file >> max_vertical_res;
            product_file >> tech;

            Product* prod= new Product(1000 + rand() % 3000);
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
            prod->prod_apu = APU();
            prod->prod_apu.CPU::set_weight(weight);
            prod->prod_apu.CPU::set_height(height);
            prod->prod_apu.CPU::set_nms(nms);
            prod->prod_apu.CPU::set_tdp(tdp);
            prod->prod_apu.CPU::set_memory(memory);
            prod->prod_apu.CPU::set_clock(clock);

            prod->prod_apu.set_cores(cores);
            prod->prod_apu.set_threads(cores);
            prod->prod_apu.set_socket(socket);
            
            prod->prod_apu.set_max_horizontal_res(max_horizontal_res);
            prod->prod_apu.set_max_vertical_res(max_vertical_res);
            prod->prod_apu.set_supported_tech(s_tech);

            product_database.push_back(*prod);

            delete prod;
        }
    }

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