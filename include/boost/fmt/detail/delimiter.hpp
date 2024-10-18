//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_DETAIL_FMT_DELIMITER_HPP
#define BOOST_DETAIL_FMT_DELIMITER_HPP

#include <iterator>
#include <numeric>
#include <tuple>
#include <boost/fmt/detail/errors.hpp>

namespace boost
{
namespace fmt
{
namespace detail
{

template<typename Char>
BOOST_CONSTEXPR std::size_t find_replacement_start(core::basic_string_view<Char> input)
{
  constexpr auto open  = static_cast<Char>('{');
  constexpr auto close = static_cast<Char>('}');

        auto it  = input.begin();
  const auto end = input.end();

  struct cmp_
  {
    constexpr bool operator()(Char c) const {return c == open || c == close;}
  };

  constexpr cmp_ cmp;

  while (it != end)
  {
    it = std::find_if(it, end, cmp);
    if (it == end)
      return std::distance(input.begin(), it);

    const auto nx = std::next(it);
    if (nx == end)
      detail::incomplete_replacement();

    if (*it == close)
    {
      if (*nx != close)
        detail::stray_unescaped();
    }
    else if (*nx != open)
      return std::distance(input.begin(), nx);
    it = std::next(nx);
  }

  return std::distance(input.begin(), it);
}

template<typename Char>
BOOST_CONSTEXPR std::size_t check_replacement_end(core::basic_string_view<Char> input)
{
  constexpr auto open  = static_cast<Char>('{');
  constexpr auto close = static_cast<Char>('}');

  if (input.empty() || input.front() != close)
    detail::incomplete_replacement();

  return 1u;
}


template<typename Char>
BOOST_CONSTEXPR auto get_initial_replacement_id(core::basic_string_view<Char> input)
  -> std::pair<std::size_t, std::size_t>
{
        auto it = input.begin();
  const auto end = input.end();
  if (it == end)
    detail::invalid_replacement_id();

  constexpr auto sep = static_cast<Char>(':');
  constexpr auto en_ = static_cast<Char>('}');

  if (*it == sep || *it == en_)
    return std::make_pair(std::distance(input.begin(), it) + 1u, std::numeric_limits<std::size_t>::max());

  struct cmp_
  {
    constexpr bool operator()(Char c) const {return c == sep || c == en_;}
  };
  constexpr cmp_ cmp;

  auto it_ = std::find_if(it, end, cmp);

  if (it_ == end)
      detail::invalid_replacement_id();

  auto f = *it;
  if (f == static_cast<Char>('0') && std::next(it) == it_)
      return std::make_pair(2u, 0u);


  if (f >= static_cast<Char>('0') &&
      f <= static_cast<Char>('9'))
  {
      struct acc_
      {
        constexpr std::size_t operator()(std::size_t n, Char c) const
        {
          if (c < static_cast<Char>('0') ||
              c > static_cast<Char>('9'))
            detail::invalid_replacement_id();

          return (n * 10) + (c - static_cast<Char>('0'));
        }
      };
      constexpr acc_ acc;

      return std::make_pair(std::distance(input.begin(), it_) + 1u,
                            std::accumulate(
                                 it, it_, std::size_t(0u), acc)
                             );
  }

  detail::invalid_replacement_id();
  return {core::basic_string_view<Char>::npos, std::numeric_limits<std::size_t>::max()};
}

template<typename Char>
BOOST_CONSTEXPR auto get_manual_replacement_id(core::basic_string_view<Char> input)
  -> std::pair<std::size_t, std::size_t>
{
        auto it = input.begin();
  const auto end = input.end();
  if (it == end)
    detail::invalid_replacement_id();

  constexpr auto sep = static_cast<Char>(':');
  constexpr auto en_ = static_cast<Char>('}');

  auto f = *it;

  struct cmp_
  {
    constexpr bool operator()(Char c) const {return c == sep || c == en_;}
  };
  constexpr cmp_ cmp;

  auto it_ = std::find_if(it, end, cmp);

  struct acc_
  {
    constexpr std::size_t operator()(std::size_t n, Char c) const
    {
      if (c < static_cast<Char>('0') ||
          c > static_cast<Char>('9'))
        detail::invalid_replacement_id();

      return (n * 10) + (c - static_cast<Char>('0'));
    }
  };
  constexpr acc_ acc;

  return std::make_pair(std::distance(it, it_),
                       std::accumulate(it, it_, std::size_t(0u), acc));
}

template<typename Char>
BOOST_CONSTEXPR bool is_manual(core::basic_string_view<Char> input)
{

  constexpr auto sep = static_cast<Char>(':');
  constexpr auto end = static_cast<Char>('}');
  const auto idx = (std::min)(input.find(sep), input.find(end));
  if (idx == core::basic_string_view<Char>::npos)
    detail::unterminated_replacement();

  return idx != 0u;

}

template<typename Char>
BOOST_CONSTEXPR auto get_named_replacement_id(core::basic_string_view<Char> input)
    -> std::pair<std::size_t, core::basic_string_view<Char>>
{
        auto it = input.begin();
  const auto end = input.end();
  if (it == end)
    detail::invalid_replacement_id();

  constexpr auto sep = static_cast<Char>(':');
  constexpr auto en_ = static_cast<Char>('}');

  auto f = *it;

  struct cmp_
  {
    constexpr bool operator()(Char c) const {return c == sep || c == en_;}
  };
  constexpr cmp_ cmp;

  auto it_ = std::find_if(it, end, cmp);

  struct check_
  {
    constexpr bool operator()(Char c) const
    {
      return (c >= static_cast<Char>('A') &&
              c <= static_cast<Char>('Z'))
             || (c >= static_cast<Char>('a') &&
                 c <= static_cast<Char>('z'))
             || (c >= static_cast<Char>('0') &&
                 c <= static_cast<Char>('9'));
    }
  };
  constexpr check_ check;
  if (!std::all_of(it, it_, check))
    detail::invalid_replacement_id();

  return std::make_pair(std::distance(input.begin(), it_) + 1u, core::string_view(it, it_));

}


}
}
}

#endif //BOOST_DETAIL_FMT_DELIMITER_HPP
