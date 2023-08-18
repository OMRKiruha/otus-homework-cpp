
#include <iostream>

#include "MyVector.h"
#include "MyList.h"
#include <list>



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
    printVec(vec);

    std::cout << "4. Выводим на экран размер объекта класса MyVector<int>\n";
    std::cout << "vec.size() = " << vec.size() << "\n";

    std::cout << "5. Удаляем из объекта класса MyVector<int> \n";
    vec.erase(vec.begin() + 2);
    vec.erase(vec.begin() + 3);
    vec.erase(vec.begin() + 4);

    std::cout << "6. Выводим на экран содержимое объекта класса MyVector<int>\n";
    printVec(vec);

    std::cout << "7. Добавляем число 10 в начало объекта класса MyVector<int>\n";
    vec.insert(vec.begin(), 10);

    std::cout << "8. Выводим на экран содержимое объекта класса MyVector<int>\n";
    printVec(vec);

    std::cout << "9. Добавляем число 20 в середину объекта класса MyVector<int>\n";
    vec.insert((vec.begin() + (vec.size() / 2)), 20);

    std::cout << "10. Выводим на экран содержимое объекта класса MyVector<int>\n";
    printVec(vec);

    std::cout << "11. Добавляем число 30 в конец объекта класса MyVector<int>\n";
    vec.insert(vec.end(), 30);

    std::cout << "12. Выводим на экран содержимое объекта класса MyVector<int>\n";
    printVec(vec);

    MyVector<int> vec1(vec);
    MyVector<int> vec2;
    vec2 = vec;
    std::cout << std::endl; // Flush
}

void testList(){
    std::cout << "1. Создаём объект класса MyList<int>\n";
    MyList<int> list;
    int i = 0;

    std::cout << "2. Заполняем объект класса MyList<int> числами от 0 до 9\n";
    while (i < 10) {
        list.push_back(i);
        ++i;
    }

    std::cout << "3. Выводим на экран содержимое объекта класса MyList<int>\n";
    printList(list);


    std::cout << "4. Выводим на экран размер объекта класса MyList<int>\n";
    std::cout << "list.size() = " << list.size() << "\n";

    std::cout << "5. Удаляем из объекта класса MyList<int> \n";
    list.erase(list.begin() + 2);
    list.erase(list.begin() + 3);
    list.erase(list.begin() + 4);


    std::cout << "6. Выводим на экран содержимое объекта класса MyList<int>\n";
    printList(list);

    std::cout << "7. Добавляем число 10 в начало объекта класса MyList<int>\n";
    list.insert(list.begin(), 10);

    std::cout << "8. Выводим на экран содержимое объекта класса MyList<int>\n";
    printList(list);

    std::cout << "9. Добавляем число 20 в середину объекта класса MyList<int>\n";
    list.insert((list.begin() + (list.size() / 2)), 20);

    std::cout << "10. Выводим на экран содержимое объекта класса MyList<int>\n";
    printList(list);

    std::cout << "11. Добавляем число 30 в конец объекта класса MyList<int>\n";
    list.insert(list.end(), 30);

    std::cout << "12. Выводим на экран содержимое объекта класса MyList<int>\n";
    printList(list);

//    MyList<int> list1(list);
//    MyList<int> list2;
//    list2 = list;

    std::cout << std::endl; // Flush

}

int main() {
    testVec();
    testList();

    return 0;
}