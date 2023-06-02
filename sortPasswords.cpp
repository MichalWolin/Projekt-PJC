#include "fmt/core.h"
#include <iostream>
#include <vector>

#include "sortPasswords.h"



void sortPasswords(std::vector<Password>& passwords) {
    fmt::println("How do you want to sort passwords?");
    fmt::println("Available sorting options:");
    fmt::println("1. Name");
    fmt::println("2. Password");
    fmt::println("3. Webpage");
    fmt::println("4. Login");

    bool typing = true;
    std::vector<int> sortingOptions;
    int option;
    while(typing){
        fmt::println("If you want to stop entering sorting options, type 0.");
        fmt::println("Enter the numbers of the sorting options (one at the time):");
        std::cin >> option;
        while(option < 0 || option > 4){
            fmt::println("Invalid option! Try again:");
            std::cin >> option;
        }
        if(option == 0)
            typing = false;
        else
            sortingOptions.push_back(option);
    }

    std::sort(passwords.begin(), passwords.end(), [&](const Password& a, const Password& b) {
        for (int option : sortingOptions) {
            switch (option) {
                case 1:
                    if (a.getName() != b.getName()) {
                        return a.getName() < b.getName();
                    }
                    break;
                case 2:
                    if (a.getPassword() != b.getPassword()) {
                        return a.getPassword() < b.getPassword();
                    }
                    break;
                case 3:
                    if (a.getWebpage() != b.getWebpage()) {
                        return a.getWebpage() < b.getWebpage();
                    }
                    break;
                case 4:
                    if (a.getLogin() != b.getLogin()) {
                        return a.getLogin() < b.getLogin();
                    }
                    break;
                default:
                    break;
            }
        }
        return false;
    });

    for(const auto& password : passwords)
        password.printPassword();
}
