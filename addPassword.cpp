#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <ctime>

#include "addPassword.h"

std::string generatePassword();
std::string encryptPassword(const std::string& password, const long& key);

void addPassword(const std::string& path, const long& key){
    auto vault = std::fstream(path, std::ios::in);
    std::string line, word;
    std::getline(vault, line);

    vault = std::fstream(path, std::ios::out | std::ios::app);
    std::string input;
    fmt::println("Name of password (e.g. password to twitter account):");
    std::cin >> input;
    vault << input + ":";

    fmt::println("Do you want to have password generated? (yes/no):");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        vault << encryptPassword(generatePassword(), key) + ":";
    }else{
        fmt::println("Password:");
        std::cin >> input;
        vault << encryptPassword(input, key) + ":";
    }

    fmt::println("Do you want to add a link to the website? (yes/no)");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        fmt::println("Enter a link to the website (g.e. www.pja.edu.pl):");
        std::cin >> input;
        vault << input + ":";
    }else{
        vault << "-:";
    }

    fmt::println("Do you want to add login? (yes/no)");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        fmt::println("Enter login (g.e. ThrowAwayAccount100):");
        std::cin >> input;
        vault << input;
    }else{
        vault << "-";
    }
}

std::string generatePassword(){
    std::string smallLetters = "abcdefghijklmnopqrstuvwxyz";
    std::string capitalLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string specialCharacters = "!@#$%^&*";

    int length = 0;
    fmt::println("Enter length of generated password (range from 6 to 100):");
    std::cin >> length;
    while(length <= 6 || length >= 100){
        fmt::println("Invalid length! Try again:");
        std::cin >> length;
    }
    std::string generatedPassword = "";
    std::string characters = "";

    while(characters.length() == 0){
        std::string input;
        fmt::println("Do you want to include small letters? (yes/no):");
        std::cin >> input;
        while(input != "yes" && input != "no"){
            fmt::println("Invalid option! Try again:");
            std::cin >> input;
        }
        if(input == "yes"){
            characters += smallLetters;
        }

        fmt::println("Do you want to include capital letters? (yes/no):");
        std::cin >> input;
        while(input != "yes" && input != "no"){
            fmt::println("Invalid option! Try again:");
            std::cin >> input;
        }
        if(input == "yes"){
            characters += capitalLetters;
        }

        fmt::println("Do you want to include special characters? (yes/no):");
        std::cin >> input;
        while(input != "yes" && input != "no"){
            fmt::println("Invalid option! Try again:");
            std::cin >> input;
        }
        if(input == "yes"){
            characters += specialCharacters;
        }

        if(characters.length() == 0){
            fmt::println("You have to pick at least one category! Try again:");
        }
    }

    std::srand(std::time(nullptr));

    for (int i = 0; i < length; ++i) {
        generatedPassword += characters.at(std::rand() % characters.length());
    }

    return generatedPassword;
}

std::string encryptPassword(const std::string& password, const long& key){
    std::string encryptedPassword = "";
    for (int i = 0; i < password.length(); ++i) {
        encryptedPassword += (char)(password.at(i) ^ key);
    }
    return encryptedPassword;
}