#ifndef LABA3_PERSON_H
#define LABA3_PERSON_H

#include <utility>
#include "../util/Definition.h"
#include "../util/random.h"
#include "../../collectionunqptr/dynamicarray/DynamicArray.h"
#include <iostream>
#include <random>


class Person {
private:
    String hash;
    size_t _hashCode;
    String _name;
    String _surname;
    int _birthdayYear;
    String _about;
public:

    Person(): _name(""), _surname(""), _birthdayYear(0), _about("") {}

    Person(
            const String &name,
            const String &surname,
            int birthdayYear,
            const String &about
    ) : _name(name), _surname(surname), _birthdayYear(birthdayYear), _about(about) {
        for (char c: name + surname + about) {
            _hashCode = _hashCode * 31 + c;
        }
        _hashCode += (birthdayYear / 100) * 31;
        _hashCode += (birthdayYear / 10) * 31;
        _hashCode += birthdayYear * 31;
        hash = std::to_string(_hashCode);
    }

    String getName() const {
        return _name;
    }

    String getSurname() const {
        return _surname;
    }

    int getAge() const {
        auto time = std::chrono::system_clock::now();
        return (time.time_since_epoch().count() / 31536000000000 + 1970) - _birthdayYear;
    }

    String getAbout() const {
        return _about;
    }

    unsigned int getBirthdayYear() const {
        return _birthdayYear;
    }

    int getHashCode() const {
        return _hashCode;
    }

    void setName(const String &name) {
        _name = name;
    }

    void setSurname(const String &surname) {
        _surname = surname;
    }

    void setAbout(const String &about) {
        _about = about;
    }

    void setBirthdayYear(unsigned int year) {
        _birthdayYear = year;
    }

    bool operator<(const Person &other) const {
        return _birthdayYear < other.getBirthdayYear();
    }

    bool operator>(const Person &other) const {
        return _birthdayYear > other.getBirthdayYear();
    }

    bool operator==(const Person &other) const {
        return _hashCode == other._hashCode;
    }

    bool operator!=(const Person &other) const {
        return _birthdayYear != other._birthdayYear;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &thiz) {
        os
                << thiz.getName() << String("|")
                << thiz.getSurname() << String("|")
                << std::to_string(thiz.getAge()) << String("|")
                << std::to_string(thiz.getBirthdayYear()) << String("|")
                << thiz.getAbout() << "\n";
        return os;
    }
};

class PersonBuilder {
public:
    Person build(const String &data) {
        std::vector<std::string> pData;
        int last = 0;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == '|') {
                pData.push_back(data.substr(last, i - last));
                last = i + 1;
            }
        }
        return Person(
                pData[0],
                pData[1],
                std::stoull(pData[2]),
                pData[3]
        );
    }

    Person randomPerson() {
        return Person(
                randomStrGen(10),
                randomStrGen(15),
                randomIn(1900, 2023),
                randomStrGen(250)
        );
    }
};

#endif //LABA3_PERSON_H
