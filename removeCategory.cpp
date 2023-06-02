#include <vector>
#include <fmt/core.h>
#include <iostream>
#include <algorithm>

#include "removeCategory.h"

/**
 * @brief Removes category from the list of categories and all passwords that have this category
 *
 * This function removes category from the list of categories and all passwords that have this category
 *
 * @param passwords vector of passwords
 * @param categories vector of categories
 */
void removeCategory(std::vector<Password>& passwords, std::vector<std::string>& categories){
    fmt::println("List of categories:");
    for (int i = 0; i < categories.size(); ++i) {
        fmt::print("{}: {}\n", i + 1, categories.at(i));
    }
    fmt::println("Which category do you want to remove?");
    int number;
    std::cin >> number;
    while(number < 1 || number > categories.size()){
        fmt::println("Wrong number, try again");
        std::cin >> number;
    }

    std::string category = categories.at(number - 1);

    int counter = std::ranges::count_if(passwords, [category](const Password& password){
        return password.getCategories().count(category) > 0;
    });

    fmt::println("Are you sure you want to remove {} passwords? (yes/no)", counter);
    std::string answer;
    std::cin >> answer;
    while(answer != "yes" && answer != "no"){
        fmt::println("Wrong answer, try again");
        std::cin >> answer;
    }

    if(answer == "no"){
        return;
    }else{
        categories.erase(categories.begin() + number - 1);

        passwords.erase(
                std::remove_if(passwords.begin(), passwords.end(),
                               [category](const Password& password){
                    return password.getCategories().count(category) > 0;
                }),
                passwords.end()
        );

        fmt::println("Category successfully removed!");
    }
}
