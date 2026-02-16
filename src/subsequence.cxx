#include <cstdlib>
#include <iostream>
#include <string>

bool isSubsequence(std::string s, std::string t) {
    size_t index{0};
    for (const auto& c : s) {
        auto pos = t.find(std::string{c}, index);
        if (t.npos == pos) {
            return false;
        }
        index = pos + 1;
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::string s1{"abc"}, t1{"ahbgdc"},
        s2{"axc"}, t2{"ahbgdc"};
    
    std::cout << s1 << " is sub-sequence of: " << t1 << " -> "
        << (isSubsequence(s1, t1) ? "TRUE" : "FALSE") << "\n";
    std::cout << s2 << " is sub-sequence of: " << t2 << " -> "
        << (isSubsequence(s2, t2) ? "TRUE" : "FALSE") << "\n";

    return EXIT_SUCCESS;
}