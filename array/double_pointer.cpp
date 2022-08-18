//
// Created by huangjiyi on 2022/8/12.
//
#include "utils.h"

class Solution {
  public:
    // 27. 移除元素 (暴力搜索)
    // int removeElement(vector<int>& nums, int val) {
    //     int len = static_cast<int>(nums.size());
    //     for (int i = len - 1; i >= 0 ; --i)
    //         if (nums[i] == val) {
    //             --len;
    //             for (int j = i; j < len; ++j)
    //                 nums[j] = nums[j + 1];
    //         }
    //     return len;
    // }

    // 27. 移除元素 (双指针)
    // https://leetcode.cn/problems/remove-element/
    int removeElement(vector<int> &nums, int val) {
        // 快指针指向值不为val的元素的下标
        // 慢指针指向当前快指针所指元素在新数组的下标
        // 用快指针遍历数组，如果遇到值为val的元素，快指针右移一位然后跳过，
        // 否则将快指针指向元素的值赋给慢指针指向元素，然后快慢指针均右移一位
        int slow = 0;
        for (int fast = 0; fast < static_cast<int>(nums.size()); ++fast)
            if (nums[fast] != val)
                nums[slow++] = nums[fast];
        return slow;
    }

    // 26. 删除有序数组中的重复项 (双指针法)
    int removeDuplicates(vector<int> &nums) {
        int slow = 1;
        for (int fast = 1; fast < static_cast<int>(nums.size()); ++fast)
            if (nums[fast] != nums[fast - 1])
                nums[slow++] = nums[fast];
        return slow;
    }

    // 283. 移动零 (双指针法)
    // https://leetcode.cn/problems/move-zeroes/
    void moveZeroes(vector<int> &nums) {
        int slow = 0, n = static_cast<int>(nums.size());
        for (int fast = 0; fast < n; ++fast)
            if (nums[fast] != 0)
                nums[slow++] = nums[fast];
        while (slow < n)
            nums[slow++] = 0;
    }

    // 844. 比较含退格的字符串 (双指针法)
    bool backspaceCompare(string s, string t) {
        int slow_s = 0, n = static_cast<int>(s.length());
        for (int fast = 0; fast < n; ++fast)
            if (s[fast] == '#') {
                if (slow_s > 0) slow_s--;
            } else
                s[slow_s++] = s[fast];
        n = static_cast<int>(t.length());
        int slow_t = 0;
        for (int fast = 0; fast < n; ++fast) {
            if (t[fast] == '#') {
                if (slow_t > 0) slow_t--;
            } else
                t[slow_t++] = t[fast];
        }
        if (slow_s != slow_t) return false;
        for (int i = 0; i < slow_s; ++i)
            if (s[i] != t[i])
                return false;
        return true;
    }

    // 977. 有序数组的平方
    vector<int> sortedSquares(vector<int> &nums) {
        // 双指针法
        // 从数组的两边开始遍历, 每次存入更大的平方和到目标数组
        vector<int> res(nums.size());
        int left = 0, right = static_cast<int>(nums.size()) - 1, cur = right;
        int left_square = nums[left] * nums[left];
        int right_square = nums[right] * nums[right];
        while (left < right) {
            if (left_square < right_square) {
                res[cur--] = right_square;
                right--;
                right_square = nums[right] * nums[right];
            } else{
                res[cur--] = left_square;
                left++;
                left_square = nums[left] * nums[left];
            }
        }
        res[cur--] = left_square;
        return res;
    }
};

int main() {
    Solution solve;
    vector<int> nums = {-7, -3, 2, 3, 11};
    print(solve.sortedSquares(nums));
    return 1;
}