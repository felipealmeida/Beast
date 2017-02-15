//
// Copyright (c) 2013-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_DETAIL_STREAM_CONCEPTS_HPP
#define BEAST_DETAIL_STREAM_CONCEPTS_HPP

#include <beast/core/buffer_concepts.hpp>
#include <beast/core/error.hpp>
#include <type_traits>
#include <utility>

namespace beast {
namespace detail {

// Types that meet the requirements,
// for use with std::declval only.
struct StreamHandler
{
    StreamHandler(StreamHandler const&) = default;
    void operator()(error_code ec, std::size_t);
};
  
template<class T>
class is_SyncReadStream
{
    template<class U, class R = std::is_same<decltype(
        std::declval<U>().read_some(
            std::declval<MutableBufferSequence>())),
                std::size_t>>
    static R check1(int);
    template<class>
    static std::false_type check1(...);
    using type1 = decltype(check1<T>(0));

    template<class U, class R = std::is_same<decltype(
        std::declval<U>().read_some(
            std::declval<MutableBufferSequence>(),
                std::declval<error_code&>())), std::size_t>>
    static R check2(int);
    template<class>
    static std::false_type check2(...);
    using type2 = decltype(check2<T>(0));

public:
    using type = std::integral_constant<bool,
        type1::value && type2::value>;
};

template<class T>
class is_SyncWriteStream
{
    template<class U, class R = std::is_same<decltype(
        std::declval<U>().write_some(
            std::declval<ConstBufferSequence>())),
                std::size_t>>
    static R check1(int);
    template<class>
    static std::false_type check1(...);
    using type1 = decltype(check1<T>(0));

    template<class U, class R = std::is_same<decltype(
        std::declval<U>().write_some(
            std::declval<ConstBufferSequence>(),
                std::declval<error_code&>())), std::size_t>>
    static R check2(int);
    template<class>
    static std::false_type check2(...);
    using type2 = decltype(check2<T>(0));

public:
    using type = std::integral_constant<bool,
        type1::value && type2::value>;
};

} // detail
} // beast

#endif
