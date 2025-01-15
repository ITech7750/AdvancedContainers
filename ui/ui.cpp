#include "ui.h"
#include "../test/pointerTests/smrt/smrtPtrTestsAB.h"
#include "../test/pointerTests/smrt/SmrtPtrTests.h"
#include "../test/pointerTests/smrt/SmrtPtrLoadTest.h"
#include "../test/pointerTests/unq/unqPtrTestsAB.h"
#include "../test/pointerTests/shrd/shrdPtrTestsAB.h"
#include "../test/mutableListSeq/MutableListSequenceUnqPtrTests.h"
#include "../test/loadSeq/loadTestSeq.h"
#include "../test/loadTests/loadTests.h"
#include "../test/pointerTests/shrd/ShrdPtrTests.h"
#include "../test/pointerTests/shrd/ShrdPtrLoadTest.h"
#include "../test/pointerTests/unq/UnqPtrTests.h"
#include "../test/pointerTests/unq/UnqPtrLoadTest.h"
#include "../test/pointerTests/weak/WeakPtrTests.h"
#include "../test/pointerTests/weak/WeakPtrLoadTest.h"
#include "../test/sorts/DataTestSuiteArray.h"
#include "../test/sorts/InteractiveTestSuiteArray.h"
#include "../test/sorts/DataTestSuiteList.h"
#include "../test/sorts/InteractiveTestSuiteList.h"
#include "../test/array/DynamicArrayTests.h"
#include "../test/mutableArraySeq/MutableArraySequenceUnqPtrTests.h"
#include "../test/graph/graphTests.h"
#include "../test/graph/undirectedGraphTest.h"
#include "../test/hashmap/HashMapTests.h"
#include "../test/hashmap/HashMapTest.h"
#include "../test/dict/DictionaryTest.h"
#include "../test/dict/DictionaryTests.h"
#include <iostream>



#include "../gistogram/model/dictionary/HashMap.h"
#include "../gistogram/model/dictionary/Dictionary.h"
#include <iostream>
#include <string>



void runGistTestsUI() {
    int choice;

    while (true) {
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "1. Работа с HashMap\n";
        std::cout << "2. Работа с Dictionary\n";
        std::cout << "3. Тесты Hash Map и Dictionary\n";
        std::cout << "0. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                runHashMapUI();
                break;
            case 2:
                runDictionaryUI();
                break;
            case 3:
                runGistTestsUITest();
            break;
            case 0:
                return;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, попробуйте снова.\n";
        }
    }
}





void runGistTestsUITest() {
    int choice;
    constexpr size_t TEST_SIZE = 100000;
    constexpr size_t STRING_LENGTH = 10;

    DictionaryTest testDict(10000, 10);
    HashMapTest testHash(TEST_SIZE, STRING_LENGTH);
    std::cout << "\n=== Меню тестов gistogram ===\n";
    std::cout << "1. Тест HashMap\n";
    std::cout << "2. Запуск нагрузочных тестов HashMap...\n";
    std::cout << "3. Тест Dictionary\n";
    std::cout << "4. Запуск нагрузочных тестов Dictionary...\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Запуск теста HashMap...\n";
            {
                HashMapTests hashMapTests;
                hashMapTests.runAllTests();
            }
            break;
        case 2:
            std::cout << "Запуск нагрузочных тестов HashMap...\n";
            testHash.runAllTests();

            break;
        case 3:
            std::cout << "Запуск теста Dictionary...\n";
            {
                DictionaryTests dictTests;
                dictTests.runAllTests();

            }
            break;
        case 4:
            std::cout << "Запуск нагрузочных тестов Dictionary...\n";
            testDict.testAdd();
            testDict.testGet();
            testDict.testStatistic();

            break;
        case 0:
            return;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
    }

}



