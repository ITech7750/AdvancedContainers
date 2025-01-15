#ifndef LABA3_HASHMAPTESTS_H
#define LABA3_HASHMAPTESTS_H

class HashMapTests {
public:
    void runAllTests();

private:
    void testPut();
    void testGet();
    void testContainsKey();
    void testRemove();
    void testSize();
    void testIsEmpty();
    void testClear();
    void testRehashing();
    void testIterator();
    void testIteratorEmptyMap();
    void testIteratorAfterClear();
    void testIteratorRehashing();
};

#endif // LABA3_HASHMAPTESTS_H