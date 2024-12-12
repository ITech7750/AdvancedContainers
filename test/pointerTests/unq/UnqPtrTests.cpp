#include "UnqPtrTests.h"
#include "../../../pointer/UnqPtr.h"

#include <iostream>
#include <string>
#include <cassert>

void UnqPtrTests::runAllTests() {
    std::cout << "Запуск дополнительных тестов для UnqPtr в парадигме ААА\n";

    testInitializationWithPointer();
    testInitializationWithValueCopy();
    testInitializationWithNullptr();
    testMoveConstructor();
    testPointerAssignment();
    testSetValue();
    testClearMethod();
    testDereferenceOperator();
    testRepeatedMove();
    testDestructorCall();
    testSelfAssignment();
    testAssignNullptr();

    std::cout << "Все тесты успешно пройдены!\n";
}

void UnqPtrTests::testInitializationWithPointer() {
    UnqPtr<int> ptr(new int(42));
    assert(*ptr == 42);
    std::cout << "Тест 1 пройден: Инициализация с указателем\n";
}

void UnqPtrTests::testInitializationWithValueCopy() {
    UnqPtr<int> ptr(42);
    assert(*ptr == 42);
    std::cout << "Тест 2 пройден: Инициализация с копией значения\n";
}

void UnqPtrTests::testInitializationWithNullptr() {
    UnqPtr<int> ptr(nullptr);
    assert(ptr.getValue() == nullptr);
    std::cout << "Тест 3 пройден: Инициализация с nullptr\n";
}

void UnqPtrTests::testMoveConstructor() {
    UnqPtr<int> ptr1(new int(84));
    UnqPtr<int> ptr2 = std::move(ptr1);
    assert(ptr1.getValue() == nullptr);
    assert(*ptr2 == 84);
    std::cout << "Тест 4 пройден: Конструктор перемещения\n";
}

void UnqPtrTests::testPointerAssignment() {
    UnqPtr<int> ptr;
    ptr = new int(99);
    assert(*ptr == 99);
    std::cout << "Тест 5 пройден: Присваивание указателя\n";
}

void UnqPtrTests::testSetValue() {
    UnqPtr<int> ptr;
    ptr.setValue(128);
    assert(*ptr == 128);
    std::cout << "Тест 6 пройден: Установка значения через setValue\n";
}

void UnqPtrTests::testClearMethod() {
    UnqPtr<int> ptr(new int(256));
    ptr.clear();
    assert(ptr.getValue() == nullptr);
    std::cout << "Тест 7 пройден: Очистка через clear\n";
}

void UnqPtrTests::testDereferenceOperator() {
    UnqPtr<std::string> ptr(new std::string("UnqPtr"));
    assert(ptr->size() == 14);
    assert(*ptr == "UnqPtr");
    std::cout << "Тест 8 пройден: Операторы -> и *\n";
}

void UnqPtrTests::testRepeatedMove() {
    UnqPtr<int> ptr1(new int(512));
    UnqPtr<int> ptr2 = std::move(ptr1);
    UnqPtr<int> ptr3 = std::move(ptr2);
    assert(ptr1.getValue() == nullptr);
    assert(ptr2.getValue() == nullptr);
    assert(*ptr3 == 512);
    std::cout << "Тест 9 пройден: Повторное перемещение\n";
}

void UnqPtrTests::testDestructorCall() {
    bool destructorCalled = false;
    struct Test {
        bool* flag;
        ~Test() { *flag = true; }
    };

    {
        UnqPtr<Test> ptr(new Test{&destructorCalled});
    }

    assert(destructorCalled);
    std::cout << "Тест 10 пройден: Вызов деструктора\n";
}

void UnqPtrTests::testSelfAssignment() {
    UnqPtr<int> ptr(new int(64));
    ptr = std::move(ptr);
    assert(*ptr == 64); // Значение должно остаться прежним
    std::cout << "Тест 11 пройден: Самоприсваивание (перемещение)\n";
}

void UnqPtrTests::testAssignNullptr() {
    UnqPtr<int> ptr(new int(128));
    ptr = nullptr;
    assert(ptr.getValue() == nullptr);
    std::cout << "Тест 12 пройден: Присваивание nullptr\n";
}
