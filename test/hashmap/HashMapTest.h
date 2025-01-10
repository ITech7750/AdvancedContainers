#ifndef HASHMAPTEST_H
#define HASHMAPTEST_H

#include <string>


class HashMapTest {
public:
    HashMapTest(size_t testSize, size_t stringLength);
    void testInsert();
    void testGet();
    void testContains();

private:
    size_t _testSize;
    size_t _stringLength;

    std::string generateRandomString(size_t length);
};

#endif // HASHMAPTEST_H
