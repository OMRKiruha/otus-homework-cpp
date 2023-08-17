
#ifndef CONTEINERS_MYVECTOR_H
#define CONTEINERS_MYVECTOR_H

#include <cstddef>
#include <stdexcept>

#define DEBUG

template<typename T>
class MyVector {
//public:
//    template<typename U=T>
//    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
//
//    private:
//        explicit Iterator<T>(T *p) : p(p) {}
//
//    public:
//        Iterator<T>(const Iterator<T> &it) : p(it.p) {}
//
//        bool operator!=(Iterator<T> const &other) const {
//            return p != other.p;
//        }
//
//        bool operator==(Iterator<T> const &other) const {
//            return p == other.p;
//        }
//
//        typename Iterator<T>::reference operator*() const {
//            return *p;
//        }
//
//        Iterator<T> &operator++() {
//            ++p;
//            return *this;
//        }
//    private:
//        T *p;
//    };

public:
    // Конструктор без параметров
    MyVector() {
#ifdef DEBUG
        std::cout << "Конструктор без параметров (по умолчанию)\n";
#endif
        m_capacity = m_min_elements;
        m_begin = new T[m_capacity]();
        m_size = 0;
        m_end = m_begin;
        m_end_capacity = m_begin + m_capacity;
    }


    // Конструктор копирования
    MyVector(const MyVector<T> &other) {
#ifdef DEBUG
        std::cout << "Конструктор копирования\n";
#endif
        this->m_capacity = other.m_capacity;
        m_begin = new T[m_capacity]();
        copy_elements_from(other);
    }


    //Деструктор
    ~MyVector() {
#ifdef DEBUG
        std::cout << "Деструктор\n";
#endif
        delete_elements();
    }


    // Оператор присваивания копированием
    MyVector<T> &operator=(const MyVector<T> &other) {
#ifdef DEBUG
        std::cout << "Оператор присваивания копированием\n";
#endif
        //Проверка на присваивание самому себе
        if (other.m_begin == this->m_begin) { return *this; }
        // Если другой вектор содержит меньше информации чем ёмкость текущего
        // вектора, то избегаем аллокаций
        if (this->m_capacity >= other.m_size) {
            copy_elements_from(other);
            return *this;
        } else {
            // Если другой вектор не помещается в наш, то удаляем наш
            delete_elements();
            // и повторяем конструктор копирования
            this->m_capacity = other.m_capacity;
            m_begin = new T[m_capacity]();
            copy_elements_from(other);
            return *this;
        }
    }


    // Оператор присваивания перемещением
    MyVector<T> &operator=(MyVector<T> &&other) noexcept {
#ifdef DEBUG
        std::cout << "Оператор присваивания перемещением\n";
#endif
        // Очищаем текущий объект
        delete_elements();
        // Присваиваем чужие указатели и поля
        this->m_begin = other.m_begin;
        this->m_end = other.m_end;
        this->m_end_capacity = other.m_end_capacity;
        this->m_size = other.m_size;
        this->m_capacity = other.m_capacity;
    };


    size_t size() { return m_size; }


    // Оператор добавления элемента в конец вектора
    void push_back(const T &value) {
        // Если есть ещё место в векторе
        if (m_end != m_end_capacity) {
            *m_end = value;
            ++m_end;
            ++m_size;
        } else {
            // Если места для добавления нового элемента уже нет, то
            m_capacity *= m_multiplicator;  // Увеличиваем размер capacity
            T *temp = new T[m_capacity];    // Выделяем новый увеличенный массив
            copy_elements_to(temp);         // Копируем элементы в новый массив
            *(temp + m_size) = value;
            ++m_size;
            delete_elements();              // Удаляем старый массив
            this->m_begin = temp;           // Присваиваем новые указатели
            this->m_end = temp + m_size;
            this->m_end_capacity = temp + m_capacity;
        }
    }


