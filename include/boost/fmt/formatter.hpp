//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_FORMATTER_HPP
#define BOOST_FMT_FORMATTER_HPP

#include <boost/core/detail/string_view.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/type_traits/make_void.hpp>

#include <type_traits>

namespace boost {
namespace fmt {

template<typename Char, typename Iterator>
struct basic_format_context;

template<typename T, typename Char>
struct formatter;

template<typename T, typename Char = char, typename = void>
constexpr bool has_formatter_v = false;

template<typename T, typename Char>
constexpr bool has_formatter_v<T, Char,
          void_t<decltype(
            std::declval<const formatter<T, Char> &>().format(
                std::declval<const T &>(),
                std::declval<basic_format_context<Char*, Char>&>())
              )>> = true;


}
}

#endif //BOOST_FMT_FORMATTER_HPP
