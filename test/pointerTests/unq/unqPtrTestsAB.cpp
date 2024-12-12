#include "unqPtrTestsAB.h"
#include "../../TestCase.h"
#include "../../testClasses/A.h"
#include "../../testClasses/B.h"
#include "../../../util/tupleUtil.h"
#include "../../../pointer/SmrtPtr.h"
#include "../../../pointer/UnqPtr.h"


void uniqPtrTesting() {
    A *a = new A(12);
    B *b = new B(100);

    std::tuple tests{
            TestCase<A *>(
                    "UnqPtr: Инициализация",
                    a,
                    [&a]() -> A * {
                        UnqPtr<A> unqPtr(a);
                        return unqPtr.operator->();
                    }
            ),
            TestCase<bool>(
                    "UnqPtr: Перемещение указателя",
                    false,
                    []() -> bool {
                        B *b = new B(122);
                        UnqPtr<B> unqPtr(b);
                        UnqPtr<B> unqPtrCopy(*unqPtr);
                        return (unqPtrCopy.operator->() == b);
                    }
            ),
            TestCase<int>(
                    "UnqPtr: Перемещение указателя класса наследника",
                    102,
                    [&b]() -> int {
                        UnqPtr<B> unqPtr(b);
                        UnqPtr<A> unqPtrCopy(*unqPtr);
                        return unqPtrCopy->getValueModified(2);
                    }
            ),
            TestCase<int>(
                    "UnqPtr: Изменение значения",
                    12 * 12,
                    []() -> int {
                        UnqPtr<int> ptr(new int(12));
                        *ptr *= 12;
                        return *ptr;
                    }
            )

    };

    util::forEach(tests, [](auto test) { test(); });
    std::cout << std::endl;
}

