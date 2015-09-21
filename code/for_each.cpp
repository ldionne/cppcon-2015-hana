// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <sstream>
#include <tuple>
#include <utility>


// sample(for_each)
template <typename Tuple, typename F, std::size_t ...i>
void for_each_impl(Tuple const& tuple, F const& f,
                   std::index_sequence<i...>)
{
  using Expand = int[];
  (void)Expand{0, (f(std::get<i>(tuple)), 0)...};
}

template <typename ...T, typename F>
void for_each(std::tuple<T...> const& tuple, F const& f) {
  for_each_impl(tuple, f, std::make_index_sequence<sizeof...(T)>{});
}
// end-sample

int main() {
  std::tuple<int, char, float> ts{1, '2', 3.3f};
  std::ostringstream ss;
  for_each(ts, [&](auto x) {
    ss << x << std::endl;
  });

  assert(ss.str() == "1\n2\n3.3\n");
}
