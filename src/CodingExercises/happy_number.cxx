#include <cstdlib>
#include <iostream>
#include <unordered_set>

int getNext(int n) {
    int totalSum{0};

    while (n > 0) {
        int digit = n % 10;
        totalSum += digit * digit;
        n /= 10;
    }

    return totalSum;
}

bool isHappy(int n) {
    int slow{n}, fast{n};

    do {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
    } while (slow != fast);

    return slow == 1;
}

bool isHappy2(int n) {
    std::unordered_set<int> seen;

    while (n != 1 && seen.find(n) == seen.end()) {
        seen.insert(n);
        n = getNext(n);
    }

    return n == 1;
}

int main(int argc, char* argv[]) {
    // Prevent compiler from complaining on unused variables
    (void) argc;
    (void) argv;

    constexpr int test1{19}, test2{2}, test3{7};

    std::cout << "Is " << test1 << " a happy number? "
        << (isHappy(test1) ? "Yes" : "No") << "\n";
    std::cout << "Is " << test2 << " a happy number? "
        << (isHappy(test2) ? "Yes" : "No") << "\n";
    std::cout << "Is " << test3 << " a happy number? "
        << (isHappy(test3) ? "Yes" : "No") << "\n";

    std::cout << "Is " << test1 << " a happy number? "
        << (isHappy2(test1) ? "Yes" : "No") << "\n";
    std::cout << "Is " << test2 << " a happy number? "
        << (isHappy2(test2) ? "Yes" : "No") << "\n";
    std::cout << "Is " << test3 << " a happy number? "
        << (isHappy2(test3) ? "Yes" : "No") << "\n";

    return EXIT_SUCCESS;
}

// End of file `happy_number.cxx'
