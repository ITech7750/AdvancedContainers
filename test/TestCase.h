#ifndef LABA1_TESTCASE_H
#define LABA1_TESTCASE_H

#include <functional>
#include <iostream>
#include <utility>
#include "../util/Definition.h"

template<class T>
class TestCase {
private:
    String _name;
    T _expect;
    T _result;
    std::function<T()> _received;

    bool run() {
        _result = _received();
        return _expect == _result;
    }

    void passedResponse() {
        std::cout << "+-" << std::endl;
        std::cout << "| " << _name << " - passed" << std::endl;
        std::cout << "| " << "Result: " << _result << std::endl;
    }

    void failedResponse() {
        std::cout << "+-" << std::endl;
        std::cout << "| " << _name << " - failed" << std::endl;
        std::cout << "| " << "Result: " << _result << std::endl;
        std::cout << "| " << "Expected: " << _expect << std::endl;
    }

public:
    explicit TestCase(
            String name,
            const T &expect,
            std::function<T()> received
    ) : _expect(expect),
        _result(expect),
        _received(received),
        _name(std::move(name)) {
    }

    bool invoke() {
        bool equals = run();
        if (equals) passedResponse();
        else failedResponse();
        return equals;
    }

    bool operator()() {
        return invoke();
    }
};

#endif //LABA1_TESTCASE_H
