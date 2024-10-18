//
// Copyright (c) 2022 Klemens Morgenstern (klemens.morgenstern@gmx.net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FMT_FORMAT_ERROR_HPP
#define BOOST_FMT_FORMAT_ERROR_HPP

#include <stdexcept>

namespace boost
{
namespace fmt
{
struct format_error : std::runtime_error {using std::runtime_error::runtime_error;   };

}
}

#endif //BOOST_FMT_FORMAT_ERROR_HPP
