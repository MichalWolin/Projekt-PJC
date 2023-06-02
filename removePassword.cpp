#include "fmt/core.h"
#include <vector>
#include <iostream>

#include "removePassword.h"

void removePassword(std::vector<Password>& passwords){
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
    fmt::println("Do you want to delete all passwords? (yes/no)");
    std::string option;
    std::cin >> option;
    while(option != "yes" && option != "no"){
        fmt::println("Wrong option, try again");
        std::cin >> option;
    }
    if(option == "yes"){
        fmt::println("Are you sure you want to delete all passwords? (yes/no)");
        std::cin >> option;
        while(option != "yes" && option != "no"){
            fmt::println("Wrong option, try again");
            std::cin >> option;
        }
        if(option == "yes"){
            passwords.clear();
            fmt::println("All passwords have been deleted");
        }
    }
    else{
        fmt::println("Which password do you want to delete?");
        int number;
        std::cin >> number;
        while(number < 1 || number > passwords.size()){
            fmt::println("Wrong number, try again");
            std::cin >> number;
        }
        passwords.erase(passwords.begin() + number - 1);
        fmt::println("Password has been deleted");
    }
}