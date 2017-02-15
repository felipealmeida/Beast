//
// Copyright (c) 2013-2016 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_HTTP_IMPL_ASYNC_PARSE_IPP_HPP
#define BEAST_HTTP_IMPL_ASYNC_PARSE_IPP_HPP

#include <beast/core/async_stream_concepts.hpp>
#include <beast/core/async_completion.hpp>
#include <beast/core/error.hpp>

namespace beast {
namespace http {

template<class AsyncReadStream,
    class DynamicBuffer, class Parser, class ReadHandler>
typename async_completion<
    ReadHandler, void(error_code)>::result_type
async_parse(AsyncReadStream& stream,
    DynamicBuffer& dynabuf, Parser& parser, ReadHandler&& handler)
{
    static_assert(is_AsyncReadStream<AsyncReadStream>::value,
        "AsyncReadStream requirements not met");
    static_assert(is_DynamicBuffer<DynamicBuffer>::value,
        "DynamicBuffer requirements not met");
    static_assert(is_Parser<Parser>::value,
        "Parser requirements not met");
    beast::async_completion<ReadHandler,
        void(error_code)> completion{handler};
    detail::parse_op<AsyncReadStream, DynamicBuffer,
        Parser, decltype(completion.handler)>{
            completion.handler, stream, dynabuf, parser};
    return completion.result.get();
}

} // http
} // beast

#endif
