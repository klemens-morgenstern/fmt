//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_FORMAT_PARSE_CONTEXT_HPP
#define BOOST_FMT_FORMAT_PARSE_CONTEXT_HPP

#include <boost/core/detail/string_view.hpp>
#include <boost/core/span.hpp>
#include <boost/fmt/detail/errors.hpp>

namespace boost
{
namespace fmt
{

template<typename CharT>
struct basic_format_parse_context
{
  using char_type = CharT;
  using iterator       = typename core::basic_string_view<CharT>::const_iterator;
  using const_iterator = typename core::basic_string_view<CharT>::const_iterator;

  BOOST_CONSTEXPR const_iterator begin() const noexcept { return current_;}
  BOOST_CONSTEXPR const_iterator end()   const noexcept { return end_;}

  BOOST_CONSTEXPR void advance_to( const_iterator it )
  {
    BOOST_ASSERT(it <= end_);
    current_ = it;
  }
  BOOST_CONSTEXPR std::size_t next_arg_id()
  {
    const auto id = ++current_arg_;
    if (id >= number_of_args_)
      detail::next_arg_out_of_range();
    return id;
  }
  BOOST_CONSTEXPR void check_arg_id(std::size_t id)
  {
    if (id >= number_of_args_)
      detail::check_arg_id_index_failed();
  }
  BOOST_CONSTEXPR void check_arg_id(core::string_view name)
  {
    if (std::find(named_args_.begin(), named_args_.end(), name) == named_args_.end())
      detail::check_arg_id_index_failed();
  }

  BOOST_CONSTEXPR basic_format_parse_context(core::basic_string_view<CharT> format, std::size_t number_of_args)
                      : current_(format.begin()), end_(format.end()), number_of_args_(number_of_args) {}


  BOOST_CONSTEXPR basic_format_parse_context(core::basic_string_view<CharT> format,
                                             span<core::basic_string_view<CharT>> named_args)
      : current_(format.begin()), end_(format.end()), number_of_args_(0u), named_args_(named_args) {}
 private:
  const_iterator current_;
  const_iterator end_;
  std::size_t current_arg_{0u};
  std::size_t number_of_args_;
  span<core::string_view> named_args_;
  template<typename, typename ...>
  friend struct basic_format_string;
};

using  format_parse_context = basic_format_parse_context< char>;
using wformat_parse_context = basic_format_parse_context<wchar_t>;

#if defined (__cpp_char8_t)
using u8format_parse_context = basic_format_parse_context<char8_t>;
#endif

using u16format_parse_context = basic_format_parse_context<char16_t>;
using u32format_parse_context = basic_format_parse_context<char32_t>;

}
}

#endif //BOOST_FMT_FORMAT_PARSE_CONTEXT_HPP
