#include <fstream>
#include <iostream>

#include "RomLoader.h"

RomLoader::RomLoader(const std::string& fileName) {
    this->fileName = fileName;
}

std::vector<uint8_t> RomLoader::load() {
    std::ifstream stream(fileName, std::ifstream::binary);

    if (!stream.is_open()) {
        std::cerr << "Failed to open rom: " << fileName << std::endl;
        return std::vector<uint8_t>();
    }

    stream.seekg(0, std::ios::end);
    int size = stream.tellg();

    std::vector<uint8_t> buffer(size);

    stream.seekg (0, std::ios::beg);
    stream.read(reinterpret_cast<char *>(&buffer[0]), size);
    stream.close();

    return buffer;
}
