// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/integral_constant.hpp>
#include <boost/hana/tuple.hpp>

#include <type_traits>


// sample(type_unification-type)
template <typename T>
class type { /* nothing */ };

type<int> t{};
// end-sample

// sample(type_unification-metafunction)
template <typename T>
constexpr type<T*> add_pointer(type<T> const&)
{ return {}; }

template <typename T>
constexpr std::false_type is_pointer(type<T> const&)
{ return {}; }

template <typename T>
constexpr std::true_type is_pointer(type<T*> const&)
{ return {}; }
// end-sample

namespace usage {
// sample(type_unification-usage)
type<int> t{};
auto p = add_pointer(t);
static_assert(is_pointer(p), "");
// end-sample
}

namespace sugar {
// sample(type_unification-sugar)
template <typename T>
constexpr type<T> type_c{};

auto t = type_c<int>;
auto p = add_pointer(t);
static_assert(is_pointer(p), "");
// end-sample
}

namespace citizen {
using namespace boost::hana;
using namespace boost::hana::literals;

// sample(type_unification-first_class)
auto xs = make_tuple(type_c<int>, type_c<char>, type_c<void>);
auto c = xs[1_c];

// sugar:
auto ys = tuple_t<int, char, void>;
// end-sample
}

int main() { }
