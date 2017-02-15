//
// Copyright (c) 2013-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_DETAIL_ASYNC_STREAM_CONCEPTS_HPP
#define BEAST_DETAIL_ASYNC_STREAM_CONCEPTS_HPP

namespace beast {
namespace detail {

using ReadHandler = StreamHandler;
using WriteHandler = StreamHandler;

template<class T>
class has_get_io_service
{
    template<class U, class R = typename std::is_same<
        decltype(std::declval<U>().get_io_service()),
            boost::asio::io_service&>>
    static R check(int);
    template<class>
    static std::false_type check(...);
public:
    using type = decltype(check<T>(0));
};

template<class T>
class is_AsyncReadStream
{
    template<class U, class R = decltype(
        std::declval<U>().async_read_some(
            std::declval<MutableBufferSequence>(),
                std::declval<ReadHandler>()),
                    std::true_type{})>
    static R check(int);
    template<class>
    static std::false_type check(...);
    using type1 = decltype(check<T>(0));
public:
    using type = std::integral_constant<bool,
        type1::value &&
        has_get_io_service<T>::type::value>;
};

template<class T>
class is_AsyncWriteStream
{
    template<class U, class R = decltype(
        std::declval<U>().async_write_some(
            std::declval<ConstBufferSequence>(),
                std::declval<WriteHandler>()),
                    std::true_type{})>
    static R check(int);
    template<class>
    static std::false_type check(...);
    using type1 = decltype(check<T>(0));
public:
    using type = std::integral_constant<bool,
        type1::value &&
        has_get_io_service<T>::type::value>;
};

} // detail
} // boost

#endif
