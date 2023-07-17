
#include "game.h"

/**
 * @brief Принимает загаданное число, возвращает количество попыток
 * @param target_value
 * @return
 */
int game(const int target_value) {

    int current_value = 0;
    bool not_win = true;

    std::cout << "Enter your guess:\n";

    do {
        std::cin >> current_value;
        //TODO вызов фильтра ввода

        if (current_value < target_value) {
            std::cout << "less than " << current_value << "\n";
        } else if (current_value > target_value) {
            std::cout << "greater than " << current_value << "\n";
        } else {
            std::cout << "You WIN !!!\n";
            break;
        }
    } while (true);
}