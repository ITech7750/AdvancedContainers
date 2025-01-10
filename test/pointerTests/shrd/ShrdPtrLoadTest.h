#ifndef SHRDPTRLOADTEST_H
#define SHRDPTRLOADTEST_H

#include <functional>

class ShrdPtrLoadTest {
public:
    ShrdPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount);
    void runTests();

private:
    size_t iterations;
    size_t objectSize;
    size_t threadCount;

    void stressTest();
    void multithreadedTest();
    void runThreads(const std::function<void()>& task);
};

#endif // SHRDPTLOADTEST_H
