#ifndef SHRD_PTR_TESTS_H
#define SHRD_PTR_TESTS_H

class ShrdPtrTests {
public:
    void runAllTests();

private:
    void testInitialization();
    void testCopyConstructor();
    void testCopyAssignment();
    void testDereferenceOperator();
    void testClearOrigin();
    void testNullBehavior();
    void testMoveConstructor();
    void testMoveAssignment();
    void testUseCount();
    void testReset();
    void testUnique();



};

#endif // SHRD_PTR_TESTS_H
