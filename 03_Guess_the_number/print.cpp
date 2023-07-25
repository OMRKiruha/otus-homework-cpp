
#include <iostream>
#include <iomanip>
#include "print.h"

namespace print {

    /**
     * @brief Очищает экран
     */
    void clearScreen() {
#ifdef WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    /**
     * @brief Выводит таблицу рекордов
     * @param tableToOutput - std::map из количества попыток и имён пользователей
     */
    void highScore(std::map<int, std::string>& tableToOutput) {
        clearScreen();
        std::cout << "-----------------------------------------" << "\n";
        std::cout << "==========     High scores     ==========" << "\n";
        std::cout << "-----------------------------------------" << "\n";
        for (auto &row: tableToOutput) {
            std::cout << "|  "
                      << std::setw(22) << std::left << row.second << "  |  "
                      << std::setw(8) << std::right << row.first << "  |\n";
            std::cout << "-----------------------------------------" << "\n";
        }
    }

    /**
     * @brief Выводим меню игры
     */
    void menu() {
        clearScreen();
        std::cout << "-------------------------------------------------------" << "\n";
        std::cout << "=============== Game = Guess the number ===============" << "\n";
        std::cout << "-------------------------------------------------------" << "\n";
        std::cout << "\n";
        std::cout << "\t 1. New game" << "\n";
        std::cout << "\t 2. Table of records" << "\n";
        std::cout << "\t 3. Exit" << "\n";
    }
}