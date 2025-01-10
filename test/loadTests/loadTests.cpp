#include "loadTests.h"
#include "../../collectionunqptr/sequence/arraysequence/MutableArraySequenceUnqPtr.h"
#include "../../util/random.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <chrono>

#define timeMls std::chrono::high_resolution_clock::time_point
#define clock std::chrono::high_resolution_clock
#define interval std::chrono::duration<double>

void fillSeq(MutableSequence<long>* seq, long amount) {
    for (long i = 0; i < amount; i++) {
        seq->append(randomIn(-10000000, 10000000));
    }
    seq->insertAt(amount / 2, randomIn(-10000000, 10000000));
}

void testSequence(MutableSequence<long>* seq, int k, std::ofstream& file, const std::string& pointerType) {
    long amount = static_cast<long>(pow(10, k));

    timeMls start = clock::now();

    fillSeq(seq, amount);
    seq->insertAt(amount / 2, randomIn(-10000000, 10000000));

    timeMls end = clock::now();
    interval total = end - start;

    // вывод в консоль
    printf("| Количество элементов: %10ld - %2.5fs\n", amount, total.count());

    // запись в файл csv
    file << pointerType << "," << amount << "," << total.count() << "\n";
}

void loadTests() {
    std::ofstream resultsFile("../test/loadTestResults/load_test_results.csv");
    resultsFile << "PointerType,ElementCount,ExecutionTime\n";

    std::cout << "+---\n";
    std::cout << "| MutableArraySequenceUnqPtr с UnqPtr\n";
    for (int k = 3; k < 8; k++) {
        auto seq = new MutableArraySequenceUnqPtr<long>();
        testSequence(seq, k, resultsFile, "UniquePtr");
        delete seq;
    }

    std::cout << "+---\n";
    resultsFile.close();
}
