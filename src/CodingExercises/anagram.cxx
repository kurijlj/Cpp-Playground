// Given two strings s and t, return true if t is an anagram of s, and false
// otherwise.
//  
// 
// Example 1:
// 
// Input: s = "anagram", t = "nagaram"
// 
// Output: true
// 
// 
// Example 2:
// 
// Input: s = "rat", t = "car"
// 
// Output: false
//  
// 
// Constraints:
// 
// 1 <= s.length, t.length <= 5 * 104
// s and t consist of lowercase English letters.
//  
// 
// Follow up: What if the inputs contain Unicode characters? How would you adapt
// your solution to such a case?

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

bool isAnagram(std::string s, std::string t) {
    std::unordered_map<unsigned char, size_t> smap, tmap;

    for (const auto& letter : s) {
        smap[letter]++;
    }
    for (const auto& letter : t) {
        tmap[letter]++;
    }

    return smap == tmap;
}

int main(int argc, char* argv[]) {
    std::string s1{"anagram"}, t1{"nagaram"},
        s2{"rat"}, t2{"car"};
    
    std::cout << "Are " << s1 << " and " << t1 << " anagrams: "
        << (isAnagram(s1, t1) ? "TRUE" : "FALSE") << "\n";
    std::cout << "Are " << s2 << " and " << t2 << " anagrams: "
        << (isAnagram(s2, t2) ? "TRUE" : "FALSE") << "\n";

    return EXIT_SUCCESS;
}