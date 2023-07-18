
#include <fstream>
#include <iostream>

#include "fileTable.h"

void writeToTable(std::string userName, int tryCount) {
    std::fstream file( "../table.txt", std::fstream::out | std::fstream::app);
    if (!file.is_open()) {
        std::cout << "ERROR Can't open file";
    }
    file << userName << " " << tryCount << "\n";
}
