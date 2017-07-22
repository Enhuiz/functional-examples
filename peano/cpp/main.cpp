#include <iostream>
#include <type_traits>

struct Zero;

template <typename N>
struct Successor;

template <typename N, typename M>
struct plus;

template <typename N>
struct plus<N, Zero>
{
    using type = N;
};

template <typename N, typename M>
struct plus<N, Successor<M>>
{
    using type = Successor<typename plus<N, M>::type>;
};

// helpers
template <int n>
struct int_to_natural;

template <>
struct int_to_natural<0>
{
    using type = Zero;
};

template <int n>
struct int_to_natural
{
    static_assert(n >= 0, "A Natural number must be a non-negative Integer.");
    using type = Successor<typename int_to_natural<n - 1>::type>;
};

template <typename N>
struct natural_to_int;

template <>
struct natural_to_int<Zero>
{
    static constexpr int value = 0;
};

template <typename N>
struct natural_to_int<Successor<N>>
{
    static constexpr int value = 1 + natural_to_int<N>::value;
};

// main
int main()
{
    using five = int_to_natural<5>::type;
    using ten = int_to_natural<10>::type;
    using sum = plus<five, ten>::type;
    int value = natural_to_int<sum>::value;

    std::cout << value << std::endl;

    return 0;
}