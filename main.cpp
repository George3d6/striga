#include "striga.h"

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <cassert>

template<template<class...>class Container>
void test_suite() {

    //With string
    {
        std::cout << "====================================" << std::endl;
        std::cout << "======Testing for std::string!======" << std::endl;
        std::cout << "====================================" << std::endl;
        std::string test1{"I shall be split at whitespace"};
        auto at = " ";
        auto container1 = striga::split(test1, at);
        assert(container1.size() == 6);
        assert(container1.at(1) == std::string{"shall"});
        assert(container1.at(5) == std::string{"whitespace"});
        std::cout << "White sapce separator working" << std::endl;

        std::string test2{"ISAlTamSAlTaSAlTcupSAlTofSAlTfineSAlTsalt"};
        Container<std::string> container2 = striga::split<Container>(test2, "SAlT");
        assert(container2.size() == 7);
        assert(container2.front() == std::string{"I"});
        assert(container2.back() == std::string{"salt"});
        std::cout << "Custom string separator working" << std::endl;

        auto result = striga::replace(test2, "SAlT", " ");
        assert(result == "I am a cup of fine salt");
        std::cout << "Replace is working" << std::endl;

        result = striga::remove(test1, " ");
        assert(result.find(" ") == std::string::npos);
        std::cout << "Remove test passing" << std::endl;

        std::string trimme = " I have 3 ws at the enddd   ";
        auto trimed = striga::trim_right(trimme, " ");
        assert(trimed == " I have 3 ws at the enddd");

        trimed = striga::trim_left(trimed, " ");
        assert(trimed == "I have 3 ws at the enddd");

        assert(striga::trim_right(trimed, " ") == trimed);
        assert(striga::trim_right(trimed, "dd") == trimed.substr(0,trimed.size() - 2));
        trimme = "baaaaaaaaaa";
        trimed = striga::trim_right(trimme, "aaa", 2);
        assert(trimed == "baaaa");
        trimed = striga::trim_right(trimme, "aaa");
        assert(trimed == "ba");

        std::cout << "Trim test passing" << std::endl;

        std::string uplow{"ab12cD"};
        assert(striga::to_uppercase_ASCII(uplow) == std::string{"AB12CD"});
        assert(striga::to_lowercase_ASCII(uplow) == std::string{"ab12cd"});

        std::string greek{"αβΓΘ"};
        auto upper_greek = striga::to_uppercase_ASCII(greek);
        assert(upper_greek == std::string{"αβΓΘ"});
        auto lower_greek = striga::to_lowercase_ASCII(greek);
        assert(lower_greek == std::string{"αβΓΘ"});

        std::cout << "To upper and to lower working !" << std::endl;
        std::cout << "\n" << std::endl;
    }

    //With wstring
    {
        std::cout << "====================================" << std::endl;
        std::cout << "======Testing for std::wstring======" << std::endl;
        std::cout << "====================================" << std::endl;
        std::wstring test1{L"I shall be split at whitespace"};
        auto at = L" ";
        auto container1 = striga::split(test1, at);
        assert(container1.size() == 6);
        assert(container1.at(1) == std::wstring{L"shall"});
        assert(container1.at(5) == std::wstring{L"whitespace"});
        std::cout << "White sapce separator working" << std::endl;

        std::wstring test2{L"ISAlTamSAlTaSAlTcupSAlTofSAlTfineSAlTsalt"};
        Container<std::wstring> container2 = striga::split<Container>(test2, L"SAlT");
        assert(container2.size() == 7);
        assert(container2.front() == std::wstring{L"I"});
        assert(container2.back() == std::wstring{L"salt"});
        std::cout << "Custom string separator working\n\n" << std::endl;

        auto result = striga::replace(test2, L"SAlT", L" ");
        assert(result == L"I am a cup of fine salt");
        std::cout << "Replace is working" << std::endl;

        result = striga::remove(test1, L" ");
        assert(result.find(L" ") == std::wstring::npos);
        std::cout << "Remove test passing" << std::endl;

        std::wstring trimme = L" I have 3 ws at the enddd   ";
        std::wstring trimed = striga::trim_right(trimme, L" ");
        assert(trimed == L" I have 3 ws at the enddd");

        trimed = striga::trim_left(trimed, L" ");
        assert(trimed == L"I have 3 ws at the enddd");

        assert(striga::trim_right(trimed, L" ") == trimed);
        assert(striga::trim_right(trimed, L"dd") == trimed.substr(0,trimed.size() - 2));
        trimme = L"baaaaaaaaaa";
        trimed = striga::trim_right(trimme, L"aaa", 2);
        assert(trimed == L"baaaa");
        trimed = striga::trim_right(trimme, L"aaa");
        assert(trimed == L"ba");

        std::cout << "Trim test passing" << std::endl;

        std::wstring uplow{L"ab12cD"};
        assert(striga::to_uppercase_ASCII(uplow) == std::wstring{L"AB12CD"});
        assert(striga::to_lowercase_ASCII(uplow) == std::wstring{L"ab12cd"});

        std::wstring greek{L"αβΓΘ"};
        auto upper_greek = striga::to_uppercase_ASCII(greek);
        assert(upper_greek == std::wstring{L"αβΓΘ"});
        auto lower_greek = striga::to_lowercase_ASCII(greek);
        assert(lower_greek == std::wstring{L"αβΓΘ"});

        std::cout << "To upper and to lower working !" << std::endl;
        std::cout << "\n" << std::endl;
    }

    {
        std::cout << "====================================" << std::endl;
        std::cout << "=====Testing for std::u32string=====" << std::endl;
        std::cout << "====================================" << std::endl;
        //With u32string
        std::u32string test1{U"I shall be split at whitespace"};
        auto at = U" ";
        auto container1 = striga::split(test1, at);
        assert(container1.size() == 6);
        assert(container1.at(1) == std::u32string{U"shall"});
        assert(container1.at(5) == std::u32string{U"whitespace"});
        std::cout << "White sapce separator working" << std::endl;

        std::u32string test2{U"ISAlTamSAlTaSAlTcupSAlTofSAlTfineSAlTsalt"};
        Container<std::u32string> container2 = striga::split<Container>(test2, U"SAlT");
        assert(container2.size() == 7);
        assert(container2.front() == std::u32string{U"I"});
        assert(container2.back() == std::u32string{U"salt"});
        std::cout << "Custom string separator working\n\n" << std::endl;

        std::u32string uplow{U"ab12cD"};
        assert(striga::to_uppercase_ASCII(uplow) == std::u32string{U"AB12CD"});
        assert(striga::to_lowercase_ASCII(uplow) == std::u32string{U"ab12cd"});
    }

    {
        std::cout << "====================================" << std::endl;
        std::cout << "=====Testing for std::u16string=====" << std::endl;
        std::cout << "====================================" << std::endl;
        //With u16string
        std::u16string test1{u"I shall be split at whitespace"};
        auto at = u" ";
        auto container1 = striga::split(test1, at);
        assert(container1.size() == 6);
        assert(container1.at(1) == std::u16string{u"shall"});
        assert(container1.at(5) == std::u16string{u"whitespace"});
        std::cout << "White sapce separator working" << std::endl;

        std::u16string test2{u"ISAlTamSAlTaSAlTcupSAlTofSAlTfineSAlTsalt"};
        Container<std::u16string> container2 = striga::split<Container>(test2, u"SAlT");
        assert(container2.size() == 7);
        assert(container2.front() == std::u16string{u"I"});
        assert(container2.back() == std::u16string{u"salt"});
        std::cout << "Custom string separator working\n\n" << std::endl;
    }

}

