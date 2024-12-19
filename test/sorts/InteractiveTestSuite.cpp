#include "InteractiveTestSuite.h"
#include "../helper/TestDataManager.h"
#include <ctime>
#include <filesystem>

MutableListSequenceUnqPtr<Person>* InteractiveTestSuite::generateTestData(size_t count) {
    return TestDataManager::generateTestData(count);
}

std::string InteractiveTestSuite::saveTestData(MutableListSequenceUnqPtr<Person>* data, int formatChoice, const std::string& filename) {
    std::string finalFilename = filename;

    if (finalFilename.empty()) {
        time_t now = time(nullptr);
        char buffer[32];
        strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", localtime(&now));

        finalFilename = (formatChoice == 1) ? "data_" + std::string(buffer) + ".json" : "data_" + std::string(buffer) + ".txt";
    }

    if (formatChoice == 1) {
        TestDataManager::saveToJson(*data, finalFilename);
    } else {
        TestDataManager::saveToTxt(*data, finalFilename);
    }

    return finalFilename;
}

MutableListSequenceUnqPtr<Person>* InteractiveTestSuite::loadTestData(int formatChoice, const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        throw std::runtime_error("Файл не найден: " + filename);
    }

    return (formatChoice == 1) ? TestDataManager::loadFromJson(filename) : TestDataManager::loadFromTxt(filename);
}
