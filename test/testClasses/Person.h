#ifndef LAB2_PERSON_H
#define LAB2_PERSON_H

#include <string>
#include <sstream>
#include <utility>

class Person {
public:
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

    // Конструктор по умолчанию
    Person()
        : firstName("Unknown"),
          lastName("Unknown"),
          age(0),
          address("Unknown"),
          height(0.0),
          weight(0.0),
          yearOfBirth(0),
          phoneNumber("Unknown"),
          email("Unknown"),
          jobTitle("Unknown") {}

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

    std::string toString() const {
        std::ostringstream oss;
        oss << firstName << " " << lastName
            << ", Age: " << age
            << ", Height: " << height
            << ", Weight: " << weight
            << ", Address: " << address
            << ", Job: " << jobTitle
            << ", Phone: " << phoneNumber
            << ", Email: " << email;
        return oss.str();
    }

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
