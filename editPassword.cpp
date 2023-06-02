#include "fmt/core.h"
#include <vector>
#include <iostream>
#include <algorithm>

#include "editPassword.h"

void editPassword(std::vector<Password>& passwords){
    fmt::println("List of passwords:");
    for (int i = 0; i < passwords.size(); ++i) {
        fmt::print("{}: Name -> {}, Password -> {}, Webpage -> {}, Login -> {}",
                   i + 1, passwords.at(i).getName(), passwords.at(i).getPassword(), passwords.at(i).getWebpage(),
                   passwords.at(i).getLogin());
        for(auto category : passwords.at(i).getCategories()){
            fmt::print(", {}: {}", category.first, category.second);
        }
        fmt::print("\n");
    }
    fmt::println("Which password do you want to edit?");
    int number;
    std::cin >> number;
    while(number < 1 || number > passwords.size()){
        fmt::println("Wrong number, try again");
        std::cin >> number;
    }
    fmt::println("What do you want to edit?");
    fmt::println("1. Name\n"
                 "2. Password\n"
                 "3. Webpage\n"
                 "4. Login"
                 );
    int i = 5;
    for (const auto& category : passwords.at(number - 1).getCategories()) {
        fmt::println("{}. {}", i++, category.first);
    }

    int choice;
    std::cin >> choice;
    while(choice < 1 || choice > i){
        fmt::println("Wrong number, try again");
        std::cin >> choice;
    }



    std::string data;
    fmt::println("Enter new data:");
    std::cin >> data;

    Password& passwordData = passwords.at(number - 1);

    switch (choice) {
        case 1:
            passwordData.setName(data);
            break;
        case 2:
            passwordData.setPassword(data);
            break;
        case 3:
            passwordData.setWebpage(data);
            break;
        case 4:
            passwordData.setLogin(data);
            break;
    }
}
