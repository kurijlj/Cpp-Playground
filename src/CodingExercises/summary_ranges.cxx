#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> summaryRanges(const std::vector<int>& nums) {
    std::vector<std::string> result;

    if (nums.empty()) {
        return result;
    }

    int start{nums.at(0)}, end{nums.at(0)};

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == end + 1) {
            end = nums[i];
        } else {
            if (start == end) {
                result.push_back(std::to_string(start));
            } else {
                result.push_back(std::to_string(start) + "->"
                    + std::to_string(end));
            }
            start = end = nums[i];
        }
    }

    // Handle the last range
    if (start == end) {
        result.push_back(std::to_string(start));
    } else {
        result.push_back(std::to_string(start) + "->" + std::to_string(end));
    }

    return result;
}

int main(int argc, char* argv[]) {
    // Prevent compiler from complaining on unused variables
    (void) argc;
    (void) argv;

    std::vector<int> nums1{0, 1, 2, 4, 5, 7},
        nums2{0, 2, 3, 4, 6, 8, 9},
        nums3{};

    std::cout << "Input: nums = [0, 1, 2, 4, 5, 7]\nOutput: [";
    for (const auto& range : summaryRanges(nums1)) {
        std::cout << range << ", ";
    }
    std::cout << "]\n";

    std::cout << "Input: nums = [0, 2, 3, 4, 6, 8, 9]\nOutput: [";
    for (const auto& range : summaryRanges(nums2)) {
        std::cout << range << ", ";
    }
    std::cout << "]\n";

    std::cout << "Input: nums = []\nOutput: [";
    for (const auto& range : summaryRanges(nums3)) {
        std::cout << range << ", ";
    }
    std::cout << "]\n\n";

    return EXIT_SUCCESS;
}

// End of file `summary_ranges.cxx'
