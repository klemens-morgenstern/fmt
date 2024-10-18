//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_FORMAT_STRING_HPP
#define BOOST_FMT_FORMAT_STRING_HPP

#include <boost/core/detail/string_view.hpp>
#include <boost/fmt/formatter.hpp>
#include <boost/fmt/detail/delimiter.hpp>
#include <boost/fmt/format_parse_context.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/tuple.hpp>
#include <array>
#include <tuple>
#include "boost/fmt/detail/errors.hpp"

namespace boost
{
namespace fmt
{

template<typename CharT, typename ...Args>
struct basic_format_string
{
  consteval basic_format_string(core::basic_string_view<CharT> format) : format_(format)
  {
    std::fill(formatter_usage_.begin(), formatter_usage_.end(), std::numeric_limits<std::size_t>::max());
    parse_();
  }
  constexpr core::basic_string_view<CharT> get() const noexcept {return format_;}

 private:

  constexpr void parse_()
  {
    constexpr auto npos = core::basic_string_view<CharT>::npos;
    auto pos = detail::find_replacement_start(format_);
    segments_[segment_idx_++] = format_.substr(0u, pos - 1u);

    auto rest = format_.substr(pos);
    if (is_manual_ = detail::is_manual(rest))
    {
      while (pos != npos)
      {
        if (pos == npos)
          detail::too_many_args_supplied();
        if (!detail::is_manual(rest))
          detail::cannot_mix_manual_and_automatic();

        auto [n, id] = detail::get_manual_replacement_id(rest);
        rest.remove_prefix(n);
        if (id >= sizeof...(Args))
          detail::too_few_arguments();
        mp11::mp_with_index<sizeof...(Args)>(
            id,
            [&](auto I)
            {
              using formatter_t = std::tuple_element_t<I, std::tuple<formatter<Args, CharT>...>>;
              formatter_t & formatter = std::get<I>(formatters_);
              basic_format_parse_context<CharT> ctx{rest, sizeof...(Args)};
              auto itr = formatter.parse(ctx);
              ctx.advance_to(itr);
              if (formatter_usage_[id] != std::numeric_limits<std::size_t>::max()) // reset
                formatter = formatter_t();
              formatter_usage_[id] = segment_idx_;

              rest = core::basic_string_view<char>{itr, rest.end()};
              rest.remove_prefix(detail::check_replacement_end(rest));
              pos = detail::find_replacement_start(rest);
              if (pos == rest.size())
              {
                if (BOOST_LIKELY(segment_idx_ < segments_.size()))
                  segments_[segment_idx_++] = rest;
                else
                  segment_idx_++;;

                pos = npos;
                return ;
              }
              else
              {
                segments_[segment_idx_++] = rest.substr(0u, pos - 1u);
                rest.remove_prefix(pos);
              }
            });
      }
    }
    else
      boost::mp11::tuple_for_each(
          formatters_,
          [&](auto & formatter) constexpr
          {
            if (pos == npos)
              detail::too_many_args_supplied();
            if (detail::is_manual(rest))
              detail::cannot_mix_manual_and_automatic();

            basic_format_parse_context<CharT> ctx{rest, sizeof...(Args)};
            auto itr = formatter.parse(ctx);
            ctx.advance_to(itr);
            rest = core::basic_string_view<char>{itr, rest.end()};
            rest.remove_prefix(detail::check_replacement_end(rest));
            pos = detail::find_replacement_start(rest);

            if (pos == rest.size())
            {
              segments_[segment_idx_++] = rest;
              return ;
            }
            segments_[segment_idx_++] = rest.substr(0u, pos - 1u);
            rest.remove_prefix(pos);
          });

    auto pp = detail::find_replacement_start(rest);
    if (pp != rest.size())
      detail::too_few_arguments();
  }

  core::basic_string_view<CharT> format_ = {};
  std::array<core::basic_string_view<CharT>, sizeof...(Args) + 1u> segments_;
  std::size_t segment_idx_ = 0u;
  bool is_manual_ = false;
  std::tuple<formatter<Args, CharT>...> formatters_ = {};
  std::array<std::size_t, sizeof...(Args)> formatter_usage_ = {};
};


template<typename ...Args> using  format_string = basic_format_string< char,   Args...>;
template<typename ...Args> using wformat_string = basic_format_string<wchar_t, Args...>;

#if defined (__cpp_char8_t)
template<typename ...Args> using u8format_string = basic_format_string<char8_t, Args...>;
#endif

template<typename ...Args> using u16format_string = basic_format_string<char16_t, Args...>;
template<typename ...Args> using u32format_string = basic_format_string<char32_t, Args...>;

}
}


#endif //BOOST_FMT_FORMAT_STRING_HPP
