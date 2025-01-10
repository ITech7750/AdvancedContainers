#ifndef SMRTPTRLOADTEST_H
#define SMRTPTRLOADTEST_H

#include <functional>

class SmrtPtrLoadTest {
public:
    SmrtPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount);
    void runTests();

private:
    size_t iterations;
    size_t objectSize;
    size_t threadCount;

    void stressTest();
    void multithreadedTest();

    void runThreads(const std::function<void()>& task);
};

#endif // SMRTPTRLOADTEST_H