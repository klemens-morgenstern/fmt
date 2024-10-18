//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/fmt/arg.hpp>

#include "doctest.h"

#include <iostream>

#if defined(BOOST_FMT_HAS_NTTP_STRING)

using namespace boost;

TEST_CASE("arg-20")
{
  CHECK(fmt::arg<"foo">(42).value == 42);
  CHECK(fmt::arg<"foo">(42).key == "foo");
}

#endif

TEST_CASE("arg-")
{
  CHECK(fmt::arg<"foo">(42).value == 42);
  CHECK(fmt::arg<"foo">(42).key == "foo");
}
