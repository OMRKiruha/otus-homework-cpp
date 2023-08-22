
#ifndef CONTEINERS_MYLIST_H
#define CONTEINERS_MYLIST_H

#include <cstddef>
#include <iostream>

//#define DEBUG

template<typename T>
class MyList {

    template<typename U>
    struct Node {

        U data{}; // пользовательские данные (хранимый объект)
        Node<U> *prev = nullptr; // указатель на предыдущий элемент Node
        Node<U> *next = nullptr; // указатель на следующий элемент Node

        explicit Node(const U &value, Node<U> *prev = nullptr, Node<U> *next = nullptr) :
                data(value), prev(prev), next(next) {}
    };

public:
    template<typename V>
    class MyListIterator {
        friend class MyList<V>;

    public:
        MyListIterator() : pNode(new Node<T>{}) {}

        explicit MyListIterator(Node<T> *p) : pNode(p) {}

        V &operator*() { return static_cast<Node<T> *>(pNode)->data; }

        V *operator->() { return &static_cast<Node<T> *>(pNode)->data; }

        V &get() { return *static_cast<Node<T> *>(pNode)->data; }

        bool operator!=(MyListIterator const &other) const { return pNode != other.pNode; }

        bool operator!=(std::nullptr_t const &other) const { return pNode != nullptr; }

        bool operator==(MyListIterator const &other) const { return pNode == other.pNode; }

        MyListIterator<V> &operator++() {
            pNode = pNode->next;
            return *this;
        }

        MyListIterator<V> &operator--() {
            pNode = pNode->prev;
            return *this;
        }

        MyListIterator<V> &operator+(int i) {
            while (i != 0) {
                if (pNode->next != nullptr) pNode = pNode->next;
                --i;
            }
            return *this;
        }

        MyListIterator<V> &operator-(int i) {
            while (i != 0) {
                if (pNode->prev != nullptr) pNode = pNode->prev;
                --i;
            }
            return *this;
        }

    private:
        Node<T> *pNode;

        Node<T> *node() {
            return pNode;
        }
    };

    typedef MyListIterator<T> iterator;
    typedef MyListIterator<const T> const_iterator;

private:
    Node<T> *m_begin = nullptr;
    Node<T> *m_end = nullptr;
    size_t m_size{};

public:
    // Конструктор без параметров
    MyList() {
#ifdef DEBUG
        std::cout << "\tКонструктор без параметров (по умолчанию)\n";
#endif
        m_begin = nullptr;
        m_end = m_begin;
        m_size = 0;
    }


    // Конструктор копирования
    MyList(const MyList<T> &other) {
#ifdef DEBUG
        std::cout << "\tКонструктор копирования\n";
#endif
        copy_elements_from(other);
    }

    // Конструктор перемещения
    MyList(const MyList<T> &&other)  noexcept {
#ifdef DEBUG
        std::cout << "\tКонструктор перемещения\n";
#endif
        // Очищаем текущий объект
        delete_elements();
        // Присваиваем чужие указатели
        this->m_begin = other.m_begin;
        this->m_end = other.m_end;
        this->m_size = other.m_size;
    }

    //Деструктор
    ~MyList() {
#ifdef DEBUG
        std::cout << "\tДеструктор\n";
#endif
        delete_elements();
    }


    // Оператор присваивания копированием
    MyList<T> &operator=(const MyList<T> &other) {
#ifdef DEBUG
        std::cout << "\tОператор присваивания копированием\n";
#endif
        //Проверка на присваивание самому себе
        if (other.m_begin == this->m_begin) { return *this; }
        // Удаляем наш лист
        delete_elements();
        // и повторяем конструктор копирования
        copy_elements_from(other);
        return *this;
    }


    // Оператор присваивания перемещением
    MyList<T> &operator=(MyList<T> &&other) noexcept {
#ifdef DEBUG
        std::cout << "\tОператор присваивания перемещением\n";
#endif
        //Проверка на присваивание самому себе
        if (other.m_begin == this->m_begin) { return *this; }
        // Очищаем текущий объект
        delete_elements();
        // Присваиваем чужие указатели и поля
        this->m_begin = other.m_begin;
        this->m_end = other.m_end;
        this->m_size = other.m_size;
        other.m_begin = nullptr;
        other.m_end = nullptr;
        other.m_size = 0;
        return *this;
    }


    [[nodiscard]] size_t size() const { return m_size; }


    // Оператор добавления элемента в конец вектора
    void push_back(const T &value) {
        auto *newNode = new Node<T>(value);    // Создаём новую ноду
        if (m_size == 0) {
            this->m_begin = newNode;
            this->m_end = m_begin;
            this->m_size++;
        } else {
            //Node *current = this->m_begin;
            //while (current->next != nullptr) { current = current->next; }
            newNode->prev = m_end;      // В последнюю ячейку присваиваем предыдущий конец
            m_end->next = newNode;      // В предыдущий конец присваиваем текущую ноду
            this->m_end = newNode;      // В конец листа присваиваем адрес новой ноды
            this->m_size++;
        }
    }


