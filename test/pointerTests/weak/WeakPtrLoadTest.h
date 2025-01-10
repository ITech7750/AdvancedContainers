#ifndef WEAKPTRLOADTEST_H
#define WEAKPTRLOADTEST_H

#include <functional>

class WeakPtrLoadTest {
public:
    WeakPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount);
    void runTests();

private:
    size_t iterations;
    size_t objectSize;
    size_t threadCount;

    void stressTest();
    void multithreadedTest();

    void runThreads(const std::function<void()>& task);
};

#endif // WEAKPTRLOADTEST_H
