#ifndef LAB2_MUTABLELISTSEQUENCEUNQPTRTESTS_H
#define LAB2_MUTABLELISTSEQUENCEUNQPTRTESTS_H

class MutableListSequenceUnqPtrTests {
public:
    static void testDefaultConstructor();
    static void testParameterizedConstructor();
    static void testCopyConstructor();
    static void testMutableSequenceConstructor();
    static void testOperatorPlusEquals();
    static void testGetFirstAndLast();
    static void testGetAndSize();
    static void testIsEmpty();
    static void testGetSubsequence();
    static void testConcat();
    static void testAppend();
    static void testPrepend();
    static void testInsertAt();
    static void testSet();
    static void testOutOfRangeAccess();
    static void runAllTests();
};

#endif // LAB2_MUTABLELISTSEQUENCEUNQPTRTESTS_H
