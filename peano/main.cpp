#include <iostream>
#include <typeinfo>

namespace peano
{
struct zero
{
    using type = zero;
};

template <typename N>
struct successor
{
    using type = successor;
};

template <typename N, typename M>
struct plus;

template <typename N>
struct plus<N, zero>
{
    using type = N;
};

template <typename N, typename M>
struct plus<N, successor<M>>
{
    using type = successor<typename plus<N, M>::type>;
};

template <int N, bool Valid = N >= 0>
struct int_to_natural;

template <>
struct int_to_natural<0>
{
    using type = zero;
};

template <int N>
struct int_to_natural<N, true>
{
    using type = successor<typename int_to_natural<N - 1>::type>;
};

template <int N>
struct int_to_natural<N, false>
{
    static_assert(N >= 0, "A Natural number must be a non-negative Integer.");
};

template <typename N>
struct natural_to_int;

template <>
struct natural_to_int<zero>
{
    static constexpr int value = 0;
};

template <typename N>
struct natural_to_int<successor<N>>
{
    static constexpr int value = 1 + natural_to_int<N>::value;
};
}

int main()
{
    using five = peano::int_to_natural<5>::type;
    using ten = peano::int_to_natural<10>::type;
    using sum = peano::plus<five, ten>::type;
    int value = peano::natural_to_int<sum>::value;

    std::cout << value << std::endl;
    std::cout << typeid(sum()).name() << std::endl;

    return 0;
}