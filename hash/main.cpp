//
// Created by huangjiyi on 2022/10/9.
//
#include "utils.h"


class Solution {
  public:
    // 242. 有效的字母异位词
    bool isAnagram(string s, string t) {
        vector<int> appears(26);
        for (const auto &ch: s) {
            appears[ch - 'a']++;
        }
        for (const auto &ch: t) {
            if (appears[ch - 'a'])
                appears[ch - 'a']--;
            else
                return false;
        }
        return all_of(appears.begin(), appears.end(),
                      [](int appear) { return appear == 0; });
    }

    // 383. 赎金信
    bool canConstruct(string ransomNote, string magazine) {
        array<int, 26> appears{};
        for (const auto &ch: magazine)
            appears[ch - 'a']++;
        for (const auto &ch: ransomNote) {
            if (appears[ch - 'a'])
                appears[ch - 'a']--;
            else
                return false;
        }
        return true;
    }


    // 49. 字母异位词分组
    // https://leetcode.cn/problems/group-anagrams/
    // 思路: 互为字母异位词的两个字符串包含的字母相同，可以建立一个哈希表的映射，
    // key为字符串每个字母出现的次数（用一个数组表示）, value则是key对应的字符串数组
    // 每个字母出现的次数可以用 array<int, 26> 表示, 该哈希表需要自行实现哈希函数
    struct array_hash {
        size_t operator()(const array<int, 26> &key) const {
            static std::hash<int> int_hash;
            return accumulate(key.begin(), key.end(), 0u,
                              [](size_t sum, int num) {
                                  return (sum << 1) ^ int_hash(num);
                              });
        }
    };

    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<array<int, 26>, vector<string>, array_hash> res_table;
        for (string &str: strs) {
            array<int, 26> appear{};
            for (const char &ch: str)
                appear[ch - 'a']++;
            res_table[appear].push_back(std::move(str));
        }

        vector<vector<string>> res;
        for (auto &iter: res_table)
            res.push_back(std::move(iter.second));

        return res;
    }

    // 438. 找到字符串中所有字母异位词
    // https://leetcode.cn/problems/find-all-anagrams-in-a-string/solution/
    // 思路: 滑动窗口 + 各字母出现次数差值数组是否全为0
    vector<int> findAnagrams(string s, string p) {
        if (s.length() < p.length()) return {};
        vector<int> res{};
        array<int, 26> appear{};
        for (char &ch: p)
            appear[ch - 'a']++;
        for (int i = 0; i < p.length(); ++i)
            appear[s[i] - 'a']--;
        if (all_of(appear.begin(), appear.end(), [](const int &num) { return num == 0; }))
            res.push_back(0);
        for (int i = 0; i < s.length() - p.length(); ++i) {
            appear[s[i] - 'a']++;
            appear[s[i + p.length()] - 'a']--;
            if (all_of(appear.begin(), appear.end(), [](const int &num) { return num == 0; }))
                res.push_back(i + 1);
        }
        return res;
    }

    // 349. 两个数组的交集
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> nums1_set(nums1.begin(), nums1.end());
        vector<int> res{};
        for (const int &num: nums2) {
            if (nums1_set.count(num)) {
                res.push_back(num);
                nums1_set.erase(num);
            }
        }
        return res;
    }

    // 350. 两个数组的交集 II
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
        unordered_map<int, int> nums1_appears;
        for (const int &num: nums1) {
            nums1_appears[num]++;
        }
        vector<int> res{};
        for (const int &num: nums2) {
            if (nums1_appears.count(num)) {
                res.push_back(num);
                nums1_appears[num]--;
                if (nums1_appears[num] == 0)
                    nums1_appears.erase(num);
            }
        }
        return res;
    }

    // 202. 快乐数
    int nextNum(int n) {
        int res = 0;
        while (n) {
            res += pow(n % 10, 2);
            n /= 10;
        }
        return res;
    }

    bool isHappy(int n) {
        unordered_set<int> nums;
        while (not nums.count(n)) {
            nums.insert(n);
            n = nextNum(n);
            if (n == 1)
                return true;
        }
        return false;
    }

    // 1. 两数之和
    // 思路: 将数组中的数 num（key）及其索引（value）一个个插入哈希表中
    // 每次插入 num 前判断 target - num 是否出现在哈希表中
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> num_index;
        for (int i = 0; i < nums.size(); ++i) {
            if (num_index.count(target - nums[i]))
                return {num_index[target - nums[i]], i};
            num_index[nums[i]] = i;
        }
        return {};
    }

    // 454. 四数相加 II
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4) {
        unordered_map<int, int> sums;
        for (const int &num1: nums1) {
            for (const int &num2: nums2)
                sums[num1 + num2]++;
        }
        int res = 0;
        for (const int &num3: nums3) {
            for (const int &num4: nums4) {
                auto iter = sums.find(-(num3 + num4));
                if (iter != sums.end())
                    res += iter->second;
            }
        }
        return res;
    }
};

int main() {
    Solution solve;
    string s = "cbaebabacd", p = "abc";
    print(solve.findAnagrams(s, p));
    return 0;
}
