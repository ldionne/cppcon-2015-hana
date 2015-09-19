// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/mpl/less.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/hana.hpp>

#include <type_traits>


namespace then {
using namespace boost::mpl;

// sample(smallest_type-then)
template <typename ...T>
struct smallest
  : deref<
    typename min_element<
      vector<T...>, less<sizeof_<_1>, sizeof_<_2>>
    >::type
  >
{ };

static_assert(std::is_same<
  smallest<char, long, long double>::type, char
>{}, "");
// end-sample
}


namespace now {
using namespace boost::hana;

// sample(smallest_type-now)
template <typename ...T>
auto smallest = minimum(make_tuple(type_c<T>...), [](auto t, auto u) {
  return sizeof_(t) < sizeof_(u);
});

static_assert(smallest<char, long, long double> == type_c<char>, "");
// end-sample
}

int main() { }
