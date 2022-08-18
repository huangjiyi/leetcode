//
// Created by huangjiyi on 2022/8/12.
//
#include "utils.h"

class Solution {
  public:
    // 209. 长度最小的子数组
    int minSubArrayLen(int target, vector<int> &nums) {
        int sum = 0, len = 0, min_len = INT32_MAX;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            len++;
            while (sum >= target) {
                if (len < min_len) min_len = len;
                sum -= nums[left++];
                len--;
            }
        }
        if (min_len > nums.size()) return 0;
        return min_len;
    }

    // 904. 水果成篮
    // 即寻找最长的只包含2种元素的子数组
    int totalFruit(vector<int> &fruits) {
        int max_len = 0;
        int first = fruits[0], second;  // 记录2个篮子里的水果种类
        int first_end = 0, second_end;  // 记录每种水果最后出现的位置
        int left = 0, right = 1, len;
        while (right < fruits.size()) {
            if (fruits[right] != first) {
                second = fruits[right];
                second_end = right;
                break;
            }
            first_end = right++;
        }
        while (right < fruits.size()) {
            if (fruits[right] == first) {
                first_end = right;
            } else if (fruits[right] == second) {
                second_end = right;
            } else {
                // print(vector<int>({left, right, first, second, first_end, second_end}));
                len = right - left;
                if (len > max_len) max_len = len;
                // 更新左指针
                if (fruits[right - 1] == first) {
                    left = second_end + 1;
                } else {
                    left = first_end + 1;
                    first_end = second_end;
                }
                first = fruits[left];
                second = fruits[right];
                second_end = right;
            }
            right++;
        }
        len = right - left;
        if (len > max_len) max_len = len;
        // print(vector<int>({left, right, first, second, first_end, second_end}));
        return max_len;
    }

    // 76. 最小覆盖子串
    string minWindow(string s, string t) {
        unordered_map<char, int> dst_map, cur_map;
        for (const auto &ch: t)
            dst_map[ch]++;
        queue<int> appear_pos;
        int min_len = INT32_MAX, start = -1, valid = 0;
        for (int left = 0, right = 0; right < s.length(); ++right) {
            char ch = s[right];
            if (dst_map.count(ch)) {
                cur_map[ch]++;
                if (cur_map[ch] == dst_map[ch])
                    valid++;
                appear_pos.push(right);
            }
            if (valid == dst_map.size()) {
                left = appear_pos.front();
                appear_pos.pop();
                while (left <= right) {
                    ch = s[left];
                    cur_map[ch]--;
                    if (cur_map[ch] < dst_map[ch]) {
                        valid--;
                        int len = right - left + 1;
                        if (len < min_len) {
                            start = left;
                            min_len = len;
                        }
                        break;
                    }
                    left = appear_pos.front();
                    appear_pos.pop();
                }
            }
        }

        if (start == -1) return "";
        return s.substr(start, min_len);
    }
};

int main() {
    Solution solve;
    string s = "ADOBECODEBANC", t = "ABC";
    print(solve.minWindow(s, t));
    return 1;
}