#ifndef LABA4_ROAD_H
#define LABA4_ROAD_H

#include <utility>

#include "../../../domain/model/edge/EProperty.h"
#include "../../../../util/Definition.h"
#include "../../../../util/random.h"
#include <functional>

class Road: public EProperty {
public:
    String name;
    size_t length;
    size_t maxSpeed;
    std::function<size_t(size_t cargo)> duration;

    Road(String _name, size_t _length, size_t _maxSpeed, std::function<size_t(size_t cargo)> _duration) :
            name(std::move(_name)), length(_length), maxSpeed(_maxSpeed), duration(std::move(_duration)) {}

    bool operator==(const Road &other) const {
        return name == other.name && length == other.length;
    }

    bool operator!=(const Road &other) const {
        return name != other.name && length == other.length;
    }

    size_t getDuration(size_t cargo) const {
        return static_cast<size_t>(60 * ((static_cast<double>(length)) / static_cast<double>(maxSpeed))) + duration(cargo);
    }

    friend std::ostream &operator<<(std::ostream &os, const Road &thiz) {
        return os << thiz.name << "|" << thiz.length << "|" << thiz.maxSpeed;
    }
};

inline Road randomRoad() {
    return Road(randomStrGen(randomIntIn(2, 5)), randomIntIn(10, 200), randomIntIn(60, 110), [](size_t cargo) -> size_t {
        return cargo / 100;
    });
}

inline Road getRoadFromString(String data) {
    String n;
    String length;
    String maxSpeed;
    int current = 0;
    for (auto a: data) {
        if (a == '|') current++;
        else {
            switch(current) {
                case 0:
                    n += a;
                    break;
                case 1:
                    length += a;
                    break;
                case 2:
                    maxSpeed += a;
                    break;
                default:
                    break;
            }
        }
    }
    return {n, static_cast<size_t>(std::stoi(length)), static_cast<size_t>(std::stoi(maxSpeed)), [](size_t cargo) -> size_t {
        return cargo / 100;
    }};
}

#endif //LABA4_ROAD_H
