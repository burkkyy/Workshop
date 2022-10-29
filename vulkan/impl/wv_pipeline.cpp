#include "wv_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace wv{
WvPipeline::WvPipeline(const std::string& vert_filepath, const std::string& frag_filepath){
    create_graphics_pipline(vert_filepath, frag_filepath);
}

std::vector<char> WvPipeline::read_file(const std::string& filepath){
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if(!file.is_open()){
        throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t file_size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}

void WvPipeline::create_graphics_pipline(const std::string& vert_filepath, const std::string& frag_filepath){
    auto vert_code = read_file(vert_filepath);
    auto frag_code = read_file(frag_filepath);

    std::cout << "Vert shader code size: " << vert_code.size() << std::endl;
    std::cout << "Frag shader code size: " << frag_code.size() << std::endl;
}
}