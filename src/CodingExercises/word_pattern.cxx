// Given a pattern and a string s, find if s follows the same pattern.
// 
// Here follow means a full match, such that there is a bijection between a
// letter in pattern and a non-empty word in s. Specifically:
// - Each letter in pattern maps to exactly one unique word in s.
// - Each unique word in s maps to exactly one letter in pattern.
// - No two letters map to the same word, and no two words map to the same
//   letter.
//  
// 
// Example 1:
// 
// Input: pattern = "abba", s = "dog cat cat dog"
// 
// Output: true
// 
// Explanation:
// 
// The bijection can be established as:
// 
// 'a' maps to "dog".
// 'b' maps to "cat".
// 
// 
// Example 2:
// 
// Input: pattern = "abba", s = "dog cat cat fish"
// 
// Output: false
// 
// 
// Example 3:
// 
// Input: pattern = "aaaa", s = "dog cat cat dog"
// 
// Output: false
//  
// 
// Constraints:
// - 1 <= pattern.length <= 300
// - pattern contains only lower-case English letters.
// - 1 <= s.length <= 3000
// - s contains only lowercase English letters and spaces ' '.
// - s does not contain any leading or trailing spaces.
// - All the words in s are separated by a single space.

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

bool wordPattern(std::string pattern, std::string s) {
    std::unordered_map<std::string, size_t> sMap;

    auto word_begining = s.begin();
    size_t index{0};

    for (auto it = s.begin(); s.end() != it; it++) {
        if (' ' == *it) {
            std::string word = s.substr(
                word_begining - s.cbegin(),
                it - word_begining
            );
            
            if (!sMap.contains(word)) {
                sMap[word] = index;
                index++;
            }

            word_begining = it + 1;
        }
    }
    // Don't forget the last word
    std::string word = s.substr(
        word_begining - s.cbegin(),
        s.cend() - word_begining
    );     
    if (!sMap.contains(word)) {
        sMap[word] = index;
    }

    index = 0;
    std::unordered_map<unsigned char, size_t> patternMap;
    for (const auto& letter : pattern) {
        if(!patternMap.contains(letter)) {
            patternMap[letter] = index;
            index++;
        }
    }

    std::vector<size_t> sPat, pPat;
    sPat.reserve(sMap.size());
    pPat.reserve(pattern.length());

    word_begining = s.begin();
    for (auto it = s.begin(); s.end() != it; it++) {
        if (' ' == *it) {
            std::string word = s.substr(
                word_begining - s.cbegin(),
                it - word_begining
            );
            sPat.push_back(sMap.at(word));
            word_begining = it + 1;
        }
    }
    // Don't forget the last word
    word = s.substr(word_begining - s.cbegin(), s.cend() - word_begining);     
    sPat.push_back(sMap.at(word));

    for (const auto& letter : pattern) {
        pPat.push_back(patternMap[letter]);
    }

    return sPat == pPat;                
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    std::string pattern1{"abba"}, s1{"dog cat cat dog"},
        pattern2{"abba"}, s2{"dog cat cat fish"},
         pattern3{"aaaa"}, s3{"dog cat cat dog"};

    std::cout << s1 << " follows pattern: " << pattern1
        << " -> " << (wordPattern(pattern1, s1) ? "TRUE" : "FALSE") << "\n";
    std::cout << s2 << " follows pattern: " << pattern2
        << " -> " <<  (wordPattern(pattern2, s2) ? "TRUE" : "FALSE") << "\n";
    std::cout << s3 << " follows pattern: " << pattern3
        << " -> " <<  (wordPattern(pattern3, s3) ? "TRUE" : "FALSE") << "\n";
    
    return EXIT_SUCCESS;
}