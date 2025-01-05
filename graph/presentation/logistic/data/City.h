#ifndef LABA4_CITY_H
#define LABA4_CITY_H

#include <utility>

#include "../../../domain/model/vertex/VProperty.h"
#include "../../../../util/Definition.h"
#include "../../../../util/random.h"
#include <functional>

class City : public VProperty {
public:
    String name;
    size_t cargoToDrop;
    std::function<size_t(size_t)> duration;

    City(String _name, size_t _cargoToDrop, std::function<size_t(size_t)> _duration) : name(std::move(_name)),
                                                                                       cargoToDrop(_cargoToDrop),
                                                                                       duration(std::move(_duration)) {}

    bool operator==(const City &other) const {
        return name == other.name;
    }

    bool operator!=(const City &other) const {
        return name != other.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const City &thiz) {
        return os << thiz.name << "|" << thiz.cargoToDrop;
    }
};

inline City randomCity() {
    return {randomStrGen(randomIntIn(3, 10)), static_cast<size_t>(randomIn(10, 100)), [](size_t time) -> size_t {
        size_t minutes = time - (time / 1440) * 1440;
        size_t hour = minutes / 60;
        if (hour < 19 && hour > 16) {
            return randomIntIn(25, 40);
        } else return 20;
    }};
}

inline City getCityFromString(String data) {
    String n;
    String cargoToDrop;
    int current = 0;
    for (auto a: data) {
        if (a == '|') current++;
        else {
            switch (current) {
                case 0:
                    n += a;
                    break;
                case 1:
                    cargoToDrop += a;
                    break;
                default:
                    break;
            }
        }
    }
    return {n, static_cast<size_t>(std::stoi(cargoToDrop)), [](size_t hour) -> size_t {
        if (hour < 19 && hour > 16) {
            return randomIntIn(25, 40);
        } else return 20;
    }};
}

#endif //LABA4_CITY_H
