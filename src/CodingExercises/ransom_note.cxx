#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

bool canConstruct(std::string ransomNote, std::string magazine) {
    std::unordered_map<unsigned char, size_t> noteHistogram, magazineHistogram;

    for (const auto& letter : ransomNote) {
        noteHistogram[letter]++;
    }

    for (const auto& letter : magazine) {
        magazineHistogram[letter]++;
    }
    
    for (const auto& el : noteHistogram) {
        if (!magazineHistogram.contains(el.first) || magazineHistogram[el.first] < el.second) {
            return false;
        }
    }

    return true;        
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    std::string ransomNote1{"a"}, magazine1{"b"},
    ransomNote2{"aa"}, magazine2{"ab"},
    ransomNote3{"aa"}, magazine3{"aab"};

    std::cout << magazine1 << " can construct: " << ransomNote1
        << " -> " << (canConstruct(ransomNote1, magazine1) ? "TRUE" : "FALSE") << "\n";
    std::cout << magazine2 << " can construct: " << ransomNote2
        << " -> " << (canConstruct(ransomNote2, magazine2) ? "TRUE" : "FALSE") << "\n";
    std::cout << magazine3 << " can construct: " << ransomNote3
        << " -> " << (canConstruct(ransomNote3, magazine3) ? "TRUE" : "FALSE") << "\n";

    return EXIT_SUCCESS;
}