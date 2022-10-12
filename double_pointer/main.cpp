//
// Created by huangjiyi on 2022/8/21.
//
#include "utils.h"

class Solution {
  public:
    // 15. 三数之和
    // https://leetcode.cn/problems/3sum/
    // 思路: 先对数组进行排序，然后分别考虑以每一个元素为第一项的三元组（一层循环）
    // 当考虑第 i 个元素时，设置左右两个指针，分别指向第 i + 1 个元素和最后一个元素
    // 计算 3 个元素的和，如果大于 0 则左移右指针，小于 0 则右值左指针
    // 等于 0 则保存该三元组，然后将左(右)指针右(左)移至第一个遇到的不同元素
    // 重复上述过程直到左右指针相遇
    // 注意排除第一项相同导致重复的三元组
    vector<vector<int>> threeSum(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res{};
        for (int i = 0; i < nums.size() - 2; ++i) {
            // 当第一项大于 0 时，则不可能构成三元组
            if (nums[i] > 0)
                return res;
            // 排除重复项
            if (i > 0 and nums[i] == nums[i - 1])
                continue;
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0) {
                    left++;
                } else if (sum > 0) {
                    right--;
                } else {
                    res.push_back({nums[i], nums[left], nums[right]});
                    while (left < right and nums[left + 1] == nums[left])
                        ++left;
                    while (left < right and nums[right - 1] == nums[right])
                        --right;
                    ++left;
                    --right;
                }
            }
        }
        return res;
    }

    // 18. 四数之和
    // https://leetcode.cn/problems/4sum/
    // 思路: 在三数之和的基础上加一层循环，然后每个内循环求的三数之和是 target - num[i]
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if (nums.size() < 4)
            return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for (int i = 0; i < nums.size() - 3; ++i) {
            if (nums[i] > 0 and nums[i] > target)
                return res;
            if (i > 0 and nums[i] == nums[i - 1])
                continue;
            int target3sum = target - nums[i];
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                if (nums[j] > 0 and nums[j] > target3sum)
                    break;
                if (j > i + 1 and nums[j] == nums[j - 1])
                    continue;
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    long sum = (long)nums[j] + (long)nums[left] + (long)nums[right];
                    if (sum < (long)target3sum) {
                        ++left;
                    } else if (sum > (long)target3sum) {
                        --right;
                    } else {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right and nums[left + 1] == nums[left])
                            ++left;
                        while (left < right and nums[right - 1] == nums[right])
                            --right;
                        ++left;
                        --right;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    Solution solve;
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    print(solve.fourSum(nums, target));
    return 1;
}