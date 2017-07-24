#include <iostream>
#include <typeinfo>

namespace si
{
template <int...>
struct list
{
    using type = list;
};

template <int I, int N, int... L>
struct unit : unit<I - 1, N - 1, L..., 0>
{
};

template <int N, int... L>
struct unit<0, N, L...> : unit<-1, N - 1, L..., 1>
{
};

template <int I, int... L>
struct unit<I, 0, L...> : list<L...>
{
};

template <typename T, typename U>
struct quantity
{
    quantity(T x) : x(x) {}
    T value() const { return x; }

  private:
    T x;
};

template <typename T, typename U>
quantity<T, U> operator+(const quantity<T, U> &a, const quantity<T, U> &b)
{
    return quantity<T, U>(a.value() + b.value());
}

template <typename T, typename U>
quantity<T, U> operator-(const quantity<T, U> &a, const quantity<T, U> &b)
{
    return quantity<T, U>(a.value() - b.value());
}

template <int A, int B>
struct plus_op
{
    static constexpr int value = A + B;
};

template <int A, int B>
struct minus_op
{
    static constexpr int value = A - B;
};

template <typename U1, typename U2, template <int, int> class OP>
struct transform;

template <template <int... Args1> class U1, template <int... Args2> class U2, int... Args1, int... Args2, template <int, int> class OP>
struct transform<U1<Args1...>, U2<Args2...>, OP>
{
    using type = list<OP<Args1, Args2>::value...>;
};

template <typename T, typename U1, typename U2>
quantity<T, typename transform<U1, U2, plus_op>::type> operator*(const quantity<T, U1> &a, const quantity<T, U2> &b)
{
    using Dim = typename transform<U1, U2, plus_op>::type;
    return quantity<T, Dim>(a.value() * b.value());
}

template <typename T, typename U1, typename U2>
quantity<T, typename transform<U1, U2, minus_op>::type> operator/(const quantity<T, U1> &a, const quantity<T, U2> &b)
{
    using Dim = typename transform<U1, U2, minus_op>::type;
    return quantity<T, Dim>(a.value() / b.value());
}

using length = typename unit<0, 7>::type;
using mass = typename unit<1, 7>::type;
using time = typename unit<2, 7>::type;
using electric_current = typename unit<3, 7>::type;
using thermodynamic_temperature = typename unit<4, 7>::type;
using amount_of_substance = typename unit<5, 7>::type;
using luminous_intensity = typename unit<6, 7>::type;
}

int main()
{
    si::quantity<double, si::length> l(2);
    si::quantity<double, si::time> t(3);
    auto v = l / t;

    si::quantity<double, si::list<1, 0, -1, 0, 0, 0, 0>> v_(2);

    std::cout << typeid(v).name() << std::endl;
    std::cout << typeid(v_).name() << std::endl;
    std::cout << typeid(v + v_).name() << std::endl;
}