void runHashMapUI() {
    HashMap<std::string, int> hashMap;
    int choice;

    while (true) {
        try {
            std::cout << "\n=== Работа с HashMap ===\n";
            std::cout << "1. Добавить пару (ключ, значение)\n";
            std::cout << "2. Получить значение по ключу\n";
            std::cout << "3. Проверить наличие ключа\n";
            std::cout << "4. Удалить ключ\n";
            std::cout << "5. Показать все ключи и значения\n";
            std::cout << "0. Вернуться в главное меню\n";
            std::cout << "Введите ваш выбор: ";
            std::cin >> choice;

            if (std::cin.fail()) throw std::invalid_argument("Некорректный ввод. Попробуйте снова.");

            switch (choice) {
                case 1: {
                    std::string key;
                    int value;
                    std::cout << "Введите ключ (строка): ";
                    std::cin >> key;
                    std::cout << "Введите значение (целое число): ";
                    std::cin >> value;
                    if (std::cin.fail()) throw std::invalid_argument("Некорректное значение. Попробуйте снова.");
                    hashMap.put(key, value);
                    std::cout << "Пара добавлена.\n";
                    break;
                }
                case 2: {
                    std::string key;
                    std::cout << "Введите ключ для поиска: ";
                    std::cin >> key;
                    if (hashMap.containsKey(key)) {
                        std::cout << "Значение: " << hashMap.get(key) << "\n";
                    } else {
                        std::cout << "Ключ не найден.\n";
                    }
                    break;
                }
                case 3: {
                    std::string key;
                    std::cout << "Введите ключ для проверки: ";
                    std::cin >> key;
                    std::cout << (hashMap.containsKey(key) ? "Ключ существует.\n" : "Ключ не найден.\n");
                    break;
                }
                case 4: {
                    std::string key;
                    std::cout << "Введите ключ для удаления: ";
                    std::cin >> key;
                    hashMap.remove(key);
                    std::cout << "Ключ удален (если существовал).\n";
                    break;
                }
                case 5: {
                    auto keys = hashMap.getKeys();
                    auto values = hashMap.getValues();
                    for (size_t i = 0; i < keys.size(); ++i) {
                        std::cout << keys[i] << ": " << values[i] << "\n";
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    std::cout << "Некорректный ввод. Пожалуйста, попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void runDictionaryUI() {
    Dictionary<std::string, int> dictionary;
    int choice;

    while (true) {
        try {
            std::cout << "\n=== Работа с Dictionary ===\n";
            std::cout << "1. Добавить пару (ключ, значение)\n";
            std::cout << "2. Получить значения по ключу\n";
            std::cout << "3. Добавить статистику для ключа\n";
            std::cout << "4. Удалить ключ\n";
            std::cout << "5. Показать все данные\n";
            std::cout << "0. Вернуться в главное меню\n";
            std::cout << "Введите ваш выбор: ";
            std::cin >> choice;

            if (std::cin.fail()) throw std::invalid_argument("Некорректный ввод. Попробуйте снова.");

            switch (choice) {
                case 1: {
                    std::string key;
                    int value;
                    std::cout << "Введите ключ (строка): ";
                    std::cin >> key;
                    std::cout << "Введите значение (целое число): ";
                    std::cin >> value;
                    if (std::cin.fail()) throw std::invalid_argument("Некорректное значение. Попробуйте снова.");
                    dictionary.add(Pair<std::string, int>(key, value));
                    std::cout << "Пара добавлена.\n";
                    break;
                }
                case 2: {
                    std::string key;
                    std::cout << "Введите ключ для поиска: ";
                    std::cin >> key;
                    if (dictionary.containsKey(key)) {
                        auto values = dictionary.get(key);
                        std::cout << "Значения: ";
                        for (const auto& val : values) {
                            std::cout << val << " ";
                        }
                        std::cout << "\n";
                    } else {
                        std::cout << "Ключ не найден.\n";
                    }
                    break;
                }
                case 3: {
                    std::string key;
                    std::cout << "Введите ключ для добавления статистики: ";
                    std::cin >> key;
                    dictionary.addStatistic(key, [](int a, int b) { return a + b; });
                    std::cout << "Статистика добавлена для ключа.\n";
                    break;
                }
                case 4: {
                    std::string key;
                    std::cout << "Введите ключ для удаления: ";
                    std::cin >> key;
                    dictionary.remove(key);
                    std::cout << "Ключ удален (если существовал).\n";
                    break;
                }
                case 5: {
                    if (dictionary.isEmpty()) {
                        std::cout << "Словарь пуст.\n";
                    } else {
                        std::cout << "Содержимое словаря:\n";
                        for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
                            const auto& entry = *it;
                            const auto& key = entry.getKey();
                            const auto& value = entry.getValue();
                            std::cout << key << ": " << value << "\n";
                        }
                    }
                    break;
                }

                case 0:
                    return;
                default:
                    std::cout << "Некорректный ввод. Пожалуйста, попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}




void runPointerTestsUI() {
    int choice;
    UnqPtrLoadTest loadTestUnq(1000000, 100, 4);
    SmrtPtrLoadTest loadTestSmrt(1000000, 100, 4);
    ShrdPtrLoadTest loadTestShrd(1000000, 100, 4);
    WeakPtrLoadTest loadTestWeak(1000000, 100, 4);
    std::cout << "\n=== Меню тестов указателей ===\n";
    std::cout << "1. Тест умных указателей (Smart Pointer)\n";
    std::cout << "2. Тест уникальных указателей (Unique Pointer)\n";
    std::cout << "3. Тест разделяемых указателей (Shared Pointer)\n";
    std::cout << "4. Тест weak указателей...\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;
    switch (choice) {
        case 1:
            std::cout << "Запуск теста умных указателей...\n";
            smrtPtrTesting();
            SmrtPtrTests().runAllTests();
            loadTestSmrt.runTests();
            break;
        case 2:
            std::cout << "Запуск тестов уникальных указателей...\n";
            uniqPtrTesting();
            UnqPtrTests().runAllTests();
            loadTestUnq.runTests();
            break;
        case 3:
            std::cout << "Запуск теста разделяемых указателей...\n";
            shrdPtrTesting();
            ShrdPtrTests().runAllTests();
            loadTestShrd.runTests();
            break;
        case 4:
            std::cout << "Запуск теста weak указателей...\n";
            WeakPtrTests::runAllTests();
            loadTestWeak.runTests();
        case 0:
            return;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
    }
}
void runSequenceTestsUI() {
    int choice;
    std::cout << "\n=== Меню тестов последовательностей ===\n";
    std::cout << "1. Тесты мутабельной последовательности на List\n";
    std::cout << "2. Тесты мутабельной последовательности на Array\n";
    std::cout << "3. Тесты Array\n";
    std::cout << "4. Нагрузочные тесты с корректируемой нагрузкой\n";
    std::cout << "5. Нагрузочные тесты\n";
    std::cout << "0. Вернуться в главное меню\n";
    std::cout << "Введите ваш выбор: ";
    std::cin >> choice;
    switch (choice) {
        case 1:
            std::cout << "Запуск теста мутабельной последовательности на базу List...\n";
            MutableListSequenceUnqPtrTests::runAllTests();
            break;
        case 2:
            std::cout << "Запуск теста мутабельной последовательности на базу Array...\n";
            MutableArraySequenceUnqPtrTests::runAllTests();
        break;
        case 3:
            std::cout << "Запуск тестов array...\n";
            DynamicArrayTests::runAllTests();
        break;
        case 4: {
            int k;
            std::cout << "Введите степень числа элементов (10^k): ";
            std::cin >> k;
            std::cout << "Запуск нагрузочного теста для 10^" << k << " элементов...\n";
            std::cout << loadTestSeq(k) << "\n";
            break;
        }
        case 5:
            std::cout << "Запуск нагрузочных тестов...\n";
            loadTests();
            break;
        case 0:
            return;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
    }
}


void runCreateUIList() {
    int choice;
    std::cout << "Интерактивный тестовый набор\n";
    std::cout << "1. Сгенерировать новые данные для теста\n";
    std::cout << "2. Загрузить существующие данные\n";
    std::cout << "Введите ваш выбор (1 или 2): ";
    std::cin >> choice;
    InteractiveTestSuiteList testSuite;
    MutableListSequenceUnqPtr<Person>* data = nullptr;
    if (choice == 1) {
        size_t count;
        std::cout << "Введите количество записей для генерации данных теста: ";
        std::cin >> count;
        data = testSuite.generateTestData(count);
        int formatChoice;
        std::cout << "Выберите формат для сохранения (1 - JSON, 2 - TXT): ";
        std::cin >> formatChoice;
        std::cin.ignore();
        std::string filename;
        std::cout << "Введите имя файла (или оставьте пустым для имени по умолчанию): ";
        std::getline(std::cin, filename);
        std::string savedFile = testSuite.saveTestData(data, formatChoice, filename);
        std::cout << "Данные сохранены в файл " << savedFile << ".\n";
    } else if (choice == 2) {
        int formatChoice;
        std::cout << "Выберите формат для загрузки (1 - JSON, 2 - TXT): ";
        std::cin >> formatChoice;
        std::cin.ignore();
        std::string filename;
        std::cout << "Введите имя файла (или оставьте пустым для имени по умолчанию): ";
        std::getline(std::cin, filename);
        if (filename.empty()) {
            filename = (formatChoice == 1) ? "../test/result/data.json" : "../test/result/data.txt";
        }
        try {
            data = testSuite.loadTestData(formatChoice, filename);
            std::cout << "Загружено " << data->size() << " записей из файла: " << filename << ".\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
            return;
        }
    } else {
        std::cout << "Некорректный выбор. Выход...\n";
        return;
    }
    for (size_t i = 0; i < data->size(); ++i) {
        const Person& p = data->get(i);
        std::cout << "Запись " << i + 1 << ": "
                  << p.firstName << " " << p.lastName << ", Возраст: " << p.age
                  << ", Адрес: " << p.address << ", Электронная почта: " << p.email << "\n";
    }
    delete data;
}


void runCreateUIArray() {
    int choice;
    std::cout << "Интерактивный тестовый набор\n";
    std::cout << "1. Сгенерировать новые данные для теста\n";
    std::cout << "2. Загрузить существующие данные\n";
    std::cout << "Введите ваш выбор (1 или 2): ";
    std::cin >> choice;
    InteractiveTestSuiteArray testSuite;
    MutableArraySequenceUnqPtr<Person>* data = nullptr;
    if (choice == 1) {
        size_t count;
        std::cout << "Введите количество записей для генерации данных теста: ";
        std::cin >> count;
        data = testSuite.generateTestData(count);
        int formatChoice;
        std::cout << "Выберите формат для сохранения (1 - JSON, 2 - TXT): ";
        std::cin >> formatChoice;
        std::cin.ignore();
        std::string filename;
        std::cout << "Введите имя файла (или оставьте пустым для имени по умолчанию): ";
        std::getline(std::cin, filename);
        std::string savedFile = testSuite.saveTestData(data, formatChoice, filename);
        std::cout << "Данные сохранены в файл " << savedFile << ".\n";
    } else if (choice == 2) {
        int formatChoice;
        std::cout << "Выберите формат для загрузки (1 - JSON, 2 - TXT): ";
        std::cin >> formatChoice;
        std::cin.ignore();
        std::string filename;
        std::cout << "Введите имя файла (или оставьте пустым для имени по умолчанию): ";
        std::getline(std::cin, filename);
        if (filename.empty()) {
            filename = (formatChoice == 1) ? "../test/result/data.json" : "../test/result/data.txt";
        }
        try {
            data = testSuite.loadTestData(formatChoice, filename);
            std::cout << "Загружено " << data->size() << " записей из файла: " << filename << ".\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
            return;
        }
    } else {
        std::cout << "Некорректный выбор. Выход...\n";
        return;
    }
    for (size_t i = 0; i < data->size(); ++i) {
        const Person& p = data->get(i);
        std::cout << "Запись " << i + 1 << ": "
                  << p.firstName << " " << p.lastName << ", Возраст: " << p.age
                  << ", Адрес: " << p.address << ", Электронная почта: " << p.email << "\n";
    }
    delete data;
}


void runSortTestsUIArray() {
    int choice;
    DataTestSuiteArray testSuiteArray;
    do {
        std::cout << "\n=== Меню тестов сортировок ===\n";
        std::cout << "1. Тест сортировки по возрасту из файла (JSON)\n";
        std::cout << "2. Тест сортировки по имени из файла (TXT)\n";
        std::cout << "3. Тест сортировки по возрасту (сгенерированные данные)\n";
        std::cout << "4. Тест сортировки по имени (сгенерированные данные)\n";
        std::cout << "5. Тест производительности всех алгоритмов сортировки\n";
        std::cout << "6. Выполнить все тесты\n";
        std::cout << "7. Генерация данных для тестов\n";
        std::cout << "0. Вернуться в главное меню\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                testSuiteArray.testSortByAgeFromFile("../test/result/data.json", true);
                break;
            case 2:
                testSuiteArray.testSortByNameFromFile("../test/result/data.txt", false);
                break;
            case 3: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteArray.testSortByAgeGenerated(dataSize);
                break;
            }
            case 4: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteArray.testSortByNameGenerated(dataSize);
                break;
            }
            case 5: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteArray.testSortPerformanceForAllAlgorithms(dataSize);
                break;
            }
            case 6:
                testSuiteArray.runAllTests();
                break;
            case 7:
                runCreateUIArray();
                break;
            case 0:
                return;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    } while (choice != 0);
}

void runSortTestsUIList() {
    int choice;
    DataTestSuiteList testSuiteList;
    do {
        std::cout << "\n=== Меню тестов сортировок ===\n";
        std::cout << "1. Тест сортировки по возрасту из файла (JSON)\n";
        std::cout << "2. Тест сортировки по имени из файла (TXT)\n";
        std::cout << "3. Тест сортировки по возрасту (сгенерированные данные)\n";
        std::cout << "4. Тест сортировки по имени (сгенерированные данные)\n";
        std::cout << "5. Тест производительности всех алгоритмов сортировки\n";
        std::cout << "6. Выполнить все тесты\n";
        std::cout << "7. Генерация данных для тестов\n";
        std::cout << "0. Вернуться в главное меню\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                testSuiteList.testSortByAgeFromFile("../test/result/data.json", true);
                break;
            case 2:
                testSuiteList.testSortByNameFromFile("../test/result/data.txt", false);
                break;
            case 3: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteList.testSortByAgeGenerated(dataSize);
                break;
            }
            case 4: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteList.testSortByNameGenerated(dataSize);
                break;
            }
            case 5: {
                size_t dataSize;
                std::cout << "Введите размер данных: ";
                std::cin >> dataSize;
                testSuiteList.testSortPerformanceForAllAlgorithms(dataSize);
                break;
            }
            case 6:
                testSuiteList.runAllTests();
                break;
            case 7:
                runCreateUIList();
                break;
            case 0:
                return;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    } while (choice != 0);
}



void runUISorts() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n===Меню сортировок===\n";
        std::cout << "1. Тесты сортировок на MutableListSequenceUnqPtr\n";
        std::cout << "2. Тесты сортировок на MutableArraySequenceUnqPtr\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                runSortTestsUIList();
            break;
            case 2:
                runSortTestsUIArray();
            break;
            case 3:
                std::cout << "Завершение программы...\n";
            break;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    }
}


void runUIGraf() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n===Меню графов===\n";
        std::cout << "1. GraphTests\n";
        std::cout << "2. UndirectedGraphTests\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                runGraphTests();
            break;
            case 2:
                runUndirectedGraphTests();
            break;
            case 3:
                std::cout << "Завершение программы...\n";
            break;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    }
}


void runUI() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n=== Главное меню ===\n";
        std::cout << "1. Тесты указателей\n";
        std::cout << "2. Тесты последовательностей\n";
        std::cout << "3. Тесты сортировок\n";
        std::cout << "4. Тесты графов\n";
        std::cout << "5. Работа с HashMap Dict и пр.\n";
        std::cout << "6. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                runPointerTestsUI();
                break;
            case 2:
                runSequenceTestsUI();
                break;
            case 3:
                runUISorts();
                break;
            case 4:
                runUIGraf();
            case 5:
                runGistTestsUI();
            case 6:
                std::cout << "Завершение программы...\n";
                break;
            default:
                std::cout << "Некорректный ввод. Пожалуйста, выберите действие из меню.\n";
        }
    }
}