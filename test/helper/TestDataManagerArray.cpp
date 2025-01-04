#include "TestDataManagerArray.h"
#include <fstream>
#include <random>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MutableArraySequenceUnqPtr<Person>* TestDataManagerArray::generateTestData(size_t count) {
    auto array = new MutableArraySequenceUnqPtr<Person>();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ageDist(18, 65);
    std::uniform_real_distribution<> heightDist(150.0, 200.0);
    std::uniform_real_distribution<> weightDist(50.0, 100.0);
    std::uniform_int_distribution<> nameCharDist('A', 'Z');
    std::uniform_int_distribution<> nameLengthDist(5, 10);

    auto generateRandomString = [&](size_t length) {
        std::string result;
        for (size_t i = 0; i < length; ++i) {
            result += static_cast<char>(nameCharDist(gen));
        }
        return result;
    };

    for (size_t i = 0; i < count; ++i) {
        std::string firstName = generateRandomString(nameLengthDist(gen));
        std::string lastName = generateRandomString(nameLengthDist(gen));

        array->append(Person(
            firstName,
            lastName,
            ageDist(gen),
            "Address " + std::to_string(i),
            heightDist(gen),
            weightDist(gen),
            2000 - ageDist(gen),
            "123-456-" + std::to_string(rd() % 10000),
            firstName + lastName + "@example.com",
            "JobTitle" + std::to_string(i)
        ));
    }

    return array;
}

void TestDataManagerArray::saveToJson(const MutableArraySequenceUnqPtr<Person>& data, const std::string& filename) {
    json j;
    for (size_t i = 0; i < data.size(); ++i) {
        const Person& p = data.get(i); // Убедитесь, что get возвращает ссылку
        j.push_back({
            {"firstName", p.firstName},
            {"lastName", p.lastName},
            {"age", p.age},
            {"address", p.address},
            {"height", p.height},
            {"weight", p.weight},
            {"yearOfBirth", p.yearOfBirth},
            {"phoneNumber", p.phoneNumber},
            {"email", p.email},
            {"jobTitle", p.jobTitle}
        });
    }
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file for saving JSON");
    }
    file << j.dump(4);
}

MutableArraySequenceUnqPtr<Person>* TestDataManagerArray::loadFromJson(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        auto generatedData = generateTestData(10);
        saveToJson(*generatedData, filename);
        return generatedData;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open JSON file for loading");
    }

    json j;
    file >> j;

    auto array = new MutableArraySequenceUnqPtr<Person>();
    for (const auto& item : j) {
        array->append(Person(
            item["firstName"],
            item["lastName"],
            item["age"],
            item["address"],
            item["height"],
            item["weight"],
            item["yearOfBirth"],
            item["phoneNumber"],
            item["email"],
            item["jobTitle"]
        ));
    }
    return array;
}

void TestDataManagerArray::saveToTxt(const MutableArraySequenceUnqPtr<Person>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open file for saving text data");
    }
    for (size_t i = 0; i < data.size(); ++i) {
        const Person& p = data.get(i); // Убедитесь, что get возвращает ссылку
        file << p.firstName << "," << p.lastName << "," << p.age << "," << p.address << ","
             << p.height << "," << p.weight << "," << p.yearOfBirth << ","
             << p.phoneNumber << "," << p.email << "," << p.jobTitle << "\n";
    }
}

MutableArraySequenceUnqPtr<Person>* TestDataManagerArray::loadFromTxt(const std::string& filename) {
    if (!std::filesystem::exists(filename)) {
        auto generatedData = generateTestData(10);
        saveToTxt(*generatedData, filename);
        return generatedData;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Failed to open text file for loading");
    }

    auto array = new MutableArraySequenceUnqPtr<Person>();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string fn, ln, addr, phone, email, job;
        int age, yob;
        double height, weight;

        std::getline(ss, fn, ',');
        std::getline(ss, ln, ',');
        ss >> age; ss.ignore();
        std::getline(ss, addr, ',');
        ss >> height; ss.ignore();
        ss >> weight; ss.ignore();
        ss >> yob; ss.ignore();
        std::getline(ss, phone, ',');
        std::getline(ss, email, ',');
        std::getline(ss, job, ',');

        array->append(Person(fn, ln, age, addr, height, weight, yob, phone, email, job));
    }
    return array;
}
