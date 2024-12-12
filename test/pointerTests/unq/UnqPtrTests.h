#ifndef UNQ_PTR_TESTS_H
#define UNQ_PTR_TESTS_H

class UnqPtrTests {
public:
    // метод для запуска всех тестов
    void runAllTests();

private:
    // методы для конкретных тестов
    void testInitializationWithPointer();
    void testInitializationWithValueCopy();
    void testInitializationWithNullptr();
    void testMoveConstructor();
    void testPointerAssignment();
    void testSetValue();
    void testClearMethod();
    void testDereferenceOperator();
    void testRepeatedMove();
    void testDestructorCall();
    void testSelfAssignment();
    void testAssignNullptr();
};

#endif // UNQ_PTR_TESTS_H
