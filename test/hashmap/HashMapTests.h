#ifndef HASHMAPTESTS_H
#define HASHMAPTESTS_H

class HashMapTests {
public:
    static void runAllTests();
private:
    static void testInsertAndGet();
    static void testInsertDuplicateKey();
    static void testContains();
    static void testOperatorAccess();
    static void testGetKeys();
    static void testGetNonExistentKey();
};

#endif // HASHMAPTESTS_H
