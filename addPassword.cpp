#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

#include "addPassword.h"
#include "Password.h"

std::string generatePassword();


/**
 * @brief Adds password to the vector of passwords
 *
 * This function asks user for name of password, if he wants to generate password or enter it himself,
 * if he wants to add link to the website and login. Then it asks user to set categories for password
 * and adds password to the vector of passwords.
 *
 * @param passwords Vector of passwords
 * @param categories Vector of categories
 * @param input Input from user
 * @param name Name of password
 * @param password Password itself
 * @param webpage Link to the website
 * @param login Login to the website
 * @param categoriesMap Map of categories
 */
void addPassword(std::vector<Password>& passwords, const std::vector<std::string>& categories){
    std::string name, password, webpage, login, input;
    fmt::println("Name of password (e.g. password to twitter account):");
    std::cin >> name;

    fmt::println("Do you want to have password generated? (yes/no):");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        password = generatePassword();
    }else{
        bool creatingPassword = true;
        while(creatingPassword){
            fmt::println("Enter password:");
            std::cin >> password;

            auto it = std::ranges::find_if(passwords, [password](const Password& p)
            {
                return p.getPassword() == password;
            });

            if(it != passwords.end()){
                fmt::println("Password already exists! Would you like to use another password? (yes/no):");
                std::cin >> input;
                while(input != "yes" && input != "no"){
                    fmt::println("Invalid input! Try again:");
                    std::cin >> input;
                }
                if(input == "yes"){
                    continue;
                }
            }

            auto smallLetter = std::ranges::find_if(password, [](char c)
            {return std::islower(c);});
            auto capitalLetter = std::ranges::find_if(password, [](char c)
            {return std::isupper(c);});
            auto specialCharacter = std::ranges::find_if(password, [](char c)
            {return std::ispunct(c);});

            int categories = 0;
            categories += smallLetter != password.end() ? 1 : 0;
            categories += capitalLetter != password.end() ? 1 : 0;
            categories += specialCharacter != password.end() ? 1 : 0;
            categories += password.size() >= 8 ? 1 : 0;

            switch(categories){
                case 0:
                    fmt::println("Your password is too weak, try other password!");
                    break;
                case 1:
                    fmt::println("Your password is weak, you should try other password!");
                    break;
                case 2:
                    fmt::println("Your password is weak, you should try other password!");
                    break;
                case 3:
                    fmt::println("Your password is strong, but it can be better!");
                    break;
                case 4:
                    fmt::println("Your password is very strong!");
                    break;
            }

            fmt::println("Would you like to try another password? (yes/no):");
            std::cin >> input;
            while(input != "yes" && input != "no"){
                fmt::println("Invalid input! Try again:");
                std::cin >> input;
            }
            if(input == "no"){
                creatingPassword = false;
            }
        }
    }

    fmt::println("Do you want to add a link to the website? (yes/no)");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        fmt::println("Enter a link to the website (g.e. www.pja.edu.pl):");
        std::cin >> webpage;
    }else{
        webpage = "-";
    }

    fmt::println("Do you want to add login? (yes/no)");
    std::cin >> input;
    while(input != "yes" && input != "no"){
        fmt::println("Invalid input! Try again:");
        std::cin >> input;
    }
    if(input == "yes"){
        fmt::println("Enter login (g.e. ThrowAwayAccount100):");
        std::cin >> login;
    }else{
        login = "-";
    }

    std::map<std::string, std::string> categoriesMap;
    for(const std::string& category : categories){
        fmt::println("Set category {}:", category);
        std::cin >> input;
        categoriesMap.insert(std::pair<std::string, std::string>(category, input));
    }

    Password newPassword(name, password, webpage, login, categoriesMap);
    passwords.push_back(newPassword);

    fmt::println("Password added successfully! Remember to exit through menu to save changes!");
}


/**
 * @brief Generates password
 *
 * This function generates password with length from 6 to 100 characters. User can choose if he wants to include
 * small letters, capital letters and special characters. Password is generated randomly.
 *
 * @param smallLetters String with small letters
 * @param capitalLetters String with capital letters
 * @param specialCharacters String with special characters
 * @param length Length of generated password
 * @param generatedPassword Generated password
 * @param characters String with characters that will be used to generate password
 * @param input Input from user
 * @return std::string Generated password
 */
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

