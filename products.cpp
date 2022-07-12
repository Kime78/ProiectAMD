#include "products.hpp"
#include <fstream>
#include <algorithm>

CPU::CPU(uint16_t cores, uint16_t threads, std::string socket) {
    this->cores = cores;
    this->threads = threads;
    this->socket = socket;
}
GPU::GPU(uint32_t max_vertical_res, uint32_t max_horizontal_res, SupportedTechnologies supported_tech) {
    this->max_vertical_res = max_vertical_res;
    this->max_horizontal_res = max_horizontal_res;
    this->supported_tech = supported_tech;
}

Product ProductDatabase::get_product_by_id(uint64_t id) {
    for(size_t i = 0; i < product_database.size(); i++) {
        if(product_database[i].id == id) {
            return product_database[i];
        }
    }
    return Product("", 0);
}

void ProductDatabase::add_product(Product prod) { //to be worked on :(
    //https://stackoverflow.com/questions/6932409/writing-a-string-to-the-end-of-a-file-c
    std::ofstream products;
    products.open("./.secrets/products.txt", std::ios::app);

    products << prod.id << "\t" << prod.name << "\t" << prod.price << "\t";
    
    switch (prod.type) {
    case ProductType::CPU:
        products << prod.cpu->get_weight() << "\t" << prod.cpu->get_height() << "\t" << prod.cpu->get_nms() << "\t" << prod.cpu->get_tdp() << "\t" << prod.cpu->get_memory() << "\t" << prod.cpu->get_clock() << "\tCPU\t";
        products << prod.cpu->get_cores() << "\t" << prod.cpu->get_threads() << "\t" << prod.cpu->get_socket() << '\n';
        break;
    case ProductType::GPU:
        products << prod.gpu->get_weight() << "\t" << prod.gpu->get_height() << "\t" << prod.gpu->get_nms() << "\t" << prod.gpu->get_tdp() << "\t" << prod.gpu->get_memory() << "\t" << prod.gpu->get_clock() << "\tGPU\t";
        products << prod.gpu->get_max_horizontal_res() << "\t" << prod.gpu->get_max_vertical_res() << "\t";
        switch (prod.gpu->get_supported_tech())
        {
        case SupportedTechnologies::OpenGL:
            products << "OpenGL\n";
            break;
        case SupportedTechnologies::DirectX:
            products << "DirectX\n";
            break;
        case SupportedTechnologies::Vulkan:
            products << "Vulkan\n";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            products << "OpenGL & DirectX\n";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            products << "OpenGL & Vulkan\n";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            products << "Vulkan & DirectX\n";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            products << "OpenGL & Vulkan & DirectX\n";
            break;
        
        default:
            break;
        }
        break;
    case ProductType::APU:
        products << prod.apu->CPU::get_weight() << "\t" << prod.apu->CPU::get_height() << "\t" << prod.apu->CPU::get_nms() << "\t" << prod.apu->CPU::get_tdp() << "\t" << prod.apu->CPU::get_memory() << "\t" << prod.apu->CPU::get_clock() << "\tAPU\t";
        products << prod.apu->get_cores() << "\t" << prod.apu->get_threads() << "\t" << prod.apu->get_socket() << "\t";
        products << prod.apu->get_max_horizontal_res() << "\t" << prod.apu->get_max_vertical_res() << "\t";
        switch (prod.apu->get_supported_tech()) {
        case SupportedTechnologies::OpenGL:
            products << "OpenGL\n";
            break;
        case SupportedTechnologies::DirectX:
            products << "DirectX\n";
            break;
        case SupportedTechnologies::Vulkan:
            products << "Vulkan\n";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            products << "OpenGL & DirectX\n";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            products << "OpenGL & Vulkan\n";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            products << "Vulkan & DirectX\n";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            products << "OpenGL & Vulkan & DirectX\n";
            break;
        
        default:
            break;
        }
        break;
    default:
        break;
    } 
    product_database.push_back(Product(prod));
}
void ProductDatabase::load_products_from_file() { //to be worked on :(
    std::ifstream product_file("./.secrets/products.txt");

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

    while(product_file >> id >> name >> price >> weight >> height >> nms >> tdp >> memory >> clock >> type) {
        if(type == "CPU") {
            product_file >> cores;
            product_file >> threads;
            product_file >> socket;

            Product* prod = new Product(name, price);
            
            prod->cpu = new CPU(cores, threads, socket);
            prod->cpu->set_weight(weight);
            prod->cpu->set_height(height);
            prod->cpu->set_nms(nms);
            prod->cpu->set_tdp(tdp);
            prod->cpu->set_memory(memory);
            prod->cpu->set_clock(clock);

            prod->type = ProductType::CPU;
            prod->id = id;
            prod->name = name;

            product_database.push_back(*prod);

            delete prod;
        }
        if(type == "GPU") {
            product_file >> max_horizontal_res;
            product_file >> max_vertical_res;
            product_file >> tech;

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
            prod->gpu = new GPU(max_vertical_res, max_horizontal_res, s_tech);
            prod->gpu->set_weight(weight);
            prod->gpu->set_height(height);
            prod->gpu->set_nms(nms);
            prod->gpu->set_tdp(tdp);
            prod->gpu->set_memory(memory);
            prod->gpu->set_clock(clock);

            prod->type = ProductType::GPU;
            prod->id = id;
            prod->name = name;

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
            prod->id = id;
            prod->name = name;

            product_database.push_back(*prod);

            delete prod;
        }
    }
}

