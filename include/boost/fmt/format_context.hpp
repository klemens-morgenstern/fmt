//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_FORMAT_CONTEXT_HPP
#define BOOST_FMT_FORMAT_CONTEXT_HPP

namespace boost
{
namespace fmt
{

template<typename Char, typename Iterator>
struct basic_format_context
{

};

template<typename Iterator> using  format_context = basic_format_context< char,   Iterator>;
template<typename Iterator> using wformat_context = basic_format_context<wchar_t, Iterator>;

#if defined (__cpp_char8_t)
template<typename Iterator> using u8format_context = basic_format_context<char8_t, Iterator>;
#endif

template<typename Iterator> using u16format_context = basic_format_context<char16_t, Iterator>;
template<typename Iterator> using u32format_context = basic_format_context<char32_t, Iterator>;



}
}

#endif //BOOST_FMT_FORMAT_CONTEXT_HPP
