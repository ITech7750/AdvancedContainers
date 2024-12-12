#include "ui.h"
#include "../test/pointerTests/smrt/smrtPtrTestsAB.h"
#include "../test/pointerTests/smrt/SmrtPtrTests.h"
#include "../test/pointerTests/unq/unqPtrTestsAB.h"
#include "../test/pointerTests/shrd/shrdPtrTestsAB.h"
#include "../test/TestMutableListSequence.h"
#include "../test/loadTestSeq.h"
#include "../test/loadTests/loadTests.h"
#include "../test/pointerTests/shrd/ShrdPtrTests.h"
#include "../test/pointerTests/unq/UnqPtrTests.h"
#include <iostream>

void runUI() {
    int choice = 0;
    while (choice != 6) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Запустить тест умных указателей (Smart Pointer)\n";
        std::cout << "2. Запустить тест уникальных указателей (Unique Pointer)\n";
        std::cout << "3. Запустить тест разделяемых указателей (Shared Pointer)\n";
        std::cout << "4. Запустить тест мутабельной последовательности (mutable sequence)\n";
        std::cout << "5. Запустить нагрузочные тесты с корректируемой нагрузкой\n";
        std::cout << "6. Запустить нагрузочные тесты\n";
        std::cout << "7. Запустить все тесты сразу\n";
        std::cout << "0. Выйти\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Запуск теста умных указателей (Smart Pointer)...\n";
                smrtPtrTesting();
                SmrtPtrTests smrtPtrTests;
                smrtPtrTests.runAllTests();
                break;
            case 2:
                std::cout << "Запуск теста уникальных указателей (Unique Pointer)...\n";
                uniqPtrTesting();
                UnqPtrTests unqPtrTests;
                unqPtrTests.runAllTests();
                break;
            case 3:
                std::cout << "Запуск теста разделяемых указателей (Shared Pointer)...\n";
                shrdPtrTesting();
                ShrdPtrTests shrdPtrTests;
                shrdPtrTests.runAllTests();
                break;
            case 4:
                std::cout << "Запуск теста мутабельной последовательности (mutable sequence) ...\n";
                mutableListSequenceTests();
                break;
            case 5:
                int k;
                std::cout << "Введите степень числа элементов (10^k): ";
                std::cin >> k;
                std::cout << "Запуск нагрузочного теста для 10^" << k << " элементов...\n";
                std::cout << loadTestSeq(k) << "\n";
                break;
            case 6:
                std::cout << "Запуск нагрузочных тестов...\n";
                loadTests();
                break;
            case 7:
                std::cout << "Запуск всех тестов сразу...\n";
                smrtPtrTesting();
                uniqPtrTesting();
                shrdPtrTesting();
                mutableListSequenceTests();
                loadTests();
                break;
            case 0:
                std::cout << "Завершение программы...\n";
                break;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    }
}

