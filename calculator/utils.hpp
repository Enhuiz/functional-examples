#ifndef UTILS_HPP
#define UTILS_HPP

namespace calc
{

using Integer = int;
using Char = char;

template <Char C, typename Cs>
struct CharCons
{
    using type = CharCons;
};

template <bool B, typename T, typename F>
struct conditional
{
    using type = T;
};

template <typename T, typename F>
struct conditional<false, T, F>
{
    using type = F;
};

struct Empty;

template <const char *S, int I = 0, int C = S[I]>
struct parse_string
{
    using type = CharCons<C, typename parse_string<S, I + 1>::type>;
};

template <const char *S, int I>
struct parse_string<S, I, 0>
{
    using type = Empty;
};

template <Char C>
struct isdigit
{
    static constexpr bool value = C >= '0' && C <= '9';
};

template <Char C>
struct isalpha
{
    static constexpr bool value = (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z');
};

template <Char C>
struct isspace
{
    static constexpr bool value = C == ' ' || C == '\n' || C == '\r';
};

template <typename First, typename Second>
struct Pair
{
    using type = Pair;
    using first = First;
    using second = Second;
};

template <template <Char C> class Pred, typename S>
struct span
{
    template <typename Acc, typename Cs>
    struct spanImpl;

    template <typename Acc>
    struct spanImpl<Acc, Empty>
    {
        using type = Pair<Acc, Empty>;
    };

    template <typename Acc, Char C, typename Cs>
    struct spanImpl<Acc, CharCons<C, Cs>>
    {
        template <typename T>
        struct branchTrue
        {
            using type = Pair<CharCons<C, typename T::type::first>, typename T::type::second>;
        };

        template <typename T>
        struct branchFalse
        {
            using type = typename T::type;
        };

        using branch = typename conditional<
            Pred<C>::value,
            branchTrue<spanImpl<Acc, Cs>>,
            branchFalse<Pair<Acc, CharCons<C, Cs>>>>::type;

        using type = typename branch::type;
    };

    using type = typename spanImpl<Empty, S>::type;
};
}
#endif