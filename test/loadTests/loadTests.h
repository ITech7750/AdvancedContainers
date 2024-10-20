#ifndef LABA1_LOADTESTS_H
#define LABA1_LOADTESTS_H

#include "../../collectionunqptr/sequence/linkedlistsequence/MutableListSequenceUnqPtr.h"
#include "../../collection/sequence/linkedlistsequence/MutableListSequence.h"
#include "../../util/random.h"
#include <cmath>
#include <fstream>
#include <memory>
#include <iostream>
#include <ctime>
#include <chrono>

void fillSeq(MutableSequence<long>* seq, long amount);
void testSequence(MutableSequence<long>* seq, int k, std::ofstream& file, const std::string& pointerType);
void loadTests();

#endif //LABA1_LOADTESTS_H
