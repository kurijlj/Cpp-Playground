#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

bool validParentheses(const std::string& s) {
    std::stack<unsigned char> parenthesesStack;
    std::unordered_map<unsigned char, unsigned char> parenthesesMap{
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    if (s.empty()) {
        return false;
    }

    for (const auto&c : s) {
        if (parenthesesMap.find(c) != parenthesesMap.end()) {
            if (
                parenthesesStack.empty() ||
                parenthesesStack.top() != parenthesesMap.at(c)
            ) {
                return false;
            } else if (!parenthesesStack.empty()) {
                parenthesesStack.pop();
            }

        } else {
            parenthesesStack.push(c);
        }
    }

    return parenthesesStack.empty();
}

int main(int argc, char* argv[]) {
    // Prevent compiler from complaining on unused variables
    (void) argc;
    (void) argv;

    std::string s1{"()"}, s2{"()[]{}"}, s3{"(]"}, s4{""};

    std::cout << "Input: s = \"()\"\nOutput: "
        << (validParentheses(s1) ? "true" : "false") << "\n";

    std::cout << "Input: s = \"()[]{}\"\nOutput: "
        << (validParentheses(s2) ? "true" : "false") << "\n";

    std::cout << "Input: s = \"(]\"\nOutput: "
        << (validParentheses(s3) ? "true" : "false") << "\n";

    std::cout << "Input: s = \"\"\nOutput: "
        << (validParentheses(s4) ? "true" : "false") << "\n";

    return 0;
}

// End of file `valid_parentheses.cxx'
