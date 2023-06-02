#include <iostream>
#include <vector>
#include <string>
#include <fmt/core.h>
#include <filesystem>
#include <fmt/std.h>
#include <map>
#include <fstream>

#include "addCategory.h"
#include "addPassword.h"
#include "editPassword.h"
#include "findPassword.h"
#include "removeCategory.h"
#include "removePassword.h"
#include "sortPasswords.h"
#include "Password.h"


std::string getPath();
long masterKey();
std::vector<std::string> getCategories(const std::string& path, const long& key);
std::vector<Password> getPasswords(const std::string& path, const long& key);
void writeFile(const std::string& path, const std::vector<std::string>& categories,
               const std::vector<Password>& passwords, const long& key, const time_t& time);
std::string encrypt(const std::string& data, const long& key);
int countLines(const std::string& path);


/**
 * @brief Main function
 *
 * This function is the main function of the program.
 * It calls other functions to get the path to the file, master key, categories and passwords.
 * Then it asks the user to choose one of the options.
 * The program runs until the user chooses to exit.
 *
 * @param key Stores the master key.
 * @param path Stores the path to the file.
 * @param categories Stores the categories.
 * @param passwords Stores the passwords.
 * @param time Stores the time of opening the file
 */
int main() {
    fmt::println("USE THE SAME MASTER KEY EVERY TIME YOU RUN THE PROGRAM!");
    fmt::println("IF YOU USE DIFFERENT MASTER KEY, YOU WILL CORRUPT THE FILE!");
    fmt::println("EXIT THROUGH THE PROGRAM! OTHERWISE YOUR CHANGES WON'T BE SAVED!\n");

    auto key = masterKey();
    auto path = getPath();
    auto categories = getCategories(path, key);
    auto passwords = getPasswords(path, key);
    auto time = std::time(nullptr);
    bool isRunning = true;

    while(isRunning){
        fmt::println("\nChoose one of the options below:\n"
                   "1 -> Find password\n"
                   "2 -> Sort password\n"
                   "3 -> Add password\n"
                   "4 -> Edit password\n"
                   "5 -> Remove password\n"
                   "6 -> Add category\n"
                   "7 -> Remove category\n"
                   "0 -> Exit");
        int option;
        std::cin >> option;

        while(option < 0 || option > 7){
            fmt::println("Invalid option! Try again:");
            std::cin >> option;
        }

        switch(option){
            case 0:
                isRunning = false;
                writeFile(path, categories, passwords, key, time);
                break;
            case 1:
                findPassword(passwords, categories);
                break;
            case 2:
                sortPasswords(passwords);
                break;
            case 3:
                addPassword(passwords, categories);
                break;
            case 4:
                editPassword(passwords);
                break;
            case 5:
                removePassword(passwords);
                break;
            case 6:
                addCategory(categories);
                break;
            case 7:
                removeCategory(passwords, categories);
                break;
        }
    }
}



/**
 * @brief Returns path to the file
 *
 * This function returns the path to the file either in this folder or an absolute path to the file.
 * The user can choose from existing files in this directory or enter an absolute path.
 * If the user chooses to enter an absolute path, the function checks if the file exists.
 * If the file doesn't exist, the user is asked to enter the path again.
 *
 * @param option Stores the option entered by the user.
 */
