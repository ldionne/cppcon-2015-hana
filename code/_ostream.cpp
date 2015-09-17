// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>

#include <iostream>
#include <string>
using namespace boost::hana;


struct concat_strings {
  template <char ...s1, char ...s2>
  constexpr auto operator()(string<s1...>, string<s2...>) const
  { return string_c<s1..., s2...>; }
};

template <typename S>
constexpr auto concat_all(S s) {
  return fold_left(s, string_c<>, concat_strings{});
}



constexpr auto formats = make_map(
  make_pair(type_c<int>, string_c<'%', 'd'>),
  make_pair(type_c<double>, string_c<'%', 'f'>),
  make_pair(type_c<char const*>, string_c<'%', 's'>)
);

constexpr struct done_t { } done{};

template <typename F, typename ...Tokens>
struct unstream_t {
  F f;
  tuple<Tokens...> tokens;

  template <typename Token>
  friend constexpr
  unstream_t<F, Tokens..., std::decay_t<Token>>
  operator<<(unstream_t&& self, Token&& token) {
    return {
      std::move(self.f),
      append(std::move(self.tokens), std::forward<Token>(token))
    };
  }

  friend auto operator<<(unstream_t&& self, done_t) {
    auto fmt = concat_all(
      adjust_if(self.tokens,
        compose(not_, is_a<string_tag>),
        [](auto&& token) {
          return formats[decltype_(token)];
        }
      )
    );

    auto args = remove_if(std::move(self.tokens), is_a<string_tag>);

    return unpack(std::move(args), [&](auto&& ...args) {
      return std::move(self.f)(
        to<char const*>(fmt),
        std::forward<decltype(args)&&>(args)...
      );
    });
  }
};

template <typename F>
constexpr unstream_t<std::decay_t<F>> unstream(F&& f) {
    return {std::forward<F>(f), {}};
}

int main() {
  unstream(std::printf)
    << BOOST_HANA_STRING("C++Now ")
    << 2015
    << " is"
    << BOOST_HANA_STRING(" awesome!")
    << done;

  // equivalent to

  std::printf("C++Now %i%s awesome!", 2015, " is");
}
