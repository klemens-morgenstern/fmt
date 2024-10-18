//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_ERRORS_HPP
#define BOOST_FMT_ERRORS_HPP

#include <boost/throw_exception.hpp>
#include <boost/fmt/format_error.hpp>

namespace boost
{
namespace fmt
{
namespace detail
{

BOOST_NORETURN inline void too_few_arguments(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(format_error("too-few-arguments"), loc);
}


BOOST_NORETURN inline void too_many_args_supplied(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(format_error("too-many-args-supplied"), loc);
}

BOOST_NORETURN inline void cannot_mix_manual_and_automatic(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(format_error("cannot-mix-manual-and-automatic"), loc);
}

BOOST_NORETURN inline void invalid_replacement_id(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::invalid_argument("invalid-replacement-id"));
}

BOOST_NORETURN inline void incomplete_replacement(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::invalid_argument("incomplete-replacement"));
}

BOOST_NORETURN inline void unterminated_replacement(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::invalid_argument("unterminated-replacement"));
}

BOOST_NORETURN inline void stray_unescaped(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::invalid_argument("stray-unescaped-}"));
}

BOOST_NORETURN inline void next_arg_out_of_range(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::out_of_range("next-arg-out-of-range-}"));
}

BOOST_NORETURN inline void check_arg_id_index_failed(const boost::source_location &loc = BOOST_CURRENT_LOCATION)
{
  boost::throw_exception(std::out_of_range("check-arg-id-index-failed"));
}

}
}
}

#endif //BOOST_FMT_ERRORS_HPP