int main() {

    //#define RESERVER_SPACE_OPTIMIZATION //Uncompent to make sure the macro enabled version also works

    test_suite<std::list>();
    test_suite<std::vector>();
    test_suite<std::deque>();

    /// striga::split
    std::string test1{"I shall be split at whitespace"};
    std::deque<std::string> container1 = striga::split<std::deque>(test1, " ");
    for(const auto& element : container1) {
        std::cout << element << std::endl;
    }

    //Readme example
    /// striga::remove && striga::replace
    std::wstring test2{L"I don't need the word need, I need the word greed"};
    auto result_replace = striga::replace(test2, L"need", L"greed");
    std::wcout << result_replace << std::endl;

    std::u16string test3{u"I don't need the word need"};
    auto result_remove = striga::remove(test3, u"need");
    assert(result_remove == u"I don't  the word ");

    /// striga::trim_left && striga::trim_right
    std::u32string trimme = U"   I have 3 whitespaces in the beginging";
    auto trimed = striga::trim_left(trimme, U" ");
    assert(trimed == U"I have 3 whitespaces in the beginging");

    /// striga::to_uppercase_ASCII && striga::to_lowercase_ASCII
    std::string uplow{"ab12cD"};
    assert(striga::to_uppercase_ASCII(uplow) == std::string{"AB12CD"});
    assert(striga::to_lowercase_ASCII(uplow) == std::string{"ab12cd"});

    //Doesn't work for greek, cyrillic... etc :/ (Yet)
    std::string greek{"αβΓΘ"};
    auto upper_greek = striga::to_uppercase_ASCII(greek);
    assert(upper_greek == std::string{"αβΓΘ"});
    auto lower_greek = striga::to_lowercase_ASCII(greek);
    assert(lower_greek == std::string{"αβΓΘ"});

    /// striga::join_container
    std::vector<std::string> container{"I", "contain", "stuff"};
    assert(striga::join_container(container, " ") == "I contain stuff" );

    /// striga::contains
    assert(striga::contains(std::string{"I contain A"}, "A"));
}
