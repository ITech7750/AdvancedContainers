#include "loadTestSeq.h"
#include "../../collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h"
#include "../loadTests/loadTests.h"
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

#define timeMls std::chrono::high_resolution_clock::time_point
#define clock std::chrono::high_resolution_clock
#define interval std::chrono::duration<double>

char* loadTestSeq(int k) {
    long amount = static_cast<long>(pow(10, k));

    timeMls start = clock::now();
    auto seq = new MutableArraySequenceUnqPtr<long>();

    fillSeq(seq, amount);

    delete seq;

    timeMls end = clock::now();
    interval total = end - start;

    char* result = new char[50];
    sprintf(result, "%f", total.count());

    std::ofstream resultsFile("../test/loadTestResults/load_test_seq_results.csv", std::ios_base::app);
    if (!resultsFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return nullptr;
    }

    std::cout << "Файл открыт успешно. Записываю данные...\n";
    resultsFile << "UnqPtr," << amount << "," << total.count() << "\n";
    resultsFile.close();
    std::cout << "Данные записаны в файл.\n";
    return result;
}
