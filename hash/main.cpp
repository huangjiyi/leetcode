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
        vector<int> appears(26);
        for (const auto &ch: magazine) {
            appears[ch - 'a']++;
        }
        for (const auto &ch: ransomNote) {
            if (appears[ch - 'a'])
                appears[ch - 'a']--;
            else
                return false;
        }
        return all_of(appears.begin(), appears.end(),
                      [](int p) { return p >= 0; });
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
};

int main() {
    Solution solve;
    string s = "cbaebabacd", p = "abc";
    print(solve.findAnagrams(s, p));
    return 0;
}
