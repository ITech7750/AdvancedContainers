#ifndef LAB2_PERSON_H
#define LAB2_PERSON_H

#include <string>
#include <sstream>
#include <utility>

class Person {
public:
    // Поля класса
    std::string firstName;
    std::string lastName;
    int age;
    std::string address;
    double height;
    double weight;
    int yearOfBirth;
    std::string phoneNumber;
    std::string email;
    std::string jobTitle;

    // Конструктор
    Person(std::string fn, std::string ln, int age, std::string addr, double h, double w, int yob,
           std::string phone, std::string email, std::string job)
            : firstName(std::move(fn)),
              lastName(std::move(ln)),
              age(age),
              address(std::move(addr)),
              height(h),
              weight(w),
              yearOfBirth(yob),
              phoneNumber(std::move(phone)),
              email(std::move(email)),
              jobTitle(std::move(job)) {}

    // Метод для строкового представления
    std::string toString() const {
        std::ostringstream oss;
        oss << firstName << " " << lastName
            << ", Age: " << age
            << ", Height: " << height
            << ", Weight: " << weight
            << ", Address: " << address
            << ", Job: " << jobTitle;
        return oss.str();
    }

    // Операторы сравнения
    bool operator==(const Person& other) const {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               age == other.age &&
               address == other.address &&
               height == other.height &&
               weight == other.weight &&
               yearOfBirth == other.yearOfBirth &&
               phoneNumber == other.phoneNumber &&
               email == other.email &&
               jobTitle == other.jobTitle;
    }

    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
};

#endif // LAB2_PERSON_H
