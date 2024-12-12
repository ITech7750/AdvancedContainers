#ifndef SMRT_PTR_TESTS_H
#define SMRT_PTR_TESTS_H

class SmrtPtrTests {
public:
    void runAllTests();

private:
    void testInitialization();
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignment();
    void testMoveAssignment();
    void testReferenceCounting();
    void testDynamicPointerCast();
    void testStaticPointerCast();
    void testSelfAssignment();
    void testNullInitialization();
    void testClearLogic();
};

#endif // SMRT_PTR_TESTS_H
