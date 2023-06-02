#include "fmt/core.h"
#include <vector>
#include <string>
#include <iostream>

#include "addCategory.h"

/**
 * @brief Adds a new category to the list of categories
 *
 * This function asks the user to enter the name of the category to be added.
 * If the category already exists, the user is asked to enter a different name.
 * If the category does not exist, it is added to the list of categories.
 *
 * @param categories Contains the list of categories
 * @param category Contains the name of the category to be added
 */
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