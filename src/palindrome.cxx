#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

static const std::set<unsigned char> ALPHANUMERICS {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

auto toLower = [](unsigned char c) -> unsigned char {
    return std::tolower(c);
};
auto isNotAlphaNum = [](unsigned char c) -> bool {
    return !ALPHANUMERICS.contains(c);
};

bool isPalindrome(const std::string& str) {
    std::string stripped{str};

    std::transform(stripped.begin(), stripped.end(), stripped.begin(), toLower);
    stripped.erase(
        std::remove_if(stripped.begin(), stripped.end(), isNotAlphaNum),
        stripped.end()
    );

    std::string reversed{};
    reversed.reserve(stripped.length());

    for(auto it = stripped.end() - 1; it - stripped.cbegin() >= 0; it--) {
        reversed.push_back(*it);
    }

    return stripped == reversed;
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    std::string str1{"Hello World!"},
        str2{"A man, a plan, a canal: Panama"},
        str3{"race a car"},
        str4{" "};
    
    std::cout << "\"" << str1 << "\" is a palindrome: "
        << (isPalindrome(str1) ? "TRUE" : "FALSE") << "\n";
    std::cout << "\"" << str2 << "\" is a palindrome: "
        << (isPalindrome(str2) ? "TRUE" : "FALSE") << "\n";
    std::cout << "\"" << str3 << "\" is a palindrome: "
        << (isPalindrome(str3) ? "TRUE" : "FALSE") << "\n";
    std::cout << "\"" << str4 << "\" is a palindrome: "
        << (isPalindrome(str4) ? "TRUE" : "FALSE") << "\n"; 

    return EXIT_SUCCESS;
}