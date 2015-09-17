// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/at_key.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/type.hpp>

#include <string>
#include <cassert>
using namespace boost::hana;


int main() {
// sample(map-now)
auto map = make_map(
  make_pair(type_c<char>,   "char"),
  make_pair(type_c<int>,    "int"),
  make_pair(type_c<long>,   "long"),
  make_pair(type_c<float>,  "float"),
  make_pair(type_c<double>, "double")
);

std::string i = map[type_c<int>];
assert(i == "int");
// end-sample
}
