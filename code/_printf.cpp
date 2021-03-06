// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>

#include <type_traits>
using namespace boost::hana;
using namespace boost::hana::literals;


// sample(printf-formats)
auto formats = make_map(
  make_pair(char_c<'i'>, type_c<int>),
  make_pair(char_c<'f'>, type_c<double>),
  make_pair(char_c<'s'>, type_c<char*>)

  // ...
);
// end-sample

// sample(printf-core)
template <typename Fmt, typename ...Args>
int type_safe_printf(Fmt fmt, Args const& ...args) {
  static_assert(is_a<string_tag>(fmt),
  "the format string must be a compile-time hana::String");

  auto format_chars = filter(to<tuple_tag>(fmt), [](auto c) {
    return contains(formats, c);
  });

  static_assert(length(format_chars) == sizeof...(args),
  "number of arguments not matching the number of format characters");

  auto conversions = zip(tuple_t<std::decay_t<Args>...>, format_chars);
  for_each(conversions, fuse([](auto arg_type, auto format_char) {
    static_assert(decltype(formats[format_char] == arg_type){},
    "the type of the argument does not match the format character");
  }));

  return std::printf(to<char const*>(fmt), args...);
};
// end-sample

int main() {

#if 1
// sample(printf-usage)
type_safe_printf(BOOST_HANA_STRING("%i, %f, %s"), 2, 3.4, "abcd");
// end-sample
#elif 0
// sample(printf-wrong_type)
type_safe_printf(BOOST_HANA_STRING("%i, %f, %s"), 2, 2, "abcd");
// end-sample
#elif 0
// sample(printf-wrong_narg)
type_safe_printf(BOOST_HANA_STRING("%i, %f, %s"), 2, 3.4);
// end-sample
#endif

}
