
//          Copyright John McFarlane 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// \file
/// \brief fixed_point specializations of math constants from <cnl/numeric.h>

#ifndef FIXED_POINT_CONSTANTS_H_
#define FIXED_POINT_CONSTANTS_H_

#include "type.h"

#include "../used_digits.h"

/// compositional numeric library
namespace cnl {

#if defined(__cpp_inline_variables)

    ////////////////////////////////////////////////////////////////////////////////
    // scaled_integer specializations of math constants from numeric.h

    namespace _impl {
        template<typename Rep, int Exponent>
        constexpr auto pi(int const max_iterations) {
            using fp = scaled_integer<Rep, Exponent>;
            constexpr auto four = scaled_integer<Rep, 3 - digits_v<Rep>>{4.};

            auto previous = fp{3.};
            for(auto n = 2; n != (max_iterations << 1); n += 4) {
                auto const addend     = four / ((n+0L) * (n+1L) * (n+2L));
                auto const subtrahend = four / ((n+2L) * (n+3L) * (n+4L));
                auto next = fp{previous + addend - subtrahend};
                if (next == previous) {
                    return next;
                }
                previous = next;
            }
            return previous;
        }

        template<typename Rep, int Exponent>
        constexpr auto pi() {
            return pi<Rep, Exponent>(0);
        }

        template<typename Rep, int Exponent>
        constexpr auto e(int const max_iterations) {
            using fp = scaled_integer<Rep, Exponent>;
            constexpr auto one = scaled_integer<Rep, 2 - digits_v<Rep>>{1.};

            auto previous = fp{2.};
            auto factor = 2;
            for (auto n = 2; n != max_iterations; ++ n, factor *= n) {
                auto const addend = one / factor;
                auto next = fp{previous + addend};
                if (next == previous) {
                    return next;
                }
                previous = next;
            }
            return previous;
        }

        template<typename Rep, int Exponent>
        constexpr auto e() {
            return e<Rep, Exponent>(0);
        }

        // Given two alternative ways to generate a constant value:
        // tries to choose the best and returns the result.
        template<typename Float, typename Rep, int Exponent>
        constexpr auto constant_with_fallback(Float constant, scaled_integer<Rep, Exponent>(*procedure)()) {
            using fp = scaled_integer<Rep, Exponent>;

            auto const required_integer_digits = used_digits(static_cast<int>(constant));

            constexpr auto fixed_fractional_digits = fractional_digits<fp>::value;
            // expect: integer_digits<fp>::value >= required_integer_digits

            constexpr auto float_digits = std::numeric_limits<Float>::digits;
            auto const float_fractional_digits = float_digits - required_integer_digits;

            return (float_fractional_digits >= fixed_fractional_digits)
                ? fp{constant}
                   : procedure();
        }
    }

    /// specialization of \ref cnl::e for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> e<scaled_integer<Rep, Exponent>> {
        _impl::constant_with_fallback<long double, Rep, Exponent>(e<long double>, _impl::e<Rep, Exponent>)
    };

    /// specialization of \ref cnl::log2e for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> log2e<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ log2e<long double> }
    };

    /// specialization of \ref cnl::log10e for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> log10e<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ log10e<long double> }
    };

    /// specialization of \ref cnl::pi for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> pi<scaled_integer<Rep, Exponent>>{
        _impl::constant_with_fallback<long double, Rep, Exponent>(pi<long double>, _impl::pi<Rep, Exponent>)
    };

    /// specialization of \ref cnl::invpi for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> invpi<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ invpi<long double> }
    };

    /// specialization of \ref cnl::invsqrtpi for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> invsqrtpi<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ invsqrtpi<long double> }
    };

    /// specialization of \ref cnl::ln2 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> ln2<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ ln2<long double> }
    };

    /// specialization of \ref cnl::ln10 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> ln10<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ ln10<long double> }
    };

    /// specialization of \ref cnl::sqrt2 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> sqrt2<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ sqrt2<long double> }
    };

    /// specialization of \ref cnl::sqrt3 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> sqrt3<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ sqrt3<long double> }
    };

    /// specialization of \ref cnl::invsqrt2 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> invsqrt2<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ invsqrt2<long double> }
    };

    /// specialization of \ref cnl::invsqrt3 for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> invsqrt3<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ invsqrt3<long double> }
    };

    /// specialization of \ref cnl::radian for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> radian<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ radian<long double> }
    };

    /// specialization of \ref cnl::egamma for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> egamma<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ egamma<long double> }
    };

    /// specialization of \ref cnl::phi for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> phi<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ phi<long double> }
    };

    /// specialization of \ref cnl::catalan for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> catalan<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ catalan<long double> }
    };

    /// specialization of \ref cnl::apery for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> apery<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ apery<long double> }
    };

    /// specialization of \ref cnl::glaisher for \ref cnl::scaled_integer
    template<typename Rep, int Exponent> inline constexpr scaled_integer<Rep, Exponent> glaisher<scaled_integer<Rep, Exponent>> {
        scaled_integer<Rep, Exponent>{ glaisher<long double> }
    };
#endif  // defined(__cpp_inline_variables)
}

#endif // FIXED_POINT_CONSTANTS_H_
