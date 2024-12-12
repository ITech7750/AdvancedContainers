#include "smrtPtrTestsAB.h"
#include "../../TestCase.h"
#include "../../testClasses/A.h"
#include "../../testClasses/B.h"
#include "../../../util/tupleUtil.h"
#include "../../../pointer/SmrtPtr.h"


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
                    5,
                    []() -> size_t {
                        SmrtPtr<A> smrtPtr(new B(11));
                        auto smrt1 = smrtPtr;
                        auto smrt2 = smrtPtr;
                        auto smrt3 = smrt1;
                        auto smrt4 = smrt3;
                        return smrt4.getCount();
                    }
            ),
            TestCase<int>(
                    "SmrtPtr: Получение значения",
                    180,
                    []() -> int {
                        SmrtPtr<B> smrtPtr(new B(120));
                        auto smrt1 = smrtPtr;
                        return smrt1->getValueModified(-2);
                    }
            ),
            TestCase<B>(
                    "SmrtPtr: Получение объекта",
                    *b,
                    [b]() -> B {
                        SmrtPtr<B> smrtPtr(b);
                        return *smrtPtr;
                    }
            ),
            TestCase<int>(
                    "SmrtPtr: Изменение значения",
                    1111,
                    []() -> int {
                        SmrtPtr<int> smrtPtr(new int(11));
                        *smrtPtr += 1100;
                        return *smrtPtr;
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

