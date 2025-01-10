// UnqPtrLoadTest.h
#ifndef UNQPTRLOADTEST_H
#define UNQPTRLOADTEST_H

#include <functional>


class UnqPtrLoadTest {
public:
    UnqPtrLoadTest(size_t iterations, size_t objectSize, size_t threadCount);
    void runTests();

private:
    size_t iterations;
    size_t objectSize;
    size_t threadCount;

    void stressTest();
    void multithreadedTest();

    void runThreads(const std::function<void()>& task);
};

#endif // UNQPTRLOADTEST_H
