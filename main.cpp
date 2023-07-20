#include <iostream>
#include <algorithm>


#include "game.h"
#include "inputFiler.h"
#include "getRandomNumber.h"
#include "fileTable.h"

unsigned int maxNumber = 100;

void displayMenu() {
    std::cout << "-------------------------------------------------------" << "\n";
    std::cout << "=============== Game = Guess the number ===============" << "\n";
    std::cout << "-------------------------------------------------------" << "\n";
    std::cout << "\n";
    std::cout << "\t 1. New game" << "\n";
    std::cout << "\t 2. Table of records" << "\n";
    std::cout << "\t 3. Exit" << "\n";
}

int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);

    std::vector<std::string> arguments;
    if (argc >= 2) {
        for (auto i = 1; i < argc; ++i) {
            arguments.push_back(argv[i]);
        }

        auto tablePos = std::find(arguments.begin(), arguments.end(), "-table");
        if (tablePos != arguments.end()) {
            printTable();
            exit(0);
        }

        auto maxPos = std::find(arguments.begin(), arguments.end(), "-max");
        if (maxPos != arguments.end()) {
            if (std::find(arguments.begin(), arguments.end(), "-level") != arguments.end()) {
                std::cout << "Wrong combination of arguments\n";
                exit(0);
            } else if ((maxPos + 1) != arguments.end() && is_integer(*(maxPos + 1))) {
                maxNumber = std::stoi(*(maxPos + 1));
                if (maxNumber < 10) maxNumber = 10;
                if (maxNumber > 100) maxNumber = 100;
            } else {
                std::cout << "After -max needed integer number from 10 to 100\n";
                exit(0);
            }
        }

        auto levelPos = std::find(arguments.begin(), arguments.end(), "-level");
        if (levelPos != arguments.end()) {
            if (std::find(arguments.begin(), arguments.end(), "-max") != arguments.end()) {
                std::cout << "Wrong combination of arguments\n";
                exit(0);
            } else if ((levelPos + 1) != arguments.end() && is_integer(*(levelPos + 1))) {
                int level = std::stoi(*(levelPos + 1));
                if (level <= 1) maxNumber = 10;
                if (level == 2) maxNumber = 50;
                if (level >= 3) maxNumber = 100;
            } else {
            std::cout << "After -level needed 1, 2 or 3\n";
            exit(0);
        }
        }
    }

    do {
        // Выводим стартовое сообщение и текстовое меню
        displayMenu();

        switch (getMenuNumber()) {
            case 1: {
                do {
                    // 1. Начать новую игру
                    // Компьютер загадывает число
                    unsigned int targetNumber = getRandomNumber(maxNumber);

                    // Человек отгадывает
                    int tryCount = game(targetNumber);
                    std::cout << "The number of Your attempts: " << tryCount << "\n";

                    // Просьба ввести имя игрока
                    std::cout << "Input player name - ";
                    std::string userName = getUserName();

                    // Сохраняем в таблицу рекордов
                    writeToTable(userName, tryCount);

                    // Играть ещё или выход в меню
                    std::cout << "\t Play again? y/n" << "\n";
                } while (getYN());
                break;
            }
            case 2: {
                // 2. Показать таблицу рекордов
                printTable();
                std::cout << "\t Continue? y/n" << "\n";
                if (!getYN()) exit(0);
                break;
            }
            case 3:
                // 3. Выход
                exit(0);
        }
    } while (true);
    return 0;
}
