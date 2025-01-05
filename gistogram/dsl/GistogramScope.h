#ifndef LABA3_GISTOGRAMSCOPE_H
#define LABA3_GISTOGRAMSCOPE_H

#include <iostream>
#include <functional>
#include "../model/Gistogram.h"

template <class K, class V>
class GistogramScope {
private:
    Gistogram<K, V> gistogram;
    std::function<V(V, V)> _statPredicate;
    bool statistic = false;
public:
    GistogramScope(): gistogram(Gistogram<K, V>()) {

    }

    GistogramScope* addData(std::initializer_list<V> data) {
        for (auto item : data) {
            gistogram.addData(item);
        }
        return this;
    }

    GistogramScope* addDataItem(V item) {
        gistogram.addData(item);
        return this;
    }

    GistogramScope* parameter(K name, std::function<bool(V)> predicate) {
        Parameter<K, V> param;
        param.name = name;
        param.predicate = predicate;
        gistogram.addParameter(param);
        return this;
    }

    GistogramScope* enableStatistic(std::function<V(V, V)> statPredicate) {
        statistic = true;
        _statPredicate = statPredicate;
        return this;
    }

    Gistogram<K, V> buildGistogram() {
        gistogram.calculate(statistic, _statPredicate);
        return gistogram;
    }
};

template <class K, class V>
Gistogram<K, V> gistogram(std::function<void(GistogramScope<K, V> *s)> scopeParam) {
    auto *scope = new GistogramScope<K, V>();
    scopeParam(scope);
    auto g = scope->buildGistogram();
    return g;
}

#endif //LABA3_GISTOGRAMSCOPE_H
