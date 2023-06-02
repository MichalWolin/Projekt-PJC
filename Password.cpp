#include <map>
#include <iostream>
#include <fmt/core.h>

#include "Password.h"

/**
 * @brief Construct a new Password:: Password object
 *
 * This constructor is used when the user wants to create a new password.
 *
 * @param name The name of the password.
 * @param password The password.
 * @param webpage The webpage associated with the password.
 * @param login The login associated with the password.
 * @param categories The categories associated with the password.
 */
Password::Password(const std::string& name, const std::string& password, const std::string& webpage,
                   const std::string& login, const std::map<std::string, std::string>& categories) :
        name(name), password(password), webpage(webpage),
        login(login), categories(categories) {}

/**
 * @brief Returns the name of the password.
 */
std::string Password::getName() const {
    return name;
}

/**
 * @brief Returns the password.
 */
std::string Password::getPassword() const {
    return password;
}

/**
 * @brief Returns the webpage associated with the password.
 */
std::string Password::getWebpage() const {
    return webpage;
}

/**
 * @brief Returns the login associated with the password.
 */
std::string Password::getLogin() const {
    return login;
}

/**
 * @brief Returns the categories associated with the password.
 */
std::map<std::string, std::string> Password::getCategories() const {
    return categories;
}

/**
 * @brief Sets the password.
 */
void Password::setPassword(const std::string& password) {
    this->password = password;
}

/**
 * @brief Sets the name of the password.
 */
void Password::setName(const std::string& name) {
    this->name = name;
}

/**
 * @brief Sets the webpage associated with the password.
 */
void Password::setWebpage(const std::string& webpage) {
    this->webpage = webpage;
}

/**
 * @brief Sets the login associated with the password.
 */
void Password::setLogin(const std::string& login) {
    this->login = login;
}

/**
 * @brief Sets the categories associated with the password.
 */
void Password::setCategories(const std::string& categoryKey, const std::string& data) {
    categories[categoryKey] = data;
}

/**
 * @brief Prints data about the password.
 */
void Password::printPassword() const{
    fmt::print("Name: {}, Password: {}, Webpage: {}, Login: {}",
               this->getName(), this->getPassword(), this->getWebpage(), this->getLogin());
    for(auto category : this->categories){
        fmt::print(", {}: {}", category.first, category.second);
    }
    fmt::print("\n");
}