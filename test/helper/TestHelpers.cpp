#include "TestHelpers.h"

int compareByAge(const Person& a, const Person& b) {
    return a.age - b.age;
}

int compareByName(const Person& a, const Person& b) {
    return a.firstName.compare(b.firstName);
}

int compareByHeight(const Person& a, const Person& b) {
    if (a.height < b.height) return -1;
    if (a.height > b.height) return 1;
    return 0;
}
