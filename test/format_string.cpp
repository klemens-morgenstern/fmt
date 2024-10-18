//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/fmt/format_string.hpp>
#include <boost/fmt/ostream.hpp>

using namespace boost ;
constexpr fmt::format_string<std::string, double> fm{"Hello, {} {}!"};
constexpr fmt::format_string<std::string, int> f2{"{}, {}!"};
constexpr fmt::format_string<std::string, int> f3{"{0}, {1}!"};
constexpr fmt::format_string<std::string, int> f4{"{1}, {0} {0}!"};
