#include "ShrdPtrTests.h"
#include "../../../pointer/ShrdPtr.h"
#include <cassert>
#include <iostream>

void ShrdPtrTests::runAllTests() {
    std::cout << "Запуск дополнительных тестов для ShrdPtr в парадигме ААА\n";

    testInitialization();
    testCopyConstructor();
    testCopyAssignment();
    testMoveConstructor();
    testMoveAssignment();
    testDereferenceOperator();
    testUseCount();
    testReset();
    testUnique();
    testNullBehavior();

    std::cout << "Все тесты для ShrdPtr успешно пройдены!\n";
}

void ShrdPtrTests::testInitialization() {
    ShrdPtr<int> shrd(new int(42));
    assert(*shrd == 42);
    assert(shrd.get() != nullptr);
    std::cout << "Тест 1 пройден: Инициализация ShrdPtr\n";
}

void ShrdPtrTests::testCopyConstructor() {
    ShrdPtr<int> shrd1(new int(10));
    ShrdPtr<int> shrd2(shrd1);

    assert(*shrd1 == 10);
    assert(*shrd2 == 10);
    assert(shrd1.get() == shrd2.get());
    std::cout << "Тест 2 пройден: Конструктор копирования\n";
}

void ShrdPtrTests::testCopyAssignment() {
    ShrdPtr<int> shrd1(new int(20));
    ShrdPtr<int> shrd2;

    shrd2 = shrd1;

    assert(*shrd1 == 20);
    assert(*shrd2 == 20);
    assert(shrd1.get() == shrd2.get());
    std::cout << "Тест 3 пройден: Оператор присваивания копии\n";
}

void ShrdPtrTests::testMoveConstructor() {
    ShrdPtr<int> shrd1(new int(30));
    ShrdPtr<int> shrd2(std::move(shrd1));

    assert(shrd1.get() == nullptr);
    assert(*shrd2 == 30);
    std::cout << "Тест 4 пройден: Конструктор перемещения\n";
}

void ShrdPtrTests::testMoveAssignment() {
    ShrdPtr<int> shrd1(new int(40));
    ShrdPtr<int> shrd2;

    shrd2 = std::move(shrd1);

    assert(shrd1.get() == nullptr);
    assert(*shrd2 == 40);
    std::cout << "Тест 5 пройден: Оператор присваивания перемещения\n";
}

void ShrdPtrTests::testDereferenceOperator() {
    ShrdPtr<int> shrd(new int(50));

    assert(*shrd == 50);
    *shrd = 60;
    assert(*shrd == 60);

    std::cout << "Тест 6 пройден: Операторы -> и *\n";
}

void ShrdPtrTests::testUseCount() {
    ShrdPtr<int> shrd1(new int(70));
    assert(shrd1.use_count() == 1);

    ShrdPtr<int> shrd2(shrd1);
    assert(shrd1.use_count() == 2);
    assert(shrd2.use_count() == 2);

    std::cout << "Тест 7 пройден: Подсчет ссылок\n";
}

void ShrdPtrTests::testReset() {
    ShrdPtr<int> shrd(new int(80));
    shrd.reset();

    assert(shrd.get() == nullptr);
    assert(shrd.use_count() == 0);
    std::cout << "Тест 8 пройден: Сброс ShrdPtr\n";
}

void ShrdPtrTests::testUnique() {
    ShrdPtr<int> shrd(new int(90));
    assert(shrd.unique());

    ShrdPtr<int> shrd2(shrd);
    assert(!shrd.unique());

    std::cout << "Тест 9 пройден: Проверка уникальности\n";
}

void ShrdPtrTests::testNullBehavior() {
    ShrdPtr<int> shrd;
    assert(shrd.get() == nullptr);
    std::cout << "Тест 10 пройден: Поведение ShrdPtr при null\n";
}
