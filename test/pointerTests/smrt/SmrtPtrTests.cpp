#include "SmrtPtrTests.h"
#include "../../../pointer/SmrtPtr.h"
#include <iostream>
#include <cassert>

void SmrtPtrTests::runAllTests() {
    std::cout << "Запуск дополнительных тестов для SmrtPtr в парадигме ААА\n";

    testInitialization();
    testCopyConstructor();
    testMoveConstructor();
    testCopyAssignment();
    testMoveAssignment();
    testReferenceCounting();
    testDynamicPointerCast();
    testStaticPointerCast();
    testSelfAssignment();
    testNullInitialization();
    testClearLogic();

    std::cout << "Все тесты для SmrtPtr успешно пройдены!\n";
}

void SmrtPtrTests::testInitialization() {
    SmrtPtr<int> ptr(new int(42));
    assert(*ptr == 42);
    assert(ptr.getCount() == 1);
    std::cout << "Тест 1 пройден: Инициализация с указателем\n";
}

void SmrtPtrTests::testCopyConstructor() {
    SmrtPtr<int> ptr1(new int(10));
    SmrtPtr<int> ptr2(ptr1);
    assert(ptr1.getCount() == 2);
    assert(ptr2.getCount() == 2);
    assert(*ptr1 == *ptr2);
    std::cout << "Тест 2 пройден: Конструктор копирования\n";
}

void SmrtPtrTests::testMoveConstructor() {
    SmrtPtr<int> ptr1(new int(15));
    SmrtPtr<int> ptr2(std::move(ptr1));
    assert(ptr1.getReferenceCount() == nullptr);
    assert(ptr2.getCount() == 1);
    assert(*ptr2 == 15);
    std::cout << "Тест 3 пройден: Конструктор перемещения\n";
}

void SmrtPtrTests::testCopyAssignment() {
    SmrtPtr<int> ptr1(new int(20));
    SmrtPtr<int> ptr2;
    ptr2 = ptr1;
    assert(ptr1.getCount() == 2);
    assert(ptr2.getCount() == 2);
    assert(*ptr1 == *ptr2);
    std::cout << "Тест 4 пройден: Оператор присваивания копии\n";
}

void SmrtPtrTests::testMoveAssignment() {
    SmrtPtr<int> ptr1(new int(30));
    SmrtPtr<int> ptr2;
    ptr2 = std::move(ptr1);
    assert(ptr1.getReferenceCount() == nullptr);
    assert(ptr2.getCount() == 1);
    assert(*ptr2 == 30);
    std::cout << "Тест 5 пройден: Оператор присваивания перемещения\n";
}

void SmrtPtrTests::testReferenceCounting() {
    SmrtPtr<int> ptr(new int(50));
    {
        SmrtPtr<int> ptr2(ptr);
        SmrtPtr<int> ptr3(ptr);
        assert(ptr.getCount() == 3);
    }
    assert(ptr.getCount() == 1);
    std::cout << "Тест 6 пройден: Подсчет ссылок\n";
}

void SmrtPtrTests::testDynamicPointerCast() {
    struct Base { virtual ~Base() = default; };
    struct Derived : Base { int value = 70; };

    SmrtPtr<Derived> derivedPtr(new Derived());
    SmrtPtr<Base> basePtr = derivedPtr;

    auto castedPtr = basePtr.dynamic_pointer_cast<Derived>();
    assert(castedPtr->value == 70);
    assert(castedPtr.getCount() == basePtr.getCount());
    std::cout << "Тест 7 пройден: Dynamic Pointer Cast\n";
}

void SmrtPtrTests::testStaticPointerCast() {
    struct Base { virtual ~Base() = default; };
    struct Derived : Base { int value = 80; };

    SmrtPtr<Derived> derivedPtr(new Derived());
    SmrtPtr<Base> basePtr = derivedPtr;

    auto castedPtr = basePtr.static_pointer_cast<Derived>();
    assert(castedPtr->value == 80);
    assert(castedPtr.getCount() == basePtr.getCount());
    std::cout << "Тест 8 пройден: Static Pointer Cast\n";
}

void SmrtPtrTests::testSelfAssignment() {
    SmrtPtr<int> ptr(new int(90));
    ptr = ptr; // Проверка самоприсваивания
    assert(ptr.getCount() == 1);
    assert(*ptr == 90);
    std::cout << "Тест 9 пройден: Самоприсваивание\n";
}

void SmrtPtrTests::testNullInitialization() {
    SmrtPtr<int> ptr;
    assert(ptr.getReferenceCount() == nullptr);
    assert(ptr.getCount() == 0);
    std::cout << "Тест 10 пройден: Инициализация nullptr\n";
}

void SmrtPtrTests::testClearLogic() {
    SmrtPtr<int> ptr(new int(100));
    ptr = nullptr; // Очистка через присвоение nullptr
    assert(ptr.getReferenceCount() == nullptr);
    assert(ptr.getCount() == 0);
    std::cout << "Тест 11 пройден: Очистка через nullptr\n";
}
