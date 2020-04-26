#ifndef CHIP8_ROMLOADER_H
#define CHIP8_ROMLOADER_H

#include <string>
#include <vector>

class RomLoader {

public:
    explicit RomLoader(const std::string& fileName);

    std::vector<uint8_t> load();

private:
    std::string fileName;

};

#endif //CHIP8_ROMLOADER_H
