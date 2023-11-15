//
// Created by Professional on 15.11.2023.
//

#pragma once

#include <algorithm>
#include <execution>
#include <list>
#include <map>


using Counter = std::map<std::string, std::size_t>; // Контейнер для подсчёта слов

std::string tolower(std::string_view str);

void count_words(std::istream &stream, Counter &counter);

Counter mt_count_words(std::string_view path);

void print_topk(std::ostream &stream, const Counter &counter, size_t k);

void print_topk1(std::ostream &stream, const Counter &counter, size_t k);