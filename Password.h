#pragma once

#include <string>
#include <map>

struct Password {
    std::string name;
    std::string password;
    std::string webpage;
    std::string login;
    std::map<std::string, std::string> categories;

    Password(const std::string &name, const std::string &password, const std::string &webpage,
             const std::string &login, const std::map<std::string, std::string> &categories);

    std::string getName() const;
    std::string getPassword() const;
    std::string getWebpage() const;
    std::string getLogin() const;
    std::map<std::string, std::string> getCategories() const;
    void setPassword(const std::string& password);
    void setName(const std::string& name);
    void setWebpage(const std::string& webpage);
    void setLogin(const std::string& login);
    void setCategories(const std::string& categoryKey, const std::string& data);
    void printPassword() const;
};
