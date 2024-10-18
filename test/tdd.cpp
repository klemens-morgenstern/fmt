//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/fmt.hpp>

using namespace boost;

consteval bool verify(core::string_view sv)
{
  return sv.find('\n') == sv.npos;
}

auto x = verify("foobar");

template<typename Char, typename Arg>
struct arg
{
  template<typename Arg_>
  constexpr arg(core::basic_string_view<Char> key, Arg_ && value)
        : key(key), value(std::forward<Arg_>(value)) {}

  core::basic_string_view<Char> key;
  Arg value;
};


template<typename Char, typename Arg>
arg(core::basic_string_view<Char> key, Arg && value) -> arg<Char, std::decay_t<Arg>>;

template<typename Arg>
arg(core::string_view key, Arg && value) -> arg<char, std::decay_t<Arg>>;

template<typename Arg>
arg(core::wstring_view key, Arg && value) -> arg<wchar_t, std::decay_t<Arg>>;

template<typename Arg>
arg(core::u8string_view key, Arg && value) -> arg<char8_t, std::decay_t<Arg>>;

template<typename Arg>
arg(core::u16string_view key, Arg && value) -> arg<char16_t, std::decay_t<Arg>>;

template<typename Arg>
arg(core::u32string_view key, Arg && value) -> arg<char32_t, std::decay_t<Arg>>;


template<typename ... Args>
void foo(Args && ... args);

template<typename ... Args>
void foo(arg<char, Args> && ... args);


void test(core::string_view sv)
{
/*  verify("foobaria");
  foo(1, 2, 3);
  foo(arg("a", sv), arg("b", 2), arg("c", 3));*/
}