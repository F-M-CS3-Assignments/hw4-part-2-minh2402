//Author: Duc Minh Pham
//Date: 2025-03-31
#include "bdc.h"
#include <algorithm>
#include <sstream>

// Converts a vector of integers to a string representation
std::string vec_to_string(const std::vector<int>& v) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << v[i];
    }
    oss << "]";
    return oss.str();
}

// Function to find the largest divisible subset using dynamic programming
std::vector<int> biggest_divisible_conglomerate(std::vector<int> input) {
    if (input.empty()) return {};

    // Sort the input to ensure the divisibility condition can be checked linearly
    std::sort(input.begin(), input.end());

    size_t n = input.size();
    std::vector<int> dp(n, 1);     // dp[i] will store the size of the largest subset ending with input[i]
    std::vector<int> prev(n, -1);  // prev[i] will store the index of the previous element in the subset
    int max_idx = 0;               // Index of the largest element in the maximum subset

    // Build the dp array and track the previous indices
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (input[i] % input[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = static_cast<int>(j);
            }
        }
        if (dp[i] > dp[max_idx]) {
            max_idx = static_cast<int>(i);
        }
    }

    // Reconstruct the largest divisible subset
    std::vector<int> largest_subset;
    for (int i = max_idx; i != -1; i = prev[i]) {
        largest_subset.push_back(input[i]);
    }

    // The subset is constructed in reverse order, so reverse it
    std::reverse(largest_subset.begin(), largest_subset.end());
    return largest_subset;
}
