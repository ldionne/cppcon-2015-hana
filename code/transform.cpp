// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <sstream>
#include <tuple>
#include <utility>


// sample(transform)
template <typename ...T, typename F, std::size_t ...i>
auto transform_impl(std::tuple<T...> const& tuple, F const& f,
                    std::index_sequence<i...>)
{
  return std::make_tuple(f(std::get<i>(tuple))...);
}

template <typename ...T, typename F>
auto transform(std::tuple<T...> const& tuple, F const& f) {
  return transform_impl(tuple, f,
            std::make_index_sequence<sizeof...(T)>{});
}
// end-sample

int main() {
  std::tuple<int, char, float> ts{1, '2', 3.3f};
  auto us = transform(ts, [](auto x) {
    std::ostringstream ss;
    ss << x;
    return ss.str();
  });

  assert(us == std::make_tuple("1", "2", "3.3"));
}
