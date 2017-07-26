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
}
#endif