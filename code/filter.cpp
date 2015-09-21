// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>


template <typename InputIterator, typename T>
constexpr std::size_t
count(InputIterator first, InputIterator last, T const& value) {
  std::size_t n = 0;
  for (; first != last; ++first)
    if (*first == value)
      ++n;
  return n;
}

template <typename T, std::size_t N>
struct array {
  T storage_[N];

  constexpr T& operator[](std::size_t i)
  { return storage_[i]; }

  constexpr T const& operator[](std::size_t i) const
  { return storage_[i]; }
};

// sample(filter-slice)
template <typename Tuple, std::size_t ...i>
auto slice(Tuple const& tuple, std::index_sequence<i...>) {
  return std::make_tuple(std::get<i>(tuple)...);
}
// end-sample

#if 0
// sample(filter-indices-pre)
template <bool ...results>
struct filter_indices_helper {
  // ...
};

template <bool ...results>
using filter_indices = typename filter_indices_helper<results...>::
                       template as_index_sequence<>;
// end-sample
#endif

template <bool ...results>
struct filter_indices_helper {
// sample(filter-computed_indices)
static constexpr bool results_array[sizeof...(results)] = {results...};
static constexpr std::size_t N =
  count(results_array, results_array + sizeof...(results), true);

static constexpr array<std::size_t, N> compute_indices() {
  array<std::size_t, N> indices{};
  std::size_t current_index = 0;
  for (std::size_t i = 0; i < N; ++i)
    if (results_array[i])
      indices[i] = current_index++;
  return indices;
}

static constexpr auto computed_indices = compute_indices();
// end-sample

// sample(filter-as_index_sequence)
template <typename Indices = std::make_index_sequence<N>>
struct as_index_sequence;

template <std::size_t ...i>
struct as_index_sequence<std::index_sequence<i...>>
  : std::index_sequence<computed_indices[i]...>
{ };
// end-sample
};

template <bool ...results>
using filter_indices = typename filter_indices_helper<results...>::
                       template as_index_sequence<>;

// sample(filter)
template <typename Tuple, typename Predicate, std::size_t ...i>
auto filter_impl(Tuple const& tuple, Predicate predicate,
                 std::index_sequence<i...>)
{
  using Indices = filter_indices<
    decltype(predicate(std::get<i>(tuple)))::value...
  >;
  return slice(tuple, Indices{});
}

template <typename ...T, typename Predicate>
auto filter(std::tuple<T...> const& tuple, Predicate predicate) {
  return filter_impl(tuple, predicate,
                     std::make_index_sequence<sizeof...(T)>{});
}
// end-sample

int main() {
  std::tuple<int, char, float, double> ts{1, '2', 3.3f, 4.4};
  auto us = filter(ts, [](auto x) {
    return std::is_integral<decltype(x)>{};
  });

  assert(us == std::make_tuple(1, '2'));
}
