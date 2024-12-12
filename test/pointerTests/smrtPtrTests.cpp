#include "smrtPtrTests.h"
void smrtPtrTesting() {
    A *a = new A(12);
    B *b = new B(100);

    std::tuple tests = {
            TestCase<A*>(
                    "SmrtPtr: Инициализация",
                    a,
                    [&a]() -> A* {
                        SmrtPtr<A> smrtPtr(a);
                        return smrtPtr.operator->();
                    }
            ),
            TestCase<size_t>(
                    "SmrtPtr: Подсчет количества указателей",
                    5, // Мы ожидаем 5 копий SmrtPtr
                    []() -> size_t {
                        SmrtPtr<A> smrtPtr(new B(11)); // Инициализация с объектом B
                        auto smrt1 = smrtPtr; // Копируем
                        auto smrt2 = smrtPtr; // Еще одна копия
                        auto smrt3 = smrt1;   // Еще одна копия
                        auto smrt4 = smrt3;   // И еще одна
                        return smrt4.getCount(); // Счетчик ссылок
                    }
            ),
            TestCase<int>(
                    "SmrtPtr: Получение значения",
                    180, // Мы ожидаем результат 180 после вызова getValueModified(-2)
                    []() -> int {
                        SmrtPtr<B> smrtPtr(new B(120)); // Инициализация объекта B со значением 120
                        auto smrt1 = smrtPtr; // Копирование указателя
                        return smrt1->getValueModified(-2); // Получаем значение с изменением
                    }
            ),
            TestCase<B>(
                    "SmrtPtr: Получение объекта",
                    *b, // Ожидаем объект b
                    [b]() -> B {
                        SmrtPtr<B> smrtPtr(b); // Инициализация с объектом b
                        return *smrtPtr; // Разыменование указателя для получения объекта
                    }
            ),
            TestCase<int>(
                    "SmrtPtr: Изменение значения",
                    1111, // Мы ожидаем результат 1111
                    []() -> int {
                        SmrtPtr<int> smrtPtr(new int(11)); // Инициализация с указателем на int
                        *smrtPtr += 1100; // Изменение значения
                        return *smrtPtr; // Возвращаем новое значение
                    }
            ),
            TestCase<bool>(
                    "SmrtPtr: динамический cast",
                    true,
                    [&]() -> bool {
                        SmrtPtr<A> basePtr(new B(200));
                        auto derivedPtr = basePtr.dynamic_pointer_cast<B>();
                        return derivedPtr.operator->() != nullptr;
                    }
            ),

            TestCase<bool>(
                    "SmrtPtr: cтатический  cast",
                    true,
                    [&]() -> bool {
                        SmrtPtr<A> basePtr(new B(300));
                        auto derivedPtr = basePtr.static_pointer_cast<B>();
                        return derivedPtr.operator->() != nullptr;
                    }
            )
    };

    util::forEach(tests, [](auto test) { test(); });
    std::cout << std::endl;
}

