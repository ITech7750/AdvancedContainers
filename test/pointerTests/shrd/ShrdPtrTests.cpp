#include "ShrdPtrTests.h"
#include "../../../pointer/ShrdPtr.h"
#include <cassert>
#include <iostream>

void ShrdPtrTests::runAllTests() {
    std::cout << "Запуск дополнительных тестов для ShrdPtr в парадигме ААА\n";

    testInitialization();
    testCopyConstructor();
    testCopyAssignment();
    testDereferenceOperator();
    testClearOrigin();
    testNullBehavior();

    std::cout << "Все тесты для ShrdPtr успешно пройдены!\n";
}

void ShrdPtrTests::testInitialization() {
    UnqPtr<int> unq(new int(42));
    ShrdPtr<int> shrd(&unq);

    assert(*shrd == 42);
    assert(shrd.getValue() == unq.getValue());
    std::cout << "Тест 1 пройден: Инициализация ShrdPtr\n";
}

void ShrdPtrTests::testCopyConstructor() {
    UnqPtr<int> unq(new int(10));
    ShrdPtr<int> shrd1(&unq);
    ShrdPtr<int> shrd2(shrd1);

    assert(*shrd1 == 10);
    assert(*shrd2 == 10);
    assert(shrd1.getValue() == shrd2.getValue());
    std::cout << "Тест 2 пройден: Конструктор копирования\n";
}

void ShrdPtrTests::testCopyAssignment() {
    UnqPtr<int> unq(new int(20));
    ShrdPtr<int> shrd1(&unq);
    ShrdPtr<int> shrd2;

    shrd2 = shrd1;

    assert(*shrd1 == 20);
    assert(*shrd2 == 20);
    assert(shrd1.getValue() == shrd2.getValue());
    std::cout << "Тест 3 пройден: Оператор присваивания копии\n";
}

void ShrdPtrTests::testDereferenceOperator() {
    UnqPtr<int> unq(new int(30));
    ShrdPtr<int> shrd(&unq);

    assert(*shrd == 30);

    // Изменяем значение через указатель
    *const_cast<int*>(shrd.getValue()) = 40;
    assert(*shrd == 40);

    std::cout << "Тест 4 пройден: Операторы -> и *\n";
}

void ShrdPtrTests::testClearOrigin() {
    UnqPtr<int> unq(new int(50));
    ShrdPtr<int> shrd(&unq);

    shrd.clearOrigin();

    assert(unq.getValue() == nullptr);
    assert(shrd.getValue() == nullptr);
    std::cout << "Тест 5 пройден: Очистка оригинального UnqPtr\n";
}

void ShrdPtrTests::testNullBehavior() {
    ShrdPtr<int> shrd;

    assert(shrd.getValue() == nullptr);
    std::cout << "Тест 6 пройден: Поведение ShrdPtr при null\n";
}
