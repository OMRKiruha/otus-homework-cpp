#include <regex>
#include <iostream>

#include "inputFiler.h"

namespace inputFilter {

    /**
     * @brief Определяем число ли в строке
     * @param s
     * @return Если строка состоит только из цифр и длинной до 6 знаков, то возвращаем true
     */
    bool is_integer(const std::string &s) {
        std::regex pat{"\\d{1,6}"};
        return regex_match(s, pat);
    }

    /**
     * @brief Определяем правильность введённого имени пользователя
     * @param s
     * @return Если строка начинается с букв и состоит только из букв и цифр, то возвращаем true
     */
    bool is_right_name(const std::string &s) {
        std::regex pat{"[a-zA-Z][[:alnum:]]{3,20}"};
        return regex_match(s, pat);
    }

    /**
     * @brief Определяем введены ли символы yYnN
     * @param s
     * @return
     */
    bool is_yes_or_no(const std::string &s) {
        std::regex pat{"[yYnN]{1}"};
        return regex_match(s, pat);
    }

    /**
     * @brief Получаем от пользователя и проверяем ввод числа
     * @return
     */
    int getUserNumber() {
        std::string str;
        do {
            std::getline(std::cin, str);
            if (is_integer(str)) {
                return std::stoi(str);
            } else {
                std::cout << "Please, input integer number\n";
            }
        } while (true);
    }

    /**
     * @brief Получаем от пользователя и проверяем ввод имени
     * @return
     */
    std::string getUserName() {
        std::string out;
        do {
            std::getline(std::cin, out);
            if (out.length() < 4) {
                std::cout << "Please, input Name more than 3 character\n";
                continue;
            } else if (out.length() > 20) {
                std::cout << "Please, input Name less than 21 character\n";
                continue;
            } else if (!is_right_name(out)) {
                std::cout << "Please, input right name\n" << "Allowed symbols a-z A-Z 0-9 \n";
                continue;
            } else {
                break;
            }
        } while (true);
        return out;
    }

    /**
     * @brief Получаем от пользователя и проверяем ввод пункта меню
     * @return
     */
    int getMenuNumber() {
        std::string str;
        int out = 0;
        do {
            std::getline(std::cin, str);
            if (is_integer(str)) {
                out = std::stoi(str);
                if (out < 1 || out > 3) {
                    std::cout << "Please, input 1, 2 or 3\n";
                    continue;
                } else
                    break;
            } else {
                std::cout << "Please, input integer number\n";
            }
        } while (true);
        return out;
    }

    /**
     * @brief Получаем от пользователя и проверяем ввод y/n
     * @return
     */
    bool getYN() {
        std::string str;
        do {
            std::getline(std::cin, str);
            if (is_yes_or_no(str) && str.length() == 1) {
                if (str == "y" || str == "y") {
                    return true;
                } else
                    return false;
            } else {
                std::cout << "Please, y or n\n";
            }
        } while (true);
    }
} //namespace inputFilter