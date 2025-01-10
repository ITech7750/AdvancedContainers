#include "WeakPtrTests.h"
#include "../../../pointer/WeakPtr.h"
#include "../../../pointer/ShrdPtr.h"
#include <cassert>
#include <iostream>

void WeakPtrTests::runAllTests() {
    std::cout << "Запуск тестов для WeakPtr в парадигме ААА\n";

    testInitialization();
    testLock();
    testExpired();
    testUseCount();
    testCopyConstructor();
    testCopyAssignment();
    testMoveConstructor();
    testMoveAssignment();

    std::cout << "Все тесты для WeakPtr успешно пройдены!\n";
}

void WeakPtrTests::testInitialization() {
    ShrdPtr<int> shrd(new int(100));
    WeakPtr<int> weak(shrd);

    assert(!weak.expired());
    assert(weak.use_count() == shrd.use_count());
    std::cout << "Тест 1 пройден: Инициализация WeakPtr\n";
}

void WeakPtrTests::testLock() {
    ShrdPtr<int> shrd(new int(110));
    WeakPtr<int> weak(shrd);

    ShrdPtr<int> locked = weak.lock();
    assert(*locked == 110);
    std::cout << "Тест 2 пройден: Метод lock\n";
}

void WeakPtrTests::testExpired() {
    WeakPtr<int> weak;
    {
        ShrdPtr<int> shrd(new int(120));
        weak = shrd; // Ппривязываем WeakPtr к ShrdPtr
        assert(!weak.expired());
    }
    std::cout << "Тест 3 пройден: Метод expired\n";
}


void WeakPtrTests::testUseCount() {
    ShrdPtr<int> shrd(new int(130));
    WeakPtr<int> weak(shrd);

    assert(weak.use_count() == 1);
    {
        ShrdPtr<int> shrd2(weak.lock());
        assert(weak.use_count() == 2);
    }
    assert(weak.use_count() == 1);
    std::cout << "Тест 4 пройден: Подсчет ссылок\n";
}

void WeakPtrTests::testCopyConstructor() {
    ShrdPtr<int> shrd(new int(140));
    WeakPtr<int> weak1(shrd);
    WeakPtr<int> weak2(weak1);

    assert(weak1.use_count() == weak2.use_count());
    std::cout << "Тест 5 пройден: Конструктор копирования\n";
}

void WeakPtrTests::testCopyAssignment() {
    ShrdPtr<int> shrd(new int(150));
    WeakPtr<int> weak1(shrd);
    WeakPtr<int> weak2;

    weak2 = weak1;

    assert(weak1.use_count() == weak2.use_count());
    std::cout << "Тест 6 пройден: Оператор присваивания копии\n";
}

void WeakPtrTests::testMoveConstructor() {
    ShrdPtr<int> shrd(new int(160));
    WeakPtr<int> weak1(shrd);
    WeakPtr<int> weak2(std::move(weak1));

    assert(weak1.expired());
    assert(!weak2.expired());
    std::cout << "Тест 7 пройден: Конструктор перемещения\n";
}

void WeakPtrTests::testMoveAssignment() {
    ShrdPtr<int> shrd(new int(170));
    WeakPtr<int> weak1(shrd);
    WeakPtr<int> weak2;

    weak2 = std::move(weak1);

    assert(weak1.expired());
    assert(!weak2.expired());
    std::cout << "Тест 8 пройден: Оператор присваивания перемещения\n";
}
