/*
LeetCode 121. Best Time to Buy and Sell Stock
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Given a non-empty list of daily prices, find the maximum profit
from one purchase followed by one sale on a later day.
Return 0 if no profitable trade is possible.

Examples
[7, 1, 5, 3, 6, 4] -> 5  (buy at 1 and sell at 6)
[7, 6, 4, 3, 1]    -> 0  (prices only decrease)

Time complexity  O(n)
Space complexity O(1)
*/

#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        // The first day is our first possible purchase.
        int lowestPrice = prices.front();
        int bestProfit = 0;

        // Start on the second day so the purchase comes before the sale.
        for (std::size_t day = 1; day < prices.size(); ++day) {
            // Compare today's selling price with the cheapest earlier price.
            int profit = prices[day] - lowestPrice;
            bestProfit = std::max(bestProfit, profit);

            // Today's price can now be used for a future purchase.
            lowestPrice = std::min(lowestPrice, prices[day]);
        }

        return bestProfit;
    }
};
