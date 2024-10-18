//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_DETAIL_ID_HPP
#define BOOST_FMT_DETAIL_ID_HPP

#include <boost/core/detail/string_view.hpp>

namespace boost
{
namespace fmt
{
namespace detail
{

template<typename C1>
struct eq_t
{
  core::basic_string_view<C1> l;

  constexpr eq_t(core::basic_string_view<C1> l) : l(l) {}

  constexpr bool operator()(core::string_view r) const { return operator()<char>(r);}
  constexpr bool operator()(core::wstring_view r) const { return operator()<wchar_t>(r);}
#if defined (__cpp_char8_t)
  constexpr bool operator()(core::u8string_view r) const { return operator()<char8_t>(r);}
#endif
  constexpr bool operator()(core::u16string_view r) const { return operator()<char16_t>(r);}
  constexpr bool operator()(core::u32string_view r) const { return operator()<char32_t>(r);}


  template<typename C2>
  constexpr bool operator()(core::basic_string_view<C2> r) const
  {
    return std::equal(
        l.begin(), l.end(), r.begin(), r.end(),
        [](C1 l, C2 r)
        {
          if ((l > static_cast<C1>(127))
              || (r > static_cast<C2>(127)))
            return false;
          return static_cast<char>(l) == static_cast<char>(r);
        });
  }
};


template<typename C1>
constexpr eq_t<C1> eq(core::basic_string_view<C1> l)
{
  return eq_t<C1>(l);
}



}
}
}

#endif //BOOST_FMT_DETAIL_ID_HPP
