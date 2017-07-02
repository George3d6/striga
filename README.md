# Striga

A basic string manipulation library for C++, implemented in a single header file for ease of inclusion.

I find myself re-writting certain string operations again and again because the std, sadly enough, doesn't have enough "high level" funcions/methods for its string types. This is a somewhat generic library meant to remove
string operation boilerplate from code by providing decently efficient, side-effect free, string operations.

If you wish to request some functionality be added to the library feel free to open an issue or make a pull request with the desired function interface (or even implementation, if you have the time).

## Usage

Include ``` striga.h ``` in your project.

Use the functions in the namepsace striga and the namespace striga::mut if you want the mutable versions of
the functions.

Example usage:

```c++

#include "striga.h"
#include <string>
#include <queue>

std::string test1{"I shall be split at whitespace"};
std::deque<std::string> container1 = striga::split<std::deque>(test1, " ");
for(const auto& element : container1) {
    std::cout << element << std::endl;
}

std::wstring test2{L"I don't need the word need, I need the word greed"};
auto result_replace = striga::replace(test2, L"need", L"greed");
std::wcout << result_replace << std::endl;

std::u16string test3{u"I don't need the word need"};
auto result_remove = striga::remove(test3, u"need");
assert(result_remove == u"I don't  the word ");


std::u32string trimme = U"   I have 3 whitespaces in the beginging";
auto trimed = striga::trim_left(trimme, U" ");
assert(trimed == U"I have 3 whitespaces in the beginging");


std::string uplow{"ab12cD"};
assert(striga::to_uppercase_ASCII(uplow) == std::string{"AB12CD"});
assert(striga::to_lowercase_ASCII(uplow) == std::string{"ab12cd"});

//Doesn't work for greek, cyrillic... etc :/ (Yet)
std::string greek{"αβΓΘ"};
auto upper_greek = striga::to_uppercase_ASCII(greek);
assert(upper_greek == std::string{"αβΓΘ"});
auto lower_greek = striga::to_lowercase_ASCII(greek);
assert(lower_greek == std::string{"αβΓΘ"});

```

## State of implementation

Currently the library is unfinished, I don't have enough testcases for it, the documentation is basically just the tests&examples and a few lines of comments... I will work on fixing this as I build more functionality.

I'm also quite certain some algorithms need improving... but for that I will have to write benchmarks and that's a whole other can of worms I will have to open.

Any contribution in the form of code or reviews is more than weclome, I mainly placed this here in the hopes of getting some code review.

Currently the library is quite small so I think compilation time is not a problem and I can leave it as a header only, rather than annoying people with including and implementation.