    T *insert(T *pos, const T &value) {
        // Проверка на корректность переданного итератора
        if (pos >= m_begin && pos <= m_end) {
            // Вставка почти всегда вызывает реаллокацию всего массива
            // Только если это не вставка в конец и есть свободное место
            if (pos == m_end && m_end != m_end_capacity) {
                *m_end = value;
                T *new_pos = m_end;
                ++m_end;
                ++m_size;
                return new_pos;
            } else {
                // Проверяем необходимость увеличить массив
                if (m_size == m_capacity) {
                    m_capacity *= m_multiplicator;
                }
                T *temp = new T[m_capacity]; // Выделяем новый массив
                T *thisElem = this->m_begin;
                T *tempElem = temp;
                T *new_pos = nullptr;
                while (thisElem != m_end) {
                    if (pos == thisElem) {
                        *tempElem = value;
                        new_pos = tempElem;
                        ++tempElem;
                    }
                    *tempElem = *thisElem;
                    ++tempElem;
                    ++thisElem;
                }
                ++m_size;
                delete_elements();              // Удаляем старый массив
                this->m_begin = temp;           // Присваиваем новые указатели
                this->m_end = temp + m_size;
                this->m_end_capacity = temp + m_capacity;
                return new_pos;
            }
        }
        return nullptr;
    }


    T *erase(T *pos) {
        // Проверка на корректность переданного итератора
        if (pos >= m_begin && pos < m_end) {
            // Удаление почти всегда вызывает реаллокацию всего массива
            // Только если это не удаление из конца
            if (pos == (m_end - 1)) {
                --m_end;
                --m_size;
                return m_end;
            } else {
                T *temp = new T[m_capacity]; // Выделяем новый массив
                T *thisElem = this->m_begin;
                T *tempElem = temp;
                T *new_pos = nullptr;
                while (thisElem != m_end) {
                    if (thisElem == pos) {
                        ++thisElem;
                        *tempElem = *thisElem;
                        new_pos = tempElem;
                    } else {
                        *tempElem = *thisElem;
                    }
                    ++tempElem;
                    ++thisElem;
                }
                --m_size;
                delete_elements();              // Удаляем старый массив
                this->m_begin = temp;           // Присваиваем новые указатели
                this->m_end = temp + m_size;
                this->m_end_capacity = temp + m_capacity;
                return new_pos;
            }
        }
        return nullptr;
    }


    T &operator[](size_t index) {
        // Проверка на корректность переданного индекса элемента
        if (index < m_size) {
            return *(m_begin + index);
        }
        throw (std::out_of_range("Проверьте правильность индекса объекта MyVector"));
    }

    T* begin() { return m_begin; }

    T* end() { return m_end; }

    //Iterator<const T>& begin() const { return static_cast<const Iterator<const T> &>(m_begin); }

    //Iterator<const T>& end() const { return static_cast<const Iterator<const T> &>(m_end); }

//    T &operator*(Iterator<T> *iter) {
//        // Проверка на корректность переданного индекса элемента
//        if (iter >= m_begin && iter < m_end) {
//            return *iter;
//        }
//        throw (std::out_of_range("Проверьте правильность итератора объекта MyVector"));
//    }
//
//    T &get(Iterator<T> iter) {
//        // Проверка на корректность переданного индекса элемента
//        if (iter >= m_begin && iter < m_end) {
//            return *iter;
//        }
//        throw (std::out_of_range("Проверьте правильность итератора объекта MyVector"));
//    }

private:
    const size_t m_min_elements = 4;
    const double m_multiplicator = 1.5;
    T *m_begin = nullptr;
    T *m_end = nullptr;
    T *m_end_capacity = nullptr;
    size_t m_size{};
    size_t m_capacity{};

private:
    void copy_elements_from(const MyVector<T> &other) {
#ifdef DEBUG
        std::cout << "Копируем элементы из другого объекта\n";
#endif
        T *otherElem = other.m_begin;
        T *thisElem = this->m_begin;
        this->m_size = 0;
        while (otherElem != other.m_end) {
            *thisElem = *otherElem;
            ++otherElem;
            ++thisElem;
            ++(this->m_size);
        }
        this->m_end = thisElem;
        this->m_end_capacity = m_begin + m_capacity;
    }

    void copy_elements_to(T *temp) {
#ifdef DEBUG
        std::cout << "Копируем элементы в temp. Capacity = " << m_capacity << "\n";
#endif
        T *thisElem = this->m_begin;
        while (thisElem != m_end) {
            *temp = *thisElem;
            ++temp;
            ++thisElem;
        }
    }

    // Удаляем элементы
    void delete_elements() {
#ifdef DEBUG
        std::cout << "Удаляем элементы\n";
#endif
        delete[] m_begin;
        m_begin = nullptr;
        m_end = nullptr;
        m_end_capacity = nullptr;
    }


};

#endif //CONTEINERS_MYVECTOR_H
