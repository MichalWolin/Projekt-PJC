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
void addPassword(const std::string& path);

int main() {
    auto path = getPath();

    while(true){
        fmt::print("\nChoose one of the options below:\n"
                   "1 -> Find password\n"
                   "2 -> Sort password\n"
                   "3 -> Add password\n"
                   "4 -> Edit password\n"
                   "5 -> Remove password\n"
                   "6 -> Add category\n"
                   "7 -> Remove category\n");
        int option;
        std::cin >> option;

        while(option < 1 || option > 7){
            fmt::print("Invalid option! Try again:\n");
            std::cin >> option;
        }

        switch(option){
            case 1:
                fmt::print("not yet implemented lol");
                break;
            case 2:
                fmt::print("not yet implemented lol");
                break;
            case 3:
                addPassword(path);
                break;
            case 4:
                fmt::print("not yet implemented lol");
                break;
            case 5:
                fmt::print("not yet implemented lol");
                break;
            case 6:
                fmt::print("not yet implemented lol");
                break;
            case 7:
                fmt::print("not yet implemented lol");
                break;
        }
    }
}

/**
 * @brief Returns path to the file
 *
 * This function returns the path to the file either in this folder or an absolute path to the file.
 *
 * @param option Stores the option entered by the user.
 */
std::string getPath(){
    fmt::print("To choose from existing file in this directory type 1, to enter an absolute path type 2:\n");
    int option;
    std::cin >> option;

    while(option < 1 || option > 2){
        fmt::print("Incorrect option! Type 1 for existing file or type 2 to enter an absolute path:\n");
        std::cin >> option;
    }

    if(option == 1){
        fmt::print("\nChoose file from this directory (type g.e. 1)\n***\n");
        auto dirIter = std::filesystem::directory_iterator("..");
        int fileIter = 1;
        std::vector<std::string> paths;
        for (auto const &entry: dirIter){
            if(entry.is_regular_file() && entry.path() != "..\\CMakeLists.txt"
            && entry.path() != "..\\main.cpp" && entry.path() != "..\\.gitignore") {
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

void addPassword(const std::string& path){
    auto vault = std::fstream(path, std::ios::in);
    std::string line, word;
    std::getline(vault, line);

    vault = std::fstream(path, std::ios::out | std::ios::app);
    std::string input;
    fmt::print("\nName of password (e.g. password to twitter account):\n");
    std::cin >> input;
    vault << input + " ";

    fmt::print("\nDo you want to have password generated? (yes/no):\n");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::print("\nInvalid input! Try again:\n");
        std::cin >> input;
    }
    if(input == "yes"){
        fmt::print("not yet implemented");
    }else{
        fmt::print("\nPassword:\n");
        std::cin >> input;
        vault << input + " ";
    }

}