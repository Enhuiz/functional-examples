#ifndef UTILS_HPP
#define UTILS_HPP

namespace calc
{

using Integer = int;
using Char = char;

template <char... CS>
struct String
{
    using type = String;
};

template <const char *S, int I = 0, int C = S[I], char... CS>
struct parse_string : parse_string<S, I + 1, S[I + 1], CS..., C>
{
};

template <const char *S, int I, char... CS>
struct parse_string<S, I, 0, CS...> : String<CS...>
{
};
}
#endif