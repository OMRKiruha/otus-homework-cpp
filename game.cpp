#include <iostream>

#include "game.h"
#include "inputFiler.h"

/**
 * @brief Принимает загаданное число, возвращает количество попыток
 * @param target_value
 * @return
 */
int game(const unsigned int target_value) {
    int tryCount = 0;
    int current_value = 0;

    std::cout << "Enter your guess:\n";
    std::string str;

    do {
        current_value = getUserNumber();

        tryCount++;

        if (current_value > target_value) {
            std::cout << "less than " << current_value << "\n";
        } else if (current_value < target_value) {
            std::cout << "greater than " << current_value << "\n";
        } else {
            std::cout << "You WIN !!!\n";
            break;
        }
    } while (true);

    return tryCount;
}