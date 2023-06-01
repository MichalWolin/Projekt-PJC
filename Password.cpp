#include <iostream>
#include <map>

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
