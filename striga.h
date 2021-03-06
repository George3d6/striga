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

/// Turns all the ASCII compatible chracters of the string to lowercase
template <class String>
void to_lowercase_ASCII(String& original) {
    std::transform(original.begin(), original.end(), original.begin(), tolower);
}

/// Turns all the ASCII compatible chracters of the string to uppercase
template <class String>
void to_uppercase_ASCII(String& original) {
    std::transform(original.begin(), original.end(), original.begin(), toupper);
}

/// Trims a string inplace, the first argument is returned with a maximum of 'nr' occurances of strings 'pattern' removed from the back of it.
/// If nr < 0 it removed all occurances (this is the defauly behavior)
template <class String>
void trim_right(String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {
    auto trim_position = original.size();
    for(typename String::size_type i = 1; i <= original.size(); i++) {
        String purge{};
#ifdef RESERVER_SPACE_OPTIMIZATION
        purge.reserve(i * pattern.size());
#endif
        //@TODO: Look into using std::generate
        for(typename String::size_type n = 0; n < i; n++) {
            purge += pattern;
        }
        auto position = original.rfind(purge);
        if(position + purge.size() == original.size() && (int(i) <= nr || nr < 0) && position != String::npos)  {
            trim_position = position;
        } else {
            break;
        }
    }
    //original.resize(trim_position);
    original.erase(original.begin() + trim_position, original.end());
}


//WRANNING: Possibly very inefficient
/// Trims a string inplace, the first argument is returned with a maximum of 'nr' occurances of strings 'pattern' removed from the front of it.
/// If nr < 0 it removed all occurances (this is the defauly behavior)
template <class String>
void trim_left(String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {
    auto trim_position = 0;
    for(typename String::size_type i = 1; i <= original.size(); i++) {
        String purge{};
#ifdef RESERVER_SPACE_OPTIMIZATION
        purge.reserve(i);
#endif
        purge.reserve(i * pattern.size());
        //@TODO: Look into using std::generate
        for(typename String::size_type n = 0; n < i; n++) {
            purge += pattern;
        }
        auto position = original.find(purge);
        if(position == 0 && (int(i) <= nr || nr < 0) && position != String::npos) {
            trim_position = purge.size();
        } else {
            break;
        }
    }
    original.erase(original.begin(), original.begin() + trim_position);
}

}

//@TODO: Make an MSVC compaible implementation
/// Split a string based on a delimiter and return a container with the parts (delimiter not included)
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

/// Unite a container into a string using the second argument
template <class Container>
auto join_container(const Container& container, const typename Container::value_type& join_with) {
    typename Container::value_type holder{};
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

/// Replace the occurances of 'pattern' in 'original' with 'replacement'
template <class String>
String replace(const String& original, const black_magic::dont_deduce_t<String>& pattern, const black_magic::dont_deduce_t<String>& replacement) {
    auto container = striga::split(original, pattern);
    return striga::join_container(container, replacement);
}

/// Replace the occurances of 'pattern' in 'original' with nothing
template <class String>
String remove(const String& original, const black_magic::dont_deduce_t<String>& pattern) {
    const String default_value;
    return striga::replace(original, pattern, default_value);
}

/// Check if a string contains 'pattern' and returns true if it does and false if it doesn't
template <class String>
bool contains(const String& find_in, const black_magic::dont_deduce_t<String>& pattern) noexcept {
    return find_in.find(pattern) != String::npos;
}


/// Trims a string, the first argument is returned with a maximum of 'nr' occurances of strings 'pattern' removed from the back of it.
/// If nr < 0 it removed all occurances (this is the defauly behavior)
/// A trimed string is returned and the original is not modified
template <class String>
String trim_right(const String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {

    String copy = original;
    mut::trim_right(copy, pattern, nr);
    return copy;

}

/// Trims a string, the first argument is returned with a maximum of 'nr' occurances of strings 'pattern' removed from the front of it.
/// If nr < 0 it removed all occurances (this is the defauly behavior)
/// A trimed string is returned and the original is not modified
template <class String>
String trim_left(const String& original, const black_magic::dont_deduce_t<String>& pattern, int nr = -1) {
    auto trim_position = 0;
    for(typename String::size_type i = 1; i <= original.size(); i++) {
        String purge{};
#ifdef RESERVER_SPACE_OPTIMIZATION
        purge.reserve(i);
#endif
        purge.reserve(i * pattern.size());
        //@TODO: Look into using std::generate
        for(typename String::size_type n = 0; n < i; n++) {
            purge += pattern;
        }
        auto position = original.find(purge);
        if(position == 0 && (int(i) <= nr || nr < 0) && position != String::npos) {
            trim_position = purge.size();
        } else {
            break;
        }
    }
    return original.substr(trim_position, original.size() - 1);
}

//How do these two work with non Latin/Greek characters ?

/// Return a string with all the ASCII compatible chracters of the original string to lowercase
template <class String>
String to_lowercase_ASCII(const String& original) {
    String the_copy = original;
    mut::to_lowercase_ASCII(the_copy);
    return the_copy;
}

/// Return a string with all the ASCII compatible chracters of the original string to uppercase
template <class String>
String to_uppercase_ASCII(const String& original) {

    String the_copy = original;
    mut::to_uppercase_ASCII(the_copy);
    return the_copy;

}

}
