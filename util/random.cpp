#include "random.h"

#include <cstdlib>
#include <ctime>
#include "Definition.h"


long randomIn(long from, long to) {
    srand(time(nullptr));
    return (random() % (to - from + 1)) + from;
}
int randomIntIn(int from, int to) {
    return (random() % (to - from + 1)) + from;
}

String randomStrGen(int length) {
    static String charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
    String result;
    result.resize(length);

    for (int i = 0; i < length; i++) {
        result[i] = charset[random() % charset.length()];
    }

    return result;
}
