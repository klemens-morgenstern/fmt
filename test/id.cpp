//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/fmt/detail/id.hpp>

using namespace boost;

static_assert(fmt::detail::eq<char>   ( "foo")( "foo"));
static_assert(fmt::detail::eq<char>   ( "foo")(L"foo"));
static_assert(fmt::detail::eq<wchar_t>(L"foo")( "foo"));
static_assert(fmt::detail::eq<wchar_t>(L"foo")(L"foo"));

