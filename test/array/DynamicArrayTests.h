#ifndef DYNAMICARRAYTESTS_H
#define DYNAMICARRAYTESTS_H

class DynamicArrayTests {
public:
    static void testDefaultConstructor();
    static void testParameterizedConstructor();
    static void testCopyConstructor();
    static void testMoveConstructor();
    static void testAssignmentOperator();
    static void testAdd();
    static void testPrepend();
    static void testInsertAt();
    static void testResize();
    static void testShrinkToFit();
    static void testGetSubarray();
    static void testSwap();
    static void testSet();
    static void testGet();
    static void testOutOfRangeAccess();
    static void testClear();
    static void runAllTests();
};

#endif // DYNAMICARRAYTESTS_H
