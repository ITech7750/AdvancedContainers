#include "InteractiveTestSuiteArray.h"
#include "../helper/TestDataManagerArray.h"
#include <ctime>
#include <filesystem>

MutableArraySequenceUnqPtr<Person>* InteractiveTestSuiteArray::generateTestData(size_t count) {
    return TestDataManagerArray::generateTestData(count);
}

std::string InteractiveTestSuiteArray::saveTestData(MutableArraySequenceUnqPtr<Person>* data, int formatChoice, const std::string& filename) {
    std::string finalFilename = filename;

    if (finalFilename.empty()) {
        time_t now = time(nullptr);
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localtime(&now));

        finalFilename = (formatChoice == 1) ? "data_" + std::string(buffer) + ".json" : "data_" + std::string(buffer) + ".txt";
    }

    if (formatChoice == 1) {
        TestDataManagerArray::saveToJson(*data, finalFilename);
    } else {
        TestDataManagerArray::saveToTxt(*data, finalFilename);
    }

    return finalFilename;
}

MutableArraySequenceUnqPtr<Person>* InteractiveTestSuiteArray::loadTestData(int formatChoice, const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("Файл не найден: " + filename);
    }

    return (formatChoice == 1) ? TestDataManagerArray::loadFromJson(filename) : TestDataManagerArray::loadFromTxt(filename);
}
