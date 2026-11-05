/*
Problem: 1. Two Sum

Given an integer array nums and an integer target, return the
indices of two numbers whose sum equals target.

Exactly one valid answer exists.
The same element cannot be used twice.
The indices may be returned in any order.

Examples:
nums = [2, 7, 11, 15], target = 9 -> [0, 1]
nums = [3, 2, 4],      target = 6 -> [1, 2]
nums = [3, 3],         target = 6 -> [0, 1]

Approach:
Use a hash map to remember previously visited numbers and their indices.

For each number:
1. Calculate the number needed to reach the target.
2. Check whether that number is already in the map.
3. If found, return its index and the current index.
4. Otherwise, store the current number and its index.

Time complexity: O(n) on average.
Space complexity: O(n).
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Key: a previously visited number.
        // Value: the index where that number appeared.
        unordered_map<int, int> seen;

        // Visit each element from left to right.
        for (int i = 0; i < nums.size(); ++i) {
            // Calculate the partner needed to reach the target.
            // Example: target = 9, nums[i] = 2 -> needed = 7.
            int needed = target - nums[i];

            // Search for the partner among previously visited numbers.
            // 'it' is an iterator pointing to the matching entry,
            // or seen.end() if the number was not found.
            auto it = seen.find(needed);

            if (it != seen.end()) {
                // A map entry contains:
                // it->first  = the stored number.
                // it->second = that number's index.
                //
                // Return the partner's index and the current index.
                return {it->second, i};
            }

            // Store the current number AFTER searching.
            // This prevents pairing an element with itself.
            //
            // For [3, 3] with target = 6:
            // The first 3 is stored at index 0.
            // The second 3 finds it and returns [0, 1].
            seen[nums[i]] = i;
        }

        // The problem guarantees a valid answer.
        // This fallback returns an empty vector if none is found.
        return {};
    }
};