std::string getPath(){
    fmt::println("To choose from existing file in this directory type 1, to enter an absolute path type 2:");
    int option;
    std::cin >> option;

    while(option < 1 || option > 2){
        fmt::println("Incorrect option! Type 1 for existing file or type 2 to enter an absolute path:");
        std::cin >> option;
    }

    if(option == 1){
        fmt::println("Choose file from this directory (type g.e. 1)\n***");
        auto dirIter = std::filesystem::directory_iterator("..");
        int fileIter = 1;
        std::vector<std::string> paths;
        for (auto const &entry: dirIter){
            if(entry.is_regular_file() && entry.path().extension() == ".vault") {
                fmt::println("Option no. {}: {}", fileIter++, entry.path());
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
        std::filesystem::path filePath(path);
        while(!std::filesystem::exists(filePath) || filePath.extension() != ".vault") {
            fmt::println("File doesn't exist or has an incorrect extension! Try again:");
            std::cin >> path;
        }

        return path;
    }
}

/**
 * @brief Returns master key
 *
 * This function returns the master key which is used to encrypt and decrypt passwords.
 * It is generated by multiplying the ASCII values of the characters of the master password.
 *
 * @param masterPassword Stores the master password entered by the user.
 * @param key Stores the master key.
 */
long masterKey(){
    std::string masterPassword;
    fmt::println("Enter your master password:");
    std::cin >> masterPassword;
    long key = 1;
    for (int i = 0; i < masterPassword.size(); ++i) {
        key *= masterPassword.at(0);
    }
    return key;
}

std::vector<std::string> getCategories(const std::string& path, const long& key){
    std::vector<std::string> categories;

    auto vault = std::fstream(path, std::ios::in);
    std::string line;
    if(std::getline(vault, line)){
        std::stringstream ss(line);
        std::string category;
        while(std::getline(ss, category, ':')){
            categories.push_back(encrypt(category, key));
        }
    }
    vault.close();

    return categories;
}

std::vector<Password> getPasswords(const std::string& path, const long& key) {
    std::vector<Password> passwords;

    auto vault = std::fstream(path, std::ios::in);
    std::string line;
    std::getline(vault, line);

    auto lineCounter = countLines(path);
    int currentLine = 1;

    while(std::getline(vault, line)) {
        std::stringstream ss(line);
        std::string name, password, webpage, login, category;
        std::map<std::string, std::string> categories;
        std::getline(ss, name, ':');
        if(currentLine == 1 || currentLine == (lineCounter / 2) + 1 || currentLine == lineCounter){
            std::getline(ss, name, ':');
        }
        std::getline(ss, password, ':');
        std::getline(ss, webpage, ':');
        std::getline(ss, login, ':');
        while (std::getline(ss, category, ':')) {
            std::string categoryName, categoryValue;
            categoryName = encrypt(category, key);
            std::getline(ss, category, ':');
            categoryValue = encrypt(category, key);
            categories.insert(std::pair<std::string, std::string>(categoryName, categoryValue));
        }

        passwords.emplace_back(encrypt(name, key), encrypt(password, key),
                               encrypt(webpage, key),encrypt(login, key), categories);
        currentLine++;
    }

    return passwords;
}

/**
 * @brief Writes data to the file
 *
 * This function writes data to the file.
 *
 * @param path Stores the path to the file.
 * @param categories Stores the categories.
 * @param passwords Stores the passwords.
 * @param key Stores the master key.
 */
void writeFile(const std::string& path, const std::vector<std::string>& categories,
               const std::vector<Password>& passwords, const long& key, const std::time_t& time){
    auto vault = std::fstream(path, std::ios::out);

    std::tm* tm = std::localtime(&time);

    for (int i = 0; i < categories.size(); ++i) {
        if(i == categories.size() - 1)
            vault << encrypt(categories.at(i), key);
        else
            vault << encrypt(categories.at(i), key) << ":";
    }
    vault << "\n";

    int line = 0;

    for (const auto& password : passwords) {
        if(line == 0){
            vault << std::put_time(tm, "%H");
            vault << ":";
        }else if(line == passwords.size() / 2){
            vault << std::put_time(tm, "%M");
            vault << ":";
        }else if(line == passwords.size() - 1) {
            vault << std::put_time(tm, "%S");
            vault << ":";
        }
        vault << encrypt(password.getName(), key) << ":"
              << encrypt(password.getPassword(), key) << ":"
              << encrypt(password.getWebpage(), key) << ":"
              << encrypt(password.getLogin(), key);
        for (const auto& category : password.getCategories()) {
            vault << ":" << encrypt(category.first, key) << ":" << encrypt(category.second, key);
        }
        vault << "\n";
        line++;
    }
}

/**
 * @brief Encrypts data
 *
 * This function encrypts data using XOR operation.
 *
 * @param data Stores the data to be encrypted.
 * @param key Stores the master key.
 * @return encryptedData Stores the encrypted data.
 */
std::string encrypt(const std::string& data, const long& key){
    std::string encryptedData = "";
    for (int i = 0; i < data.length(); ++i) {
        encryptedData += (char)(data.at(i) ^ key);
    }
    return encryptedData;
}

/**
 * @brief Counts lines of passwords in the file
 *
 * This function counts lines of passwords in the file.
 *
 * @param path Stores the path to the file.
 * @return counter Stores the number of lines.
 */
int countLines(const std::string& path){
    int counter = 0;
    auto vault = std::fstream(path, std::ios::in);
    std::string line;
    while(std::getline(vault, line)){
        if (!line.empty()) {
            counter++;
        }
    }
    vault.close();

    return counter - 1;
}