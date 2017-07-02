#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <type_traits>

#include <cctype>

namespace striga {

namespace black_magic {

/*
 * For credit where creidt is due, this pattern was explained to me by Barry over at SO:
 * https://stackoverflow.com/questions/44834415/implicit-template-type-deduction-with-two-arguments-of-different-types/44834741#44834741
 * Used to place the type T in a non deduceable context
 * Better than using decltype(first) because it comes without the const qualifier (or lack thereof) and & / &&
 */
template <class T> struct dont_deduce { using type = T; };
template <class T> using dont_deduce_t = typename dont_deduce<T>::type;
}


namespace mut {

template <class String>
void to_lowercase_ASCII(String& original) noexcept {
    std::transform(original.begin(), original.end(), original.begin(), tolower);
}

template <class String>
void to_uppercase_ASCII(String& original) noexcept {
    std::transform(original.begin(), original.end(), original.begin(), toupper);
}



//@WEIRD: Decltype doesn't work here, apparently using decltype invalidates the const...
template <class String>
void trim_right(String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {
    auto trim_position = original.size();
     for(auto i = 1; i <= original.size(); i++) {
        String purge{};
#ifdef RESERVER_SPACE_OPTIMIZATION
    purge.reserve(i);
#endif
        purge.reserve(i * pattern.size());
        //@TODO: Look into using std::generate
        for(auto n = 0; n < i; n++) {
            purge += pattern;
        }
        auto position = original.rfind(purge);
        if(position + purge.size() == original.size() && (i <= nr || nr < 0) && position != String::npos)  {
             trim_position = position;
        } else {
            break;
        }
     }
     original.resize(trim_position);
}

}

template <template<class...>class Container = std::vector, class String>
Container<String> split(const String& to_split, const black_magic::dont_deduce_t<String>& delimiter) {
    auto current_position = 0;
    auto delimiter_position = to_split.find(delimiter);
    Container<String> parts{};
    while(delimiter_position != String::npos) {
        parts.emplace_back(to_split.substr(current_position, delimiter_position - current_position));
        current_position = delimiter_position + delimiter.size();
        delimiter_position = to_split.find(delimiter, current_position);
    }
    parts.emplace_back(to_split.substr(current_position, to_split.length()));
    return parts;
}

template <template<class...>class Container = std::vector, class String>
String join_container(const Container<String>& container, const black_magic::dont_deduce_t<String>& join_with) {
    String holder{};
#ifdef RESERVER_SPACE_OPTIMIZATION
    holder.reserve(2*container.begin()->size()*container.size());
#endif
    //Faster then comparing iterator addresses
    auto is_first = true;
    for(const auto& str : container) {
        if(!is_first)
            holder += join_with + str;
        else
            holder += str;
        is_first = false;
    }
    return holder;
}

template <class String>
String replace(const String& original, const black_magic::dont_deduce_t<String>& pattern, const black_magic::dont_deduce_t<String>& replacement) {
    auto container = striga::split(original, pattern);
    return striga::join_container(container, replacement);
}

template <class String>
String remove(const String& original, const black_magic::dont_deduce_t<String>& pattern) {
    const String default_value;
    return striga::replace(original, pattern, default_value);
}

template <class String>
bool contains(const String& find_in, const black_magic::dont_deduce_t<String>& pattern) noexcept {
    return find_in.find(pattern) != String::npos;
}

template <class String>
String trim_right(const String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {

    String copy = original;
    mut::trim_right(copy, pattern, nr);
    return copy;

}

template <class String>
String trim_left(const String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {
    auto trim_position = 0;
     for(auto i = 1; i <= original.size(); i++) {
        String purge{};
#ifdef RESERVER_SPACE_OPTIMIZATION
    purge.reserve(i);
#endif
        purge.reserve(i * pattern.size());
        //@TODO: Look into using std::generate
        for(auto n = 0; n < i; n++) {
            purge += pattern;
        }
        auto position = original.find(purge);
        if(position == 0 && (i <= nr || nr < 0) && position != String::npos) {
            trim_position = purge.size();
        } else {
            break;
        }
     }
     return original.substr(trim_position, original.size() - 1);
}

//How do these two work with non Latin/Greek characters ?

template <class String>
String to_lowercase_ASCII(const String& original) noexcept {
    String the_copy = original;
    mut::to_lowercase_ASCII(the_copy);
    return the_copy;
}

template <class String>
String to_uppercase_ASCII(const String& original) noexcept {

    String the_copy = original;
    mut::to_uppercase_ASCII(the_copy);
    return the_copy;

}

}
