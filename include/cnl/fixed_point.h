
//          Copyright John McFarlane 2015 - 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief contains fixed_point alias to scaled_integer

#if !defined(CNL_FIXED_POINT_H)
#define CNL_FIXED_POINT_H 1

#include "scaled_integer.h"

/// compositional numeric library
namespace cnl {
    using fixed_point = scaled_integer;
}

#endif  // CNL_FIXED_POINT_H
