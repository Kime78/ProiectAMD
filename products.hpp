#pragma once

#include <string>
#include <vector>

class Chip {
protected:
    double weight;
    double height;
    uint8_t nms;
    double tdp;
    uint32_t memory;
    uint32_t clock;

public:
    Chip() = default;
    inline void set_weight(double weight) {
        this->weight = weight;
    }
    inline void set_height(double height) {
        this->height = height;
    }
    inline void set_nms(uint8_t nms) {
        this->nms = nms;
    }
    inline void set_tdp(double tdp) {
        this->tdp = tdp;
    }
    inline void set_memory(uint32_t memory) {
        this->memory = memory;
    }
    inline void set_clock(uint32_t clock) {
        this->clock = clock;
    }

    inline double get_weight() {
        return this->weight;
    }
    inline double get_height() {
        return this->height;
    }
    inline uint8_t get_nms() {
        return this->nms;
    }
    inline double get_tdp() {
        return this->tdp;
    }
    inline uint32_t get_memory() {
        return this->memory;
    }
    inline uint32_t get_clock() {
        return this->clock;
    }
};

class CPU : public Chip {
protected:
    uint16_t cores;
    uint16_t threads;
    std::string socket;
public:
    CPU() = default;
    CPU(uint16_t cores, uint16_t threads, std::string socket);
    inline void set_cores(uint16_t cores) {
        this->cores = cores; 
    }

    inline void set_threads(uint16_t threads) {
        this->threads = threads; 
    }

    inline void set_socket(std::string socket) {
        this->socket = socket; 
    }

    inline uint16_t get_cores() {
        return this->cores;
    }
    inline uint16_t get_threads() {
        return this->threads;
    }
    inline std::string get_socket() {
        return this->socket;
    }
};

enum class SupportedTechnologies {
        OpenGL, Vulkan, DirectX, OpenGL_Vulkan, OpenGL_DirectX, Vulkan_DirectX, OpenGL_Vulkan_DirectX
};
class GPU : public Chip {
protected:
    uint32_t max_vertical_res;
    uint32_t max_horizontal_res;
    SupportedTechnologies supported_tech;
public:
    GPU() = default;
    GPU(uint32_t max_vertical_res, uint32_t max_horizontal_res, SupportedTechnologies supported_tech);

    inline void set_max_vertical_res(uint32_t max_vertical_res) {
        this->max_vertical_res = max_vertical_res; 
    }

    inline void set_max_horizontal_res(uint32_t max_horizontal_res) {
        this->max_horizontal_res = max_horizontal_res; 
    }

    inline void set_supported_tech(SupportedTechnologies supported_tech) {
        this->supported_tech = supported_tech; 
    }

    inline double get_max_vertical_res() {
        return this->max_vertical_res;
    }
    inline uint32_t get_max_horizontal_res() {
        return this->max_horizontal_res;
    }
    inline SupportedTechnologies get_supported_tech() {
        return this->supported_tech;
    }
};

class APU : public CPU, public GPU {
public:
APU() = default;
};

enum class ProductType {
    GPU, CPU, APU
};
struct Product {
    std::string name;
    uint32_t price;
    uint64_t id;
    ProductType type;
    APU* apu;
    CPU* cpu;
    GPU* gpu;

    Product(std::string name, uint32_t price) {
        this->name = name;
        this->price = price;
        this->id = random();
    }
};

struct ProductDatabase {
private:
    std::vector<Product> product_database;
public:
    uint64_t selected_product_id = 0;
    Product get_product_by_id(uint64_t id);
    void add_product(Product prod);
    void remove_product(uint64_t id);
    void load_products_from_file();
    const std::vector<Product> get_products();
    const std::vector<Product> get_products_with_type(ProductType type);
    
    //to be filled with all filters...
};