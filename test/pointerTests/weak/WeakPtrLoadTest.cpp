#include "WeakPtrLoadTest.h"
#include "../../../pointer/ShrdPtr.h"
#include "../../../pointer/WeakPtr.h"
#include <memory>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

WeakPtrLoadTest::WeakPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount)
    : iterations(iterations), objectSize(objectSize), threadCount(threadCount) {}

void WeakPtrLoadTest::runTests() {
    std::cout << "Running stress test..." << std::endl;
    stressTest();

    std::cout << "Running multithreaded test..." << std::endl;
    multithreadedTest();
}

void WeakPtrLoadTest::stressTest() {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < iterations; ++i) {
        ShrdPtr<int> sharedPtr(new int[objectSize]);
        WeakPtr<int> weakPtr(sharedPtr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Stress test completed in " << duration.count() << " seconds." << std::endl;
}

void WeakPtrLoadTest::multithreadedTest() {
    auto task = [this]() {
        for (size_t i = 0; i < iterations / threadCount; ++i) {
            ShrdPtr<int> sharedPtr(new int[objectSize]);
            WeakPtr<int> weakPtr(sharedPtr);
        }
    };

    runThreads(task);
}

void WeakPtrLoadTest::runThreads(const std::function<void()>& task) {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < threadCount; ++i) {
        threads.emplace_back(task);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Multithreaded test completed." << std::endl;
}
