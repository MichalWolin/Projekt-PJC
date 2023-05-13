#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fmt/ranges.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fmt/std.h>

std::string getPath();

int main() {
    auto path = getPath();

    fmt::print("Choose one of the options below:\n"
               "");

    return 0;
}

std::string getPath(){
    fmt::print("To choose from existing file in this directory type 1, to enter an absolute path type 2:\n");
    int option;
    std::cin >> option;

    while(option < 1 || option > 2){
        fmt::print("Incorrect option! Type 1 for existing file or type 2 to enter an absolute path:\n");
        std::cin >> option;
    }

    if(option == 1){
        fmt::print("Choose file from this directory (type g.e. 1)\n***\n");
        auto dirIter = std::filesystem::directory_iterator("..");
        int fileIter = 1;
        std::vector<std::string> paths;
        for (auto const &entry: dirIter){
            if(entry.is_regular_file() && entry.path() != "..\\CMakeLists.txt" && entry.path() != "..\\main.cpp") {
                fmt::print("Option no. {}: {}\n", fileIter++, entry.path());
                paths.push_back(entry.path().string());
            }
        }
        fmt::print("***\n");

        int fileNo;
        std::cin >> fileNo;

        while(fileNo < 1 || fileNo > fileIter){
            fmt::print("Incorrect file number! Try again:\n");
        }

        return paths.at(fileNo - 1);
    }else{
        fmt::print("Enter an absolute path to vault:\n");
        std::string path;
        std::cin >> path;
        return path;
    }
}