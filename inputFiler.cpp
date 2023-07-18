#include <regex>
#include <iostream>

#include "inputFiler.h"

bool is_integer(const std::string &s) {
    std::regex pat{"\\d{1,6}"};
    return regex_match(s, pat);
}

bool is_right_name(const std::string &s) {
    std::regex pat{"[a-zA-Z][[:alnum:]]{4,20}"};
    return regex_match(s, pat);
}

bool is_yes_or_no(const std::string &s) {
    std::regex pat{"[yYnN]"};
    return regex_match(s, pat);
}

int getUserNumber() {

    std::string str;
    bool repeat = true;
    int out = 0;

    do {
        std::getline(std::cin, str);
        if (is_integer(str)) {
            out = std::stoi(str);
            repeat = false;
        } else {
            std::cout << "Please, input integer number\n";
            repeat = true;
        }
    } while (repeat);
    return out;
}

std::string getUserName() {

    std::string out;
    bool repeat = true;

    do {
        std::getline(std::cin, out);
        if(out.length()<4){
            std::cout << "Please, input Name more than 3 character\n";
            repeat = true;
        } else if (out.length()>20){
            std::cout << "Please, input Name less than 21 character\n";
            repeat = true;
        } else if(!is_right_name(out)) {
            std::cout << "Please, input right name\n" << "Allowed symbols a-z A-Z 0-9 \n" ;
            repeat = true;
        } else {
            repeat = false;
        }
    } while (repeat);

    return out;
}

int getMenuNumber() {

    std::string str;
    bool repeat = true;
    int out = 0;

    do {
        std::getline(std::cin, str);
        if (is_integer(str)) {
            out = std::stoi(str);
            if(out<1 || out>3) {
                std::cout << "Please, input 1, 2 or 3\n";
                repeat = true;
            }else
                repeat = false;
        } else {
            std::cout << "Please, input integer number\n";
            repeat = true;
        }
    } while (repeat);
    return out;
}

bool getYN() {

    std::string str;

    do {
        std::getline(std::cin, str);
        if (is_yes_or_no(str)) {
            if(str == "y" || str == "y") {
                return true;
            }else
                return false;
        } else {
            std::cout << "Please, y or n\n";
        }
    } while (true);
}
