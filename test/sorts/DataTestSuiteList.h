#ifndef DATA_TEST_LIST_SUITE_H
#define DATA_TEST_LIST_SUITE_H

#include <string>
#include <cstddef>

class DataTestSuiteList {
public:
    // Тесты сортировки по возрасту и имени с использованием данных из файла
    void testSortByAgeFromFile(const std::string& filename, bool isJson);
    void testSortByNameFromFile(const std::string& filename, bool isJson);

    // Тесты сортировки по возрасту и имени с использованием сгенерированных данных
    void testSortByAgeGenerated(size_t dataSize);
    void testSortByNameGenerated(size_t dataSize);

    // Тест производительности для всех алгоритмов сортировки
    void testSortPerformanceForAllAlgorithms(size_t dataSize);

    // Запуск всех тестов
    void runAllTests();
};

#endif // DATA_TEST_LIST_SUITE_H