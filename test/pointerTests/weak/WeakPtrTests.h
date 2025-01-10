#ifndef LABA1_WEAKPTRTESTS_H
#define LABA1_WEAKPTRTESTS_H

class WeakPtrTests {
public:
    static void runAllTests();

private:
    static void testInitialization();
    static void testLock();
    static void testExpired();
    static void testUseCount();
    static void testCopyConstructor();
    static void testCopyAssignment();
    static void testMoveConstructor();
    static void testMoveAssignment();
};

#endif //LABA1_WEAKPTRTESTS_H
