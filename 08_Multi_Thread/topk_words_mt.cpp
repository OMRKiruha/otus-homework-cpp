// Read files and prints top k word by frequency

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <chrono>
#include <future>

#include "common_func.h"

const size_t TOPK = 10; // Размер выводимого списка наиболее встречающихся слов

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    Counter freq_dict;

    std::vector<std::future<Counter>> tasks;

    for (int i = 1; i < argc; ++i) {


        tasks.push_back(std::async(mt_count_words, argv[i]));
    }

    for (auto & task : tasks) {
        try {
            freq_dict.merge(task.get());
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    auto count = std::chrono::high_resolution_clock::now();
    print_topk1(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();

    auto count_ms = std::chrono::duration_cast<std::chrono::microseconds>(count - start);
    std::cout << "Count words time is " << count_ms.count() << " us\n";

    auto out_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - count);
    std::cout << "Output words time is " << out_ms.count() << " us\n";

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}