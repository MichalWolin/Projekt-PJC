#include <map>
#include <iostream>
#include <fmt/core.h>

#include "Password.h"

Password::Password(const std::string& name, const std::string& password, const std::string& webpage,
                   const std::string& login, const std::map<std::string, std::string>& categories) :
        name(name), password(password), webpage(webpage),
        login(login), categories(categories) {}

std::string Password::getName() const {
    return name;
}

std::string Password::getPassword() const {
    return password;
}

std::string Password::getWebpage() const {
    return webpage;
}

std::string Password::getLogin() const {
    return login;
}

std::map<std::string, std::string> Password::getCategories() const {
    return categories;
}

void Password::setPassword(const std::string& password) {
    this->password = password;
}

void Password::setName(const std::string& name) {
    this->name = name;
}

void Password::setWebpage(const std::string& webpage) {
    this->webpage = webpage;
}

void Password::setLogin(const std::string& login) {
    this->login = login;
}

void Password::setCategories(const std::string& categoryKey, const std::string& data) {
    categories[categoryKey] = data;
}

void Password::printPassword() const{
    fmt::print("Name: {}, Password: {}, Webpage: {}, Login: {}",
               this->getName(), this->getPassword(), this->getWebpage(), this->getLogin());
    for(auto category : this->categories){
        fmt::print(", {}: {}", category.first, category.second);
    }
    fmt::print("\n");
}