#include <iostream>
#include <typeinfo>
#include "lexer.hpp"

constexpr char a[] = "12#";
constexpr char b[] = "141223";

int main()
{

    using namespace calc;
    using namespace std;

    using s = typename parse_string<a>::type;
    cout << typeid(s).name() << endl;

    using sp = typename span<calc::isdigit, s>::type;
    cout << typeid(sp).name() << endl;

    auto num = read<typename parse_string<b>::type>::value;
    cout << num << endl;

    // using tokens = typename tokenize<s>::type;
    // cout << typeid(tokens).name() << endl;
}