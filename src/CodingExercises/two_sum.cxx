#include <array>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

std::array<int, 2> twoSum(const std::vector<int>& nums, const int& target) {
    std::unordered_map<int, int> numToIndex;

    for (size_t index{0}; index < nums.size(); ++index) {
        int complement = target - nums.at(index);

        if (numToIndex.find(complement) != numToIndex.end()) {
            return {numToIndex.at(complement), static_cast<int>(index)};
        }

        numToIndex[nums.at(index)] = static_cast<int>(index);
    }

    return {-1, -1}; // Return an invalid pair if no solution is found
}

int main(int argc, char* argv[]) {
    // Prevent compiler from complaining on unused variables
    (void) argc;
    (void) argv;

    const std::vector<int> nums1{2,7,11,15}, nums2{3,2,4}, nums3{3,3};
    constexpr int target1{9}, target2{6}, target3{6};

    auto result1 = twoSum(nums1, target1);
    std::cout << "Indices for target " << target1 << ": ["
        << result1[0] << ", " << result1[1] << "]\n";

    auto result2 = twoSum(nums2, target2);
    std::cout << "Indices for target " << target2 << ": ["
        << result2[0] << ", " << result2[1] << "]\n";

    auto result3 = twoSum(nums3, target3);
    std::cout << "Indices for target " << target3 << ": ["
        << result3[0] << ", " << result3[1] << "]\n";

    return EXIT_SUCCESS;
}

// End of file `two_sum.cxx'
