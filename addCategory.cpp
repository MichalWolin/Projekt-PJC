#include "fmt/core.h"
#include <vector>
#include <string>
#include <iostream>

#include "addCategory.h"

void addCategory(std::vector<std::string>& categories){
    fmt::println("Enter the name of the category:");
    std::string category;
    std::cin >> category;

    while(std::find(categories.begin(), categories.end(), category) != categories.end()){
        fmt::println("Category already exists! Try again:");
        std::cin >> category;
    }

    categories.push_back(category);
    fmt::println("Category added successfully!");
}