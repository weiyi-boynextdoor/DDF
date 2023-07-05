#include "file_utils.h"

#include <fstream>
#include <stdexcept>

namespace DDF {
std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }
    auto fileSize = file.tellg();

    std::string data;
    data.resize(fileSize);
    file.seekg(0);
    file.read(data.data(), fileSize);
    return data;
}
} // namespace DDF
