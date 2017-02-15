//
// Copyright (c) 2017 Felipe Magno de Almeida (felipe@expertisesolutions.com.br)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BEAST_CORE_REF_HPP
#define BEAST_CORE_REF_HPP

#include <functional>

namespace beast {

template <typename T>
T& unwrap_ref(T& object) { return object; }
template <typename T>
T& unwrap_ref(std::reference_wrapper<T> ref) { return ref.get(); }

}

#endif
