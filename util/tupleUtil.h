#ifndef LABA1_TUPLEUTIL_H
#define LABA1_TUPLEUTIL_H

#include <iterator>

class util {
private:
    template<typename Tuple, typename F, std::size_t ...Indices>
    static void forEachImpl(Tuple &&tuple, F &&f, std::index_sequence<Indices...>) {
        using swallow = int[];
        (void) swallow{1,
                       (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
        };
    }

public:
    template<typename F, typename... Args>
    static void forEach(const std::tuple<Args...> &tuple, F &&f) {
        forEachImpl(tuple, std::forward<F>(f), std::index_sequence_for<Args...>{});
    }
};


#endif //LABA1_TUPLEUTIL_H
