
#include <cnl/cstdint.h>
#include <cnl/_impl/assert.h>
#include <cnl/_impl/ostream.h>

#include <string>

namespace cnl {
    namespace _impl {
        std::string to_string(cnl::int128 const& n)
        {
            using std::to_string;
            CNL_ASSERT(n < 0x7fffffffffffffff);
            return to_string(cnl::int64(n));
        }
    }
}

#include <cnl/all.h>

#include <iostream>
#include <string>
#include <type_traits>

using namespace cnl::literals;

template<typename Scalar>
auto divide(Scalar const& n, Scalar const& d)
-> typename std::enable_if<std::is_floating_point<Scalar>::value, decltype(n / d)>::type {
    return n / d;
}

template<typename NumeratorRep, int NumeratorExponent, typename DenominatorRep, int DenominatorExponent>
auto divide(
        cnl::fixed_point<NumeratorRep, NumeratorExponent> const& n,
        cnl::fixed_point<DenominatorRep, DenominatorExponent> const& d) {
    return cnl::quotient(n, d);
}

template<
        typename NumeratorNumerator, typename NumeratorDenominator,
        typename DenominatorNumerator, typename DenominatorDenominator>
auto divide(
        cnl::fraction<NumeratorNumerator, NumeratorDenominator> const& n,
        cnl::fraction<DenominatorNumerator, DenominatorDenominator> const& d) {
    return n / d;
}

// from: https://medium.com/@bellmar/is-cobol-holding-you-hostage-with-math-5498c0eb428b
template<typename Scalar>
auto iterate_simple(Scalar const& y, Scalar const& z)
{
    auto n = Scalar(1500.);
    auto a = divide(n, z);
    auto b = Scalar(815.);
    auto c = Scalar{a};
    auto d = b - c;
    auto e = Scalar(108.);
    auto f = Scalar(divide(d, y));
    auto g = e - f;
//    cnl::reduce(e);
    return g;
}

template<typename Scalar>
auto iterate(Scalar const& y, Scalar const& z)
{
    return iterate_simple(y, z);
}

template<typename Scalar>
auto iterate(
        cnl::fraction<cnl::overflow_integer<Scalar, cnl::throwing_overflow_tag>> const& y,
        cnl::fraction<cnl::overflow_integer<Scalar, cnl::throwing_overflow_tag>> const& z)
{
    try {
        return iterate_simple(y, z);
    }
    catch (std::overflow_error const& e) {
        using fraction = std::remove_reference_t<decltype(y)>;
        return iterate(
                fraction(y.numerator/2, y.denominator/2),
                fraction(z.numerator/2, z.denominator/2));
    }
}

template<typename Scalar>
void test(char const* const title)
{
    using std::cout;
    cout << title << '\n';
    auto print_row = [&](int iteration, Scalar const& value) {
        cout << iteration << '\t' << cnl::to_string(value) << "==" << static_cast<double>(value) << '\n';
    };

    auto previous = Scalar(cnl::fraction(16, 4));  // 4
    print_row(0, previous);

    Scalar current{cnl::fraction(17, 4)};   // 4.25
    print_row(1, current);

    auto divergence_iteration = 0;
    for (auto n = 2; n<100; ++n) {
        Scalar const next = iterate(current, previous);
        if (next==current) {
            break;
        }
        previous = current;
        //previous = reduce(current);
        current = next;

        if (!divergence_iteration && cnl::abs(current-Scalar(5.)) > cnl::abs(previous-Scalar(5.))) {
            divergence_iteration = n;
        }

        print_row(n, current);
    }

    cout << "converged until " << divergence_iteration << "\n\n";
}

int main()
{
//    using fract = cnl::fraction<cnl::int128>;
//    using fract = cnl::fraction<cnl::overflow_integer<cnl::elastic_integer<24>, cnl::throwing_overflow_tag>>;
    using fract = cnl::fraction<cnl::overflow_integer<cnl::elastic_integer<31>>>;
//    using fract = cnl::fraction<cnl::elastic_integer<24>>;
//    using fract = float;

    auto z = fract{16, 4};
    auto y = fract{17, 4};
//    fract y = 4;
//    fract z = 4;
    auto x = iterate(y, z);
    std::cout << to_string(x);
//    test<float>("single precision floaint point");
//    test<double>("double precision floaint point");
//    test<long double>("extended precision floaint point");
    test<cnl::fixed_point<cnl::int64, -52>>("Q25.38");
//    test<cnl::fixed_point<cnl::elastic_integer<49>, -38>>("Q11.38");
//    test<cnl::static_number<42, -30>>("cnl::static_number<42, -30>");

//    test<cnl::fraction<cnl::int64, cnl::int64>>("cnl::fraction<cnl::int64, cnl::int64>");
//    test<cnl::fraction<cnl::int128, cnl::int128>>("cnl::fraction<cnl::int128, cnl::int128>");
//    test<cnl::fraction<cnl::overflow_integer<cnl::elastic_integer<31>, cnl::throwing_overflow_tag>>>(
//            "cnl::fraction<cnl::overflow_integer<cnl::int64, cnl::overflow_integer>>");
//    test<cnl::fraction<int>>(
//            "cnl::fraction<cnl::overflow_integer<cnl::int64, cnl::overflow_integer>>");
}
