#include "TestMutableListSequence.h"

void mutableListSequenceTests() {
    int a[] = {67, 2, 8, 4, 51, 44, 89, 46, 0, 3};
    String s[6] = {"ss", "aa", "bb", "cc", "q", "w"};
    std::tuple tests{
            TestCase<bool>(
                    "MutableListSequenceUnqPtr: Инициализация",
                    true,
                    []() -> bool {
                        int a[] = {1, 2, 3, 4, 5};
                        auto sequence = MutableListSequenceUnqPtr<int>();
                        for (int i: a) {
                            sequence.append(i);
                        }
                        auto sequence1 = MutableListSequenceUnqPtr(a, 5);
                        return sequence1[2] == sequence[2];
                    }
            ),
            TestCase<int>(
                    "MutableListSequenceUnqPtr: Получение значения",
                    100,
                    []() -> int {
                        int a[] = {1, 224, 100, 4, 51};

                        auto sequence = MutableListSequenceUnqPtr(a, 5);
                        return sequence[2];
                    }
            ),
            TestCase<bool>(
                    "MutableListSequenceUnqPtr: Сложение",
                    true,
                    []() -> bool {
                        int a[] = {34, 55, 1, 35, 0, 9};
                        auto sequence1 = MutableListSequenceUnqPtr(a, 5);
                        auto sequence2 = MutableListSequenceUnqPtr<int>();
                        for (int i = 2; i < 10; i++) {
                            sequence2.prepend(i);
                        }
                        auto seq = sequence1 + sequence2;
                        return seq->size() == sequence1.size() + sequence2.size();
                    }
            ),
            TestCase<MutableListSequenceUnqPtr<int>>(
                    "MutableListSequenceUnqPtr: subSequence",
                    MutableListSequenceUnqPtr<int>(a, 4),
                    []() -> MutableListSequenceUnqPtr<int> {
                        int a[8] = {90, 67, 2, 8, 4, 8, 7, 123};
                        auto seq = MutableListSequenceUnqPtr<int>(a, 8);
                        return *seq.getSubsequence(1, 5);
                    }
            ),
            TestCase<MutableListSequenceUnqPtr<int>>(
                    "MutableListSequenceUnqPtr: Прибавление к существующей",
                    MutableListSequenceUnqPtr<int>(a, 6),
                    []() -> MutableListSequenceUnqPtr<int> {
                        int a[3] = {67, 2, 8};
                        auto list = LinkedListUP<int>();
                        list.append(4);
                        list.append(51);
                        list.append(44);
                        auto seq = MutableListSequenceUnqPtr<int>(a, 3);
                        seq += list;
                        return seq;
                    }
            )
    };

    util::forEach(tests, [](auto test) { test(); });
    std::cout << std::endl;
}
