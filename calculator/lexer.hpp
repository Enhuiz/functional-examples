#ifndef LEXER_HPP
#define LEXER_HPP

#include "utils.hpp"

namespace calc
{

struct Plus;
struct Minus;
struct Times;
struct Div;

struct TokAssign;
struct TokLParen;
struct TokRParen;
struct TokEnd;

template <typename OP>
struct TokOp;

template <typename S>
struct TokIdent;

template <Integer X>
struct TokNum;

template <typename Tok, typename Tail>
struct TokenCons
{
};

template <typename S>
struct tokenize;

template <Char C, typename Cs>
struct number_token;

template <Char C, typename Cs>
struct ident_token;

template <>
struct tokenize<Empty>
{
    using type = Empty;
};

template <typename Cs>
struct tokenize<CharCons<'+', Cs>>
{
    using type = TokenCons<TokOp<Plus>, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<'-', Cs>>
{
    using type = TokenCons<TokOp<Minus>, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<'*', Cs>>
{
    using type = TokenCons<TokOp<Times>, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<'/', Cs>>
{
    using type = TokenCons<TokOp<Div>, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<'=', Cs>>
{
    using type = TokenCons<TokAssign, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<'(', Cs>>
{
    using type = TokenCons<TokLParen, typename tokenize<Cs>::type>;
};

template <typename Cs>
struct tokenize<CharCons<')', Cs>>
{
    using type = TokenCons<TokRParen, typename tokenize<Cs>::type>;
};

template <Char C, typename Cs>
struct tokenize<CharCons<C, Cs>>
{
    using branch = typename conditional<
        isdigit<C>::value,
        number_token<C, Cs>,
        typename conditional<
            isalpha<C>::value,
            ident_token<C, Cs>,
            typename conditional<
                isspace<C>::value,
                tokenize<Cs>,
                Empty>::type>::type>::type;

    using type = typename branch::type;
};

template <Char C, typename Cs>
struct number_token
{
    using type = number_token;
};

template <Char C, typename Cs>
struct ident_token
{
    using type = ident_token;
};
}

#endif