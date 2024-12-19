#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "../testClasses/Person.h"

// Компараторы для сортировки
int compareByAge(const Person& a, const Person& b);
int compareByName(const Person& a, const Person& b);
int compareByHeight(const Person& a, const Person& b);

#endif // TEST_HELPERS_H
