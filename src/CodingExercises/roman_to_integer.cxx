#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

int romanToInt(std::string s) {
    std::unordered_map<char, int> r2i {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    char prev{s.at(0)};
    int result{r2i.at(prev)};
    for (auto it = s.cbegin() + 1; s.cend() != it; it++) {
        if (r2i.at(prev) < r2i.at(*it)) {
            result += r2i.at(*it) - 2*r2i.at(prev);
        } else {
            result += r2i.at(*it);
        }

        prev = *it;
    }

    return result;
};

int main(int argc, char* argv[]) {
    std::string s1{"III"}, s2{"LVIII"}, s3{"MCMXCIV"};

    std::cout << s1 << " -> " << romanToInt(s1) << "\n";
    std::cout << s2 << " -> " << romanToInt(s2) << "\n";
    std::cout << s3 << " -> " << romanToInt(s3) << "\n";

    return EXIT_SUCCESS;
}

// End of file `roman_to_integer.cxx'
