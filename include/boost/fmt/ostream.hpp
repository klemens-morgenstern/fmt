//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_OSTREAM_HPP
#define BOOST_FMT_OSTREAM_HPP

#include <boost/fmt/format_parse_context.hpp>
#include <boost/fmt/format_context.hpp>
#include <ostream>
#include <streambuf>

namespace boost
{
namespace fmt
{

namespace detail
{

template<typename OutputIt, typename Char>
struct format_streambuf final : std::basic_streambuf<Char>
{
  format_streambuf(basic_format_context<OutputIt, Char> & ctx) : ctx(ctx) {}

  basic_format_context<OutputIt, Char> & ctx;
};

}

template<typename T, typename Char>
  requires requires (std::basic_ostream<Char> & os, const T & value) {{os << value};}
struct formatter<T, Char>
{
  BOOST_CONSTEXPR auto parse(basic_format_parse_context<Char>& ctx)
  {
    return ctx.begin();
  }

  template <typename OutputIt>
  auto format(const T & t, basic_format_context<OutputIt, Char>& ctx) const -> OutputIt
  {
    detail::format_streambuf<OutputIt, Char> buf{ctx};
    std::ostream ostr{&buf};
    ostr << t;
    return buf.result();
  }
};


}
}

#endif //BOOST_FMT_OSTREAM_HPP
