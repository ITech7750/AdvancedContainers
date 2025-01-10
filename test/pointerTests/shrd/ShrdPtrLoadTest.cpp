#include "ShrdPtrLoadTest.h"
#include "../../../pointer/ShrdPtr.h"
#include <memory>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

ShrdPtrLoadTest::ShrdPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount)
    : iterations(iterations), objectSize(objectSize), threadCount(threadCount) {}

void ShrdPtrLoadTest::runTests() {
    std::cout << "Running stress test..." << std::endl;
    stressTest();

    std::cout << "Running multithreaded test..." << std::endl;
    multithreadedTest();
}

void ShrdPtrLoadTest::stressTest() {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < iterations; ++i) {
        int *ptr(new int[objectSize]);
        for (size_t j = 0; j < objectSize; ++j) {
            ptr[j] = static_cast<int>(j);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Stress test completed in " << duration.count() << " seconds." << std::endl;
}

void ShrdPtrLoadTest::multithreadedTest() {
    auto task = [this]() {
        for (size_t i = 0; i < iterations / threadCount; ++i) {
            int *ptr(new int[objectSize]);
            for (size_t j = 0; j < objectSize; ++j) {
                ptr[j] = static_cast<int>(j);
            }
        }
    };

    runThreads(task);
}

void ShrdPtrLoadTest::runThreads(const std::function<void()>& task) {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(task);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Multithreaded test completed." << std::endl;
}
