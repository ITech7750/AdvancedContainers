#include "shrdPtrTestsAB.h"
#include "../../TestCase.h"
#include "../../testClasses/A.h"
#include "../../testClasses/B.h"
#include "../../../util/tupleUtil.h"
#include "../../../pointer/ShrdPtr.h"

void shrdPtrTesting() {
    A *a = new A(12);
    A *a1 = new A(12);
    B *b = new B(100);

    std::tuple tests{
            TestCase<A *>(
                    "ShrdPtr: Инициализация",
                    a,
                    [&a]() -> A * {
                        UnqPtr<A> ptr(a);
                        ShrdPtr<A> shrdPtr(&ptr);
                        return shrdPtr.operator->();
                    }
            ),
            TestCase<bool>(
                    "ShrdPtr: Копирование указателя",
                    true,
                    []() -> bool {
                        B *b = new B(100);
                        UnqPtr<B> ptr(b);
                        ShrdPtr<B> shrd(&ptr);
                        ShrdPtr<B> shrd1 = shrd;
                        return (shrd1.getValue() == b);
                    }
            ),
            TestCase<int>(
                    "ShrdPtr: Изменение значения",
                    12 * 12,
                    []() -> int {
                        UnqPtr<int> ptr(new int(12));
                        ShrdPtr<int> shrd(&ptr);
                        *shrd *= 12;
                        return *ptr;
                    }
            ),
            TestCase<A>(
                    "ShrdPtr: Получение значения",
                    *a1,
                    [&a1]() -> A {
                        UnqPtr<A> ptr(a1);
                        ShrdPtr<A> shrd(&ptr);
                        return *shrd;
                    }
            ),
            TestCase<const B *>(
                    "ShrdPtr: Получение адреса",
                    b,
                    [&b]() -> const B * {
                        UnqPtr<B> ptr(b);
                        ShrdPtr<B> shrd(&ptr);
                        return shrd.getValue();
                    }
            ),
            TestCase<bool>(
                    "ShrdPtr: Работа со строками",
                    true,
                    []() -> bool {
                        UnqPtr<String> ptr("sdcsdvsd");
                        ShrdPtr<String> shrd(&ptr);
                        ShrdPtr<String> shrd1 = shrd;
                        return shrd1.getValue() == ptr.getValue();
                    }
            )

    };

    util::forEach(tests, [](auto test) { test(); });
    std::cout << std::endl;
}
