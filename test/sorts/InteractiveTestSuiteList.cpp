#include "InteractiveTestSuiteList.h"
#include "../helper/TestDataManagerList.h"
#include <ctime>
#include <filesystem>

MutableListSequenceUnqPtr<Person>* InteractiveTestSuiteList::generateTestData(size_t count) {
    return TestDataManagerList::generateTestData(count);
}

std::string InteractiveTestSuiteList::saveTestData(MutableListSequenceUnqPtr<Person>* data, int formatChoice, const std::string& filename) {
    std::string finalFilename = filename;

    if (finalFilename.empty()) {
        time_t now = time(nullptr);
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localtime(&now));

        finalFilename = (formatChoice == 1) ? "data_" + std::string(buffer) + ".json" : "data_" + std::string(buffer) + ".txt";
    }

    if (formatChoice == 1) {
        TestDataManagerList::saveToJson(*data, finalFilename);
    } else {
        TestDataManagerList::saveToTxt(*data, finalFilename);
    }

    return finalFilename;
}

MutableListSequenceUnqPtr<Person>* InteractiveTestSuiteList::loadTestData(int formatChoice, const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("Файл не найден: " + filename);
    }

    return (formatChoice == 1) ? TestDataManagerList::loadFromJson(filename) : TestDataManagerList::loadFromTxt(filename);
}
