// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>

#include <cassert>
#include <string>
using namespace boost::hana;


// sample(introspection-now)
struct Person {
  BOOST_HANA_DEFINE_STRUCT(Person,
    (std::string, name),
    (int, age)
  );
};

int main() {
  Person john{"John", 30};
  std::string name = at_key(john, BOOST_HANA_STRING("name"));
  int age = at_key(john, BOOST_HANA_STRING("age"));
}
// end-sample