void ProductDatabase::remove_product(uint64_t id) {
    std::ifstream in("./.secrets/products.txt");
    std::ofstream out("./.secrets/temp.txt");
    std::string line;
    std::string delete_line;
    Product prod = get_product_by_id(id);
    delete_line = std::to_string(prod.id) + "\t" + prod.name + "\t" + std::to_string(prod.price) + "\t";  
    if(prod.type == ProductType::CPU) {
        delete_line += std::to_string(prod.cpu->get_weight()) + "\t" + std::to_string(prod.cpu->get_height()) + "\t" + std::to_string(prod.cpu->get_nms()) + "\t" + std::to_string(prod.cpu->get_tdp()) + "\t" + std::to_string(prod.cpu->get_memory()) + "\t" + std::to_string(prod.cpu->get_clock()) + "\tCPU\t";
        delete_line += std::to_string(prod.cpu->get_cores()) + "\t" + std::to_string(prod.cpu->get_threads()) + "\t" + prod.cpu->get_socket();
        delete prod.cpu;
    }
    else if(prod.type == ProductType::GPU) {
        delete_line += std::to_string(prod.gpu->get_weight()) + "\t" + std::to_string(prod.gpu->get_height()) + "\t" + std::to_string(prod.gpu->get_nms()) + "\t" + std::to_string(prod.gpu->get_tdp()) + "\t" + std::to_string(prod.gpu->get_memory()) + "\t" + std::to_string(prod.gpu->get_clock()) + "\tGPU\t";
        delete_line += std::to_string(prod.gpu->get_max_horizontal_res()) + "\t" + std::to_string(prod.gpu->get_max_vertical_res()) + "\t";
        switch (prod.gpu->get_supported_tech()) {
        case SupportedTechnologies::OpenGL:
            delete_line += "OpenGL";
            break;
        case SupportedTechnologies::DirectX:
            delete_line += "DirectX";
            break;
        case SupportedTechnologies::Vulkan:
            delete_line += "Vulkan";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            delete_line += "OpenGL & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            delete_line += "OpenGL & Vulkan";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            delete_line += "Vulkan & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            delete_line += "OpenGL & Vulkan & DirectX";
            break;
        
        default:
            break;
        }
        delete prod.gpu;
    }
    else if(prod.type == ProductType::APU) {
        delete_line += std::to_string(prod.apu->CPU::get_weight()) + "\t" + std::to_string(prod.apu->CPU::get_height()) + "\t" + std::to_string(prod.apu->CPU::get_nms()) + "\t" + std::to_string(prod.apu->CPU::get_tdp()) + "\t" + std::to_string(prod.apu->CPU::get_memory()) + "\t" + std::to_string(prod.apu->CPU::get_clock()) + "\tAPU\t";
        delete_line += std::to_string(prod.apu->get_cores()) + "\t" + std::to_string(prod.apu->get_threads()) + "\t" + prod.apu->get_socket() + "\t";
        delete_line += std::to_string(prod.apu->get_max_horizontal_res()) + "\t" + std::to_string(prod.apu->get_max_vertical_res()) + "\t";
        switch (prod.apu->get_supported_tech())
        {
        case SupportedTechnologies::OpenGL:
            delete_line += "OpenGL";
            break;
        case SupportedTechnologies::DirectX:
            delete_line += "DirectX";
            break;
        case SupportedTechnologies::Vulkan:
            delete_line += "Vulkan";
            break;
        case SupportedTechnologies::OpenGL_DirectX:
            delete_line += "OpenGL & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan:
            delete_line += "OpenGL & Vulkan";
            break;
        case SupportedTechnologies::Vulkan_DirectX:
            delete_line += "Vulkan & DirectX";
            break;
        case SupportedTechnologies::OpenGL_Vulkan_DirectX:
            delete_line += "OpenGL & Vulkan & DirectX";
            break;
        
        default:
            break;
        }
        delete prod.apu;
    }
    const Product p = prod;
    while (getline(in, line)) {
        if(line != delete_line)
            out << line << std::endl;
    }

    std::remove("./.secrets/products.txt");
    std::rename("./.secrets/temp.txt", "./.secrets/products.txt");

    for(auto i = product_database.begin(); i != product_database.end(); i++) {
        if((*i).id == id) {
            product_database.erase(i);
            break;
        }
    }
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
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_price(uint32_t price) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        if(product_database[i].price == price)
            ret.push_back(product_database[i]);
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_weight(uint16_t weight) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_weight() == weight)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_weight() == weight)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_weight() == weight)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_height(uint16_t height) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_height() == height)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_height() == height)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_height() == height)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_nms(uint16_t nms) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_nms() == nms)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_nms() == nms)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_nms() == nms)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_tdp(uint16_t tdp) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_tdp() == tdp)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_tdp() == tdp)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_tdp() == tdp)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_memory(uint32_t memory) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_memory() == memory)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_memory() == memory)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_memory() == memory)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_clock(uint32_t clock) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_clock() == clock)
                ret.push_back(product_database[i]);
            break;
        case ProductType::GPU:
            if(product_database[i].gpu->get_clock() == clock)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_clock() == clock)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_cores(uint16_t cores) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_cores() == cores)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_cores() == cores)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_threads(uint16_t threads) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_threads() == threads)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_threads() == threads)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_socket(std::string socket) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::CPU:
            if(product_database[i].cpu->get_socket() == socket)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->CPU::get_socket() == socket)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_max_vert_res(uint32_t max_vertical_res) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::GPU:
            if(product_database[i].gpu->get_max_vertical_res() == max_vertical_res)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->get_max_vertical_res() == max_vertical_res)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_max_hor_res(uint32_t max_horizontal_res) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::GPU:
            if(product_database[i].gpu->get_max_horizontal_res() == max_horizontal_res)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->get_max_horizontal_res() == max_horizontal_res)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}

const std::vector<Product> ProductDatabase::get_products_with_tech(SupportedTechnologies tech) {
    std::vector<Product> ret;
    for(size_t i = 0; i < product_database.size(); i++) {
        switch (product_database[i].type)
        {
        case ProductType::GPU:
            if(product_database[i].gpu->get_supported_tech() == tech)
                ret.push_back(product_database[i]);
            break;
        case ProductType::APU:
            if(product_database[i].apu->get_supported_tech() == tech)
                ret.push_back(product_database[i]);
            break;
        default:
            break;
        }
    }
    return ret;
}