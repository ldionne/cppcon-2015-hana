// Copyright Louis Dionne 2015
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>
using namespace boost::hana;


namespace disambiguate {
// sample(sorting-now)
template <typename Xs, typename Pred>
auto sort(Xs xs, Pred pred) {
  return eval_if(length(xs) < size_c<2>,
    make_lazy(xs),
    make_lazy([=](auto xs) {
      auto pivot = front(xs);
      auto parts = partition(tail(xs), partial(pred, pivot));
      return concat(
        append(sort(second(parts), pred), pivot),
        sort(first(parts), pivot)
      );
    })(xs)
  );
}
// end-sample
}

int main() {
  using disambiguate::sort;
  BOOST_HANA_CONSTANT_CHECK(
    sort(make_tuple(), less) == make_tuple()
  );

  BOOST_HANA_CONSTANT_CHECK(
    sort(make_tuple(int_c<1>), less) == make_tuple(int_c<1>)
  );

  BOOST_HANA_CONSTANT_CHECK(
    sort(make_tuple(int_c<2>, int_c<1>), less) == make_tuple(int_c<1>, int_c<2>)
  );

  BOOST_HANA_CONSTANT_CHECK(
    sort(make_tuple(int_c<3>, int_c<2>, int_c<1>), less) ==
      make_tuple(int_c<1>, int_c<2>, int_c<3>)
  );

  BOOST_HANA_CONSTANT_CHECK(
    sort(make_tuple(int_c<4>, int_c<3>, int_c<2>, int_c<1>), less) ==
      make_tuple(int_c<1>, int_c<2>, int_c<3>, int_c<4>)
  );
}
