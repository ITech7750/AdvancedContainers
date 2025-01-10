#ifndef DICTIONARYTEST_H
#define DICTIONARYTEST_H

#include <string>
class DictionaryTest {
public:
    DictionaryTest(size_t testSize, size_t stringLength);
    void testAdd();
    void testGet();
    void testStatistic();

private:
    size_t _testSize;
    size_t _stringLength;

    std::string generateRandomString(size_t length);
};

#endif // DICTIONARYTEST_H
