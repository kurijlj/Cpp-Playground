// Given two strings s and t, determine if they are isomorphic.
//
// Two strings s and t are isomorphic if the characters in s can be replaced to
// get t.
//
// All occurrences of a character must be replaced with another character while
// preserving the order of characters. No two characters may map to the same
// character, but a character may map to itself.
// 
//
// Example 1:
//
// Input: s = "egg", t = "add"
//
// Output: true
//
// Explanation:
//
// The strings s and t can be made identical by:
//
// Mapping 'e' to 'a'.
// Mapping 'g' to 'd'.
//
//
// Example 2:
//
// Input: s = "f11", t = "b23"
//
// Output: false
//
// Explanation:
//
// The strings s and t can not be made identical as '1' needs to be mapped to
// both '2' and '3'.
//
//
// Example 3:
//
// Input: s = "paper", t = "title"
//
// Output: true
//
// 
// Constraints:
// 
// 1 <= s.length <= 5 * 104
// t.length == s.length
// s and t consist of any valid ascii character.

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

bool isIsomorphic(std::string s, std::string t) {
    if (s.length() != t.length()) {
        return false;
    }

    std::unordered_map<unsigned char, size_t> sMap, tMap;
    size_t index{0};
    for (const auto& letter : s) {
        if (!sMap.contains(letter)) {
            sMap[letter] = index;
            index++;
        }
    }
    index = 0;
    for (const auto& letter : t) {
        if (!tMap.contains(letter)) {
            tMap[letter] = index;
            index++;
        }
    }

    std::vector<size_t> spat, tpat;
    spat.reserve(s.length());
    tpat.reserve(t.length());

    for (const auto& letter : s) {
        spat.push_back(sMap[letter]);
    }
    for (const auto& letter : t) {
        tpat.push_back(tMap[letter]);
    }

    return spat == tpat;        
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    std::string s1{"egg"}, t1{"add"},
        s2{"f11"}, t2{"b23"},
        s3{"paper"}, t3{"title"};
    
    std::cout << "Are " << s1 << " and " << t1 << " isomorphic: "
        << (isIsomorphic(s1, t1) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Are " << s2 << " and " << t2 << " isomorphic: "
        << (isIsomorphic(s2, t2) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Are " << s3 << " and " << t3 << " isomorphic: "
        << (isIsomorphic(s3, t3) ? "TRUE" : "FALSE") << "\n";

    return EXIT_SUCCESS;
}