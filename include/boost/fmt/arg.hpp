//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_ARG_HPP
#define BOOST_FMT_ARG_HPP

#include <boost/fmt/ct/string.hpp>

namespace boost
{
namespace fmt
{

#if defined(BOOST_FMT_HAS_NTTP_STRING)

namespace detail
{

template<ct::string Name, typename T>
struct ct_arg
{

  constexpr static core::basic_string_view<typename decltype(Name)::char_type> key{Name};

  T value;

  template<typename U>
  ct_arg(U && u) :  value(std::forward<U>(u)) {}
};

}

template<ct::string Name, typename T>
constexpr auto arg(T && arg) -> detail::ct_arg<Name, std::decay_t<T>>
{
  return {std::forward<T>(arg)};
}

#endif

}
}


#endif //BOOST_FMT_ARG_HPP
