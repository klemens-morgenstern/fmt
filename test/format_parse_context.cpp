//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/fmt/format_parse_context.hpp>
#include <boost/fmt/detail/delimiter.hpp>

#include <iostream>

#include "doctest.h"

using namespace boost;

constexpr int test()
{
  std::array<core::string_view, 3u> nms = {"foo", "bar" , "foobar"};
  span<core::string_view> na = nms;
  fmt::format_parse_context ctx{"{} foo {}", na};
  ctx.check_arg_id("foo");
  ctx.check_arg_id("bar");
  return 0u;
}


constexpr auto val = test();

TEST_CASE("find_replacement_start")
{
  constexpr core::string_view ts = "escape {{}} to {} ending";
  constexpr auto c = fmt::detail::find_replacement_start(ts);
  constexpr core::string_view pre = ts.substr(0, c);
  constexpr core::string_view post = ts.substr(c);
  fmt::detail::check_replacement_end(post);

  CHECK(pre  == "escape {{}} to {");
  CHECK(post == "} ending");

}


TEST_CASE("get_initial_replacement")
{
  constexpr core::string_view a1 = "} ending";
  constexpr core::string_view a2 = ":spec} ending";
  constexpr auto c1 = fmt::detail::get_initial_replacement_id(a1);
  CHECK(std::get<0>(c1) == 1u);
  CHECK(std::get<1>(c1) == std::numeric_limits<std::size_t>::max());

  constexpr auto c2 = fmt::detail::get_initial_replacement_id(a2);
  CHECK(std::get<0>(c2) == 1);
  CHECK(std::get<1>(c2) == std::numeric_limits<std::size_t>::max());


  constexpr core::string_view m1 = "12} ending";
  constexpr core::string_view m2 = "0:spec} ending";
  constexpr auto d1 = fmt::detail::get_initial_replacement_id(m1);
  CHECK(std::get<0>(d1) == 3);
  CHECK(std::get<1>(d1) == 12);

  constexpr auto d2 = fmt::detail::get_initial_replacement_id(m2);
  CHECK(std::get<0>(d2) == 2);
  CHECK(std::get<1>(d2) == 0);
}

