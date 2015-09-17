// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <cassert>
#include <string>
using namespace boost::hana;
using namespace boost::hana::literals;


// sample(introspection-tomorrow)
struct Person {
  BOOST_HANA_DEFINE_STRUCT(Person,
    (std::string, name),
    (int, age)
  );
};

int main() {
  Person john{"John", 30};
  std::string name = at_key(john, "name"_s);
  int age = at_key(john, "age"_s);
}
// end-sample
