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

template <typename... T>
struct Tokens
{
    using type = Tokens;
};

template <typename S, typename... T>
struct tokenize;

template <typename... T>
struct tokenize<String<>, T...> : Tokens<T...>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'+', CS...>, T...> : tokenize<String<CS...>, T..., TokOp<Plus>>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'-', CS...>, T...> : tokenize<String<CS...>, T..., TokOp<Minus>>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'*', CS...>, T...> : tokenize<String<CS...>, T..., TokOp<Times>>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'/', CS...>, T...> : tokenize<String<CS...>, T..., TokOp<Div>>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'=', CS...>, T...> : tokenize<String<CS...>, T..., TokAssign>
{
};

template <Char... CS, typename... T>
struct tokenize<String<'(', CS...>, T...> : tokenize<String<CS...>, T..., TokLParen>
{
};

template <Char... CS, typename... T>
struct tokenize<String<')', CS...>, T...> : tokenize<String<CS...>, T..., TokRParen>
{
};
}

#endif