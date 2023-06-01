#include <string>
#include <fstream>
#include <fmt/std.h>

#include "sortPasswords.h"

void sortPasswords(const std::string& path) {
    auto vault = std::fstream(path);
    std::string line;
    while(std::getline(vault, line)){
        fmt::println("{}", line);
    }
}
