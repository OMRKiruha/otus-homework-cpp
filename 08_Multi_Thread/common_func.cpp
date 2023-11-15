//
// Created by Professional on 15.11.2023.
//

#include "common_func.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <filesystem>


std::string clear(std::string_view str) {
    std::string clear_str;
    std::copy_if(std::cbegin(str), std::cend(str),
                 std::back_inserter(clear_str),
                 [](unsigned char ch) { return std::isalpha(ch); });
    return clear_str;
}

/**
 * @brief Преобразование слов в нижний регистр(работает ли с русскими словами?)
 * @param str - строка в любом виде
 * @return - строка в нижнем регистре
 */
std::string tolower(std::string_view str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

/**
 * @brief Каждое слово из потока переводим в нижний регистр и записываем в map<слово, счётчик>
 * @param stream
 * @param counter
 */
void count_words(std::istream &stream, Counter &counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](std::string_view s) { ++counter[clear(tolower(s))]; });
}

/**
 * @brief Каждое слово из потока переводим в нижний регистр и записываем в map<слово, счётчик>
 * @param stream
 * @param counter
 */
Counter mt_count_words(std::string_view path) {
    Counter counter;
    std::ifstream input{std::filesystem::path(path)};
    if (!input.is_open()) {
        std::cerr << "Failed to open file " << path << '\n';
        return counter;
    }
    std::for_each(std::istream_iterator<std::string>(input),
                  std::istream_iterator<std::string>(),
                  [&counter](std::string_view s) { ++counter[clear(tolower(s))]; });
    return counter;
}


/**
 * @brief Нахождение самых часто встречающихся слов и их вывод(default)
 * @param stream - поток вывода (std::cout)
 * @param counter - контейнер map<слово, количество>
 * @param k - размер выводимого списка "лидеров" часто встречающихся слов
 */
void print_topk(std::ostream &stream, const Counter &counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(std::execution::par_unseq,
                      std::begin(words), std::begin(words) + k, std::end(words),
                      [](auto &lhs, auto &rhs) { return lhs->second > rhs->second; });

    stream << "default" << '\n';
    std::for_each(
            std::begin(words), std::begin(words) + k,
            [&stream](const Counter::const_iterator &pair) {
                stream << std::setw(4) << pair->second << " " << pair->first
                       << '\n';
            });
}

/**
 * @brief Нахождение самых часто встречающихся слов и их вывод(оптимальнее по памяти аналогично по производительности)
 * @param stream - поток вывода (std::cout)
 * @param counter - контейнер map<слово, количество>
 * @param k - размер выводимого списка "лидеров" часто встречающихся слов
 */
void print_topk1(std::ostream &stream, const Counter &counter, const size_t k) {
    std::list<Counter::const_iterator> words{};
    words.push_back(counter.cbegin());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        // Если текущий элемент больше минимального, то обрабатываем его
        if (it->second > words.back()->second) {
            // Проходим по выходному контейнеру от меньшего к большему(от конца к началу)
            auto word = std::prev(words.end());
            while (word != words.begin() && (*std::prev(word))->second < it->second) {
                --word; // Находим позицию для вставки
            }
            words.insert(word, it);
            // Если размер контейнера больше требуемого, то удаляем последний элемент
            if (words.size() > k) words.pop_back();
        }
    }
    stream << "modify" << '\n';
    for (auto word: words) {
        // Находим максимальные значения за один проход по карте
        // Вывод
        stream << std::setw(4) << word->second << " " << word->first << '\n';
    }
}