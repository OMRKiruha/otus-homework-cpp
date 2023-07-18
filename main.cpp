#include <iostream>


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

int main() {
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
                if(!getYN()) exit(0);
                break;
            }
            case 3:
                // 3. Выход
                exit(0);
        }
    } while (true);
    return 0;
}
