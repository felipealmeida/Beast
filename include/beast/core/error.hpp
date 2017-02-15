//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_ERROR_HPP
#define BEAST_ERROR_HPP

#ifndef BOOST_ASIO_USE_STD_SYSTEM_ERROR
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#else
#include <system_error>
#endif

namespace beast {

#ifndef BOOST_ASIO_USE_STD_SYSTEM_ERROR
#define BOOST_BEAST_SYSTEM_NAMESPACE boost::system::
#else 
#define BOOST_BEAST_SYSTEM_NAMESPACE std::
#endif
  
/// The type of error code used by the library
using error_code = BOOST_BEAST_SYSTEM_NAMESPACE error_code;

/// The type of system error thrown by the library
using system_error = BOOST_BEAST_SYSTEM_NAMESPACE system_error;

/// The type of error category used by the library
using error_category = BOOST_BEAST_SYSTEM_NAMESPACE error_category;

/// The type of error condition used by the library
using error_condition = BOOST_BEAST_SYSTEM_NAMESPACE error_condition;

/// The set of constants used for cross-platform error codes
#if GENERATING_DOCS
enum errc{};
#elif !defined(BOOST_ASIO_USE_STD_SYSTEM_ERROR)
namespace errc = boost::system::errc;
#else
using errc = std::errc;
#endif
} // beast

#endif
