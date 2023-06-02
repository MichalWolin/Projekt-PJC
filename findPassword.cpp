#include "fmt/core.h"
#include <vector>
#include <iostream>

#include "findPassword.h"

/**
 * @brief Function that finds password by name, webpage, login or category
 *
 * This function asks user by what he wants to find password and then finds it.
 *
 * @param passwords Vector of passwords
 * @param categories Vector of categories
 * @param data Data that user entered
 * @param choice Number of choice
 * @param categoryNumber Number of category
 * @param category Category
 * @param passwordCategories Categories of password
 */
void findPassword(const std::vector<Password>& passwords, const std::vector<std::string>& categories){
    fmt::println("By what do you want to find password?");
    fmt::println("1. Name\n"
                 "2. Webpage\n"
                 "3. Login\n"
                 "4. Category");
    int choice;
    std::cin >> choice;
    while(choice < 1 || choice > 4){
        fmt::println("Wrong number, try again");
        std::cin >> choice;
    }

    std::string data;

    switch(choice){
        case 1:
            fmt::println("Enter name:");
            std::cin >> data;
            fmt::println("List of found passwords:");
            for(const auto& password : passwords){
                if(password.getName() == data){
                    password.printPassword();
                }
            }
            break;
        case 2:
            fmt::println("Enter webpage:");
            std::cin >> data;
            fmt::println("List of found passwords:");
            for(const auto& password : passwords){
                if(password.getWebpage() == data){
                    password.printPassword();
                }
            }
            break;
        case 3:
            fmt::println("Enter login:");
            std::cin >> data;
            fmt::println("List of found passwords:");
            for(const auto& password : passwords){
                if(password.getLogin() == data){
                    password.printPassword();
                }
            }
            break;
        case 4:
            fmt::println("Available categories:");
            for (int i = 0; i < categories.size(); ++i) {
                fmt::println("{} -> {}", i+1, categories[i]);
            }
            fmt::println("Enter category number:");
            int categoryNumber;
            std::cin >> categoryNumber;
            while (categoryNumber < 1 || categoryNumber > categories.size()) {
                fmt::println("Invalid category number! Try again:");
                std::cin >> categoryNumber;
            }
            std::string category = categories[categoryNumber - 1];

            fmt::println("List of found passwords:");
            for (const auto& password : passwords) {
                const auto& passwordCategories = password.getCategories();
                if (passwordCategories.count(category) > 0) {
                    password.printPassword();
                }
            }
            break;
    }
}