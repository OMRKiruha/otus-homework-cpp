
#ifndef FINDNUMBER_PRINT_H
#define FINDNUMBER_PRINT_H

#include <map>

namespace print {

    void clearScreen();

    void highScore(std::map<int, std::string>& tableToOutput);

    void menu();

};

#endif //FINDNUMBER_PRINT_H
