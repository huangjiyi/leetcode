//
// Created by huangjiyi on 2022/8/11.
//
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // 704. 二分查找
    // https://leetcode.cn/problems/binary-search/
    int search(vector<int> &nums, int target) {
        int left = 0, right = static_cast<int>(nums.size()) - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    // 35. 搜索插入位置
    // https://leetcode.cn/problems/search-insert-position/
    int searchInsert(vector<int> &nums, int target) {
        int left = 0, right = static_cast<int>(nums.size()) - 1, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }

    // 34. 在排序数组中查找元素的第一个和最后一个位置
    vector<int> searchRange(vector<int> &nums, int target) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return {-1, -1};
        int left = 0, right = n - 1, mid;
        // 寻找左边界
        while (left <= right) {
            mid = (left + right) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        // left == n 表示 target 大于最后一个元素
        // 如果寻找到的左边界上的元素不是 target, 则 target 不存在, 因此右边界也不用找了
        if (left == n or nums[left] != target) return {-1, -1};
        int left_border = left;
        // 寻找右边界
        // 因为已经找到了左边界, 所以右边界必定存在, 且必定在区间 [left_border, n - 1] 内
        right = n - 1;
        while (left <= right) {
            mid = (left + right) / 2;
            if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return {left_border, right};
    }

    // 69. x 的平方根
    int mySqrt(int x) {
        // 二分查找实现, 即寻找满足 t * t <= x 的最大数
        int left = 0, right = x, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (static_cast<long long>(mid) * mid > x)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return right;
    }

    // 牛顿法求平方根
    int mySqrt2(int x) {
        if (x == 0) return x;
        int x1 = x, x2;
        while (true) {
            x2 = (static_cast<long long>(x1) + x / x1) / 2;
            if (x1 - x2 <= 0)
                break;
            x1 = x2;
        }
        return x1;
    }
};

int main() {
    Solution solve;
    int x = 1;
    cout << solve.mySqrt2(x) << endl;
    return 1;
}