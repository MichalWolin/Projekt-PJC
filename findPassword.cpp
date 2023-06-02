#include "fmt/core.h"
#include <vector>
#include <iostream>

#include "findPassword.h"

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
            for(const auto& password : passwords){
                if(password.getName() == data){
                    password.printPassword();
                }
            }
            break;
        case 2:
            fmt::println("Enter webpage:");
            std::cin >> data;
            for(const auto& password : passwords){
                if(password.getWebpage() == data){
                    password.printPassword();
                }
            }
            break;
        case 3:
            fmt::println("Enter login:");
            std::cin >> data;
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

            for (const auto& password : passwords) {
                const auto& passwordCategories = password.getCategories();
                if (passwordCategories.count(category)) {
                    password.printPassword();
                }
            }
            break;
    }
}