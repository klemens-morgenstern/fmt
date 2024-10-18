//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>
#include <boost/fmt/formatter.hpp>
#include <boost/fmt/named_arg.hpp>
//#include <boost/fmt/ostream.hpp>
#include "doctest.h"
#include <iostream>

using namespace boost;

struct test
{
  int bar;
  std::string foo;
};

BOOST_DESCRIBE_STRUCT(test, (), (bar, foo));

TEST_CASE("described")
{
  constexpr auto x = tag_invoke(fmt::get_arg_names_tag<test>{});
  constexpr auto idx = std::find(x.begin(), x.end(), x[0]) - x.end();
  static_assert(!fmt::has_formatter_v<int>);
  static_assert(
      mp11::mp_valid<
        std::is_default_constructible,
        fmt::formatter<int, char>>::value);

  test t { 42, "deus vult"};

  CHECK(tag_invoke(fmt::get_arg<0u>{}, t) == 42);
  CHECK(tag_invoke(fmt::get_arg<1u>{}, t) == "deus vult");

  static_assert(!fmt::has_named_args_v<int>);
  static_assert(fmt::has_named_args_v<test>);
}