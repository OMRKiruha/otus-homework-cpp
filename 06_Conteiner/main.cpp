
#include <iostream>

#include "MyVector.h"
#include "MyList.h"


void testVec() {
    std::cout << "1. Создаём объект класса MyVector<int>\n";
    MyVector<int> vec;
    int i = 0;

    std::cout << "2. Заполняем объект класса MyVector<int> числами от 0 до 9\n";
    while (i < 10) {
        vec.push_back(i);
        ++i;
    }

    std::cout << "3. Выводим на экран содержимое объекта класса MyVector<int>\n";
    for (auto elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "4. Выводим на экран размер объекта класса MyVector<int>\n";
    std::cout << "vec.size() = " << vec.size() << "\n";

    std::cout << "5. Удаляем из объекта класса MyVector<int> \n";
    vec.erase(vec.begin() + 3);
    vec.erase(vec.begin() + 5);
    vec.erase(vec.begin() + 7);

    std::cout << "6. Выводим на экран содержимое объекта класса MyVector<int>\n";
    for (auto elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "7. Добавляем число 10 в начало объекта класса MyVector<int>\n";
    vec.insert(vec.begin(), 10);

    std::cout << "8. Выводим на экран содержимое объекта класса MyVector<int>\n";
    for (auto elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "9. Добавляем число 20 в середину объекта класса MyVector<int>\n";
    vec.insert((vec.begin() + (vec.size() / 2)), 20);

    std::cout << "10. Выводим на экран содержимое объекта класса MyVector<int>\n";
    for (auto elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    std::cout << "11. Добавляем число 30 в конец объекта класса MyVector<int>\n";
    vec.insert(vec.end(), 30);

    std::cout << "12. Выводим на экран содержимое объекта класса MyVector<int>\n";
    for (auto elem: vec) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

void testList(){

}

int main() {
    testVec();
    testList();


    return 0;
}