    // Оператор добавления элемента в конец вектора
    void push_front(const T &value) {
        auto *newNode = new Node<T>(value);    // Создаём новую ноду
        if (m_size == 0) {
            this->m_begin = newNode;
            this->m_end = m_begin;
            this->m_size++;
        } else {
            newNode->next = m_begin;      // В первую ячейку присваиваем предыдущее начало
            m_begin->prev = newNode;      // В предыдущее начало присваиваем текущую ноду
            this->m_begin = newNode;      // В начало листа присваиваем адрес новой ноды
            this->m_size++;
        }
    }


    // Оператор удаления элемента из конца вектора
    void pop_back() {
        if (m_end->prev != nullptr) {
            Node<T> *new_end = m_end->prev;
            delete this->m_end;
            this->m_end = new_end;    // Присваиваем новые указатели
            m_end->next = nullptr;
            --m_size;
        } else {
            delete this->m_end;
            this->m_end = nullptr;    // Зануляем указатели
            this->m_begin = nullptr;
            --m_size;
        }
    }

    // Оператор удаления элемента из начала списка
    void pop_front() {
        if (m_begin->next != nullptr) { // Если удаляем не последний элемент
            Node<T> *new_begin = m_begin->next;
            delete this->m_begin;
            this->m_begin = new_begin;    // Присваиваем новые указатели
            m_begin->prev = nullptr;
            --m_size;
        } else {
            delete this->m_begin;
            this->m_end = nullptr;    // Зануляем указатели
            this->m_begin = nullptr;
            --m_size;
        }
    }

    T &operator[](size_t index) {
        // Проверка на корректность переданного индекса элемента
        if (index < m_size) {
            size_t i = 0;
            Node<T> *it = m_begin;
            while (i != index) {
                it = it->next;
                i++;
            }
            return it->data;
        }
        throw (std::out_of_range("Проверьте правильность индекса объекта MyList"));
    }


    T operator[](size_t index) const {
        // Проверка на корректность переданного индекса элемента
        if (index < m_size) {
            size_t i = 0;
            Node<T> *it = m_begin;
            while (i != index) {
                it = it->next;
                i++;
            }
            return it->data;
        }
        throw (std::out_of_range("Проверьте правильность индекса объекта MyList"));
    }


    iterator begin() { return iterator(m_begin); }

    iterator end() { return iterator(m_end->next); }

    const_iterator begin() const { return const_iterator(m_begin); }

    const_iterator end() const { return const_iterator(m_end->next); }


    iterator erase(iterator pos) {
        // Удаление из начала
        if (pos == begin()) {
            pop_front();
            return begin();
        } else if (pos == end()) { // Удаление из конца
            pop_back();
            return end();
        } else {        // Удаление из середины
            // Находим предыдущий и следующий элементы
            Node<T> *prev = pos.node()->prev;
            Node<T> *next = pos.node()->next;
            // Присваиваем новые указатели в обход удаляемого элемента
            prev->next = next;
            next->prev = prev;
            --m_size;
            // Удаляем старый элемент
            delete pos.node();
            return iterator(next);
        }
    }

    iterator insert(iterator pos, const T &value) {
        // Вставка в начало
        if (pos == begin()) {
            push_front(value);
        } else if (pos == end()) { // Вставка в конец
            push_back(value);
        } else {        // Вставка в произвольное место
            // Находим предыдущий и следующий элементы
            Node<T> *prev = pos.node()->prev;
            Node<T> *next = pos.node();
            // Присваиваем новые указатели в обход удаляемого элемента
            auto temp = new Node<T>(value);
            prev->next = temp;
            next->prev = temp;
            temp->prev = prev;
            temp->next = next;
            ++m_size;
        }
        return pos;
    }

private:
    void copy_elements_from(const MyList<T> &other) {
#ifdef DEBUG
        std::cout << "\tКопируем элементы из другого объекта\n";
#endif
        auto otherElem = other.begin();
        while (otherElem != nullptr) {
            push_back(*otherElem);
            ++otherElem;
        }
    }

    // Удаляем элементы
    void delete_elements() {
#ifdef DEBUG
        std::cout << "\tУдаляем элементы. Size = " << m_size << "\n";
#endif
        while (m_size > 0) {
            pop_back();
        }
    }

};

template<typename T>
inline void print(const MyList<T> &list) {
    for (auto elem: list) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

#endif //CONTEINERS_MYLIST_H
