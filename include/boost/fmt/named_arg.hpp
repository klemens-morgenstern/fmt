//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_NAMED_ARG_HPP
#define BOOST_FMT_NAMED_ARG_HPP

#include <boost/core/detail/string_view.hpp>
#include <boost/describe/class.hpp>
#include <boost/describe/members.hpp>
#include <array>
#include <boost/mp11/algorithm.hpp>

namespace boost
{
namespace fmt
{

template<typename >
struct get_arg_names_tag {};

template<typename T>
  requires describe::has_describe_members<T>::value
constexpr auto tag_invoke(get_arg_names_tag<T>)
{
  using tp = describe::describe_members<T, describe::mod_public>;
  std::array<core::string_view, mp11::mp_size<tp>::value> res = { };

  std::size_t idx= 0u;
  boost::mp11::mp_for_each<tp>([&](auto tp){res[idx++] = tp.name;});

  return res;
}

template<std::size_t Idx>
struct get_arg {};

template<std::size_t Idx, typename T>
  requires describe::has_describe_members<T>::value
constexpr const auto & tag_invoke(get_arg<Idx> arg, const T & value)
{
  using tp = describe::describe_members<T, describe::mod_public>;
  using et = mp11::mp_at_c<tp, Idx>;
  return value.*et::pointer;
}

template<typename T, typename = void>
constexpr bool has_named_args_v = false;

template<typename T>
constexpr bool has_named_args_v<T, void_t<decltype(tag_invoke(get_arg_names_tag<T>{}))>> = true;


}
}
#endif //BOOST_FMT_NAMED_ARG_HPP
