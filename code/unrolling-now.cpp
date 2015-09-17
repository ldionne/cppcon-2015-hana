// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/integral_constant.hpp>
using namespace boost::hana;

// To generate, first do not define f(), i.e. remove the trailing `{ }`.
// Otherwise, the compiler optimizes everything away. Then,
// clang++-3.6 -S -O3 -c code/unrolling-now.cpp -I path/to/hana/include -std=c++14 -o unrolling-now.s

// sample(unrolling-now)
__attribute__((noinline)) void f() { }

int main() {
    int_c<5>.times(f);
}
// end-sample
