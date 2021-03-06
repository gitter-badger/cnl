
//          Copyright John McFarlane 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if !defined(CNL_IMPL_ROUNDING_NEAREST_ROUNDING_TAG_H)
#define CNL_IMPL_ROUNDING_NEAREST_ROUNDING_TAG_H

/// compositional numeric library
namespace cnl {
    /// \brief tag to specify round-to-nearest behavior in arithemtic operations
    ///
    /// Arithmetic operations using this tag round to the nearest representatable value in situations where the
    /// precise value cannot be represented.
    ///
    /// \headerfile cnl/rounding.h
    /// \sa cnl::rounding_integer,
    /// cnl::add, cnl::convert, cnl::divide, cnl::left_shift, cnl::multiply, cnl::subtract,
    /// cnl::native_rounding_tag
    struct nearest_rounding_tag {
    };
}

#endif  // CNL_IMPL_ROUNDING_NEAREST_ROUNDING_TAG_H
