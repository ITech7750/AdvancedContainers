#include "random.h"

long randomIn(long from, long to) {
    srand(time(nullptr));
    return (random() % (to - from + 1)) + from;
}
