/*
Problem summary:
Given an integer array nums, create at least k non-overlapping
subarrays of exactly x consecutive elements, where all elements
within each subarray are equal. Different subarrays may use
different target values.

One operation increases or decreases one element by 1.
Return the minimum total number of operations needed.

Example:
nums = [5, -2, 1, 3, 7, 3, 6, 4, -1], x = 3, k = 2
Answer: 8 operations.

Approach:
1. Use a sliding window to calculate the minimum cost of making
   each subarray of length x equal to its median.
2. Use dynamic programming to choose k non-overlapping subarrays
   with the smallest total cost.

Choosing exactly k subarrays is sufficient: any valid solution
with more groups also contains k valid groups.

Time complexity: O(n * log(x) + n * k).
Space complexity: O(n).
*/

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        // cost[start] = minimum operations needed to make
        // nums[start ... start + x - 1] equal.
        vector<long long> cost(n - x + 1);

        // Split the current window into two sorted halves:
        // low contains the smaller numbers.
        // high contains the larger numbers.
        //
        // A multiset keeps elements sorted and allows duplicates.
        multiset<int> low, high;

        // Track each half's sum so we can calculate the cost
        // without visiting every element in the window.
        //
        // Use long long because total costs may exceed int's range.
        long long sumLow = 0, sumHigh = 0;

        // Keep both halves equally sized, or let low have
        // exactly one extra element.
        //
        // The largest element in low will then be a median.
        auto balance = [&]() {
            // Move the largest element from low to high
            // if low contains too many elements.
            while (low.size() > high.size() + 1) {
                auto it = prev(low.end());
                int value = *it;

                low.erase(it);
                sumLow -= value;

                high.insert(value);
                sumHigh += value;
            }

            // Move the smallest element from high to low
            // if high contains more elements than low.
            while (high.size() > low.size()) {
                auto it = high.begin();
                int value = *it;

                high.erase(it);
                sumHigh -= value;

                low.insert(value);
                sumLow += value;
            }
        };

        // PART 1: Calculate the cost of every window of length x.
        //
        // Slide the window one position at a time.
        // The original order of nums remains unchanged.
        for (int i = 0; i < n; ++i) {
            int value = nums[i];

            // Insert the incoming number into the appropriate half.
            // *low.rbegin() is the largest element in low.
            if (low.empty() || value <= *low.rbegin()) {
                low.insert(value);
                sumLow += value;
            } else {
                high.insert(value);
                sumHigh += value;
            }

            // Once the window exceeds x elements,
            // remove the number leaving its left side.
            if (i >= x) {
                int outgoing = nums[i - x];
                auto it = low.find(outgoing);

                if (it != low.end()) {
                    // Remove only one occurrence of the number.
                    low.erase(it);
                    sumLow -= outgoing;
                } else {
                    high.erase(high.find(outgoing));
                    sumHigh -= outgoing;
                }
            }

            // Restore the required size balance between the halves.
            balance();

            // Calculate a cost only when the window is full.
            if (i >= x - 1) {
                long long median = *low.rbegin();

                // Cost to increase the elements in low to the median:
                // median * number of elements - sum of elements.
                //
                // Cost to decrease the elements in high to the median:
                // sum of elements - median * number of elements.
                //
                // Their sum is the minimum cost for this window.
                cost[i - x + 1] =
                    median * static_cast<long long>(low.size())
                    - sumLow
                    + sumHigh
                    - median * static_cast<long long>(high.size());
            }
        }

        // PART 2: Choose k non-overlapping windows.
        //
        // Use dynamic programming to build the answer
        // from previously calculated smaller subproblems.

        // A large value representing an impossible state.
        const long long INF = LLONG_MAX / 4;

        // previous[i] = minimum cost of selecting the previous
        // number of groups using only the first i elements.
        //
        // Initially, selecting zero groups costs zero.
        vector<long long> previous(n + 1, 0);

        for (int groups = 1; groups <= k; ++groups) {
            // current[i] = minimum cost of selecting exactly
            // 'groups' groups using only the first i elements.
            vector<long long> current(n + 1, INF);

            // At least groups * x elements are needed.
            for (int i = groups * x; i <= n; ++i) {
                // Compare two options:
                //
                // 1. Skip the element at index i - 1.
                //    Keep the best answer for the first i - 1 elements.
                //
                // 2. Select the window nums[i - x ... i - 1].
                //    Add its cost to the best previous answer.
                //
                // That previous answer uses only the first i - x
                // elements, preventing any overlap with this window.
                current[i] = min(
                    current[i - 1],
                    previous[i - x] + cost[i - x]
                );
            }

            // Reuse these results when selecting one more group.
            previous.swap(current);
        }

        // Minimum cost of selecting k groups from the entire array.
        return previous[n];
    }
};
