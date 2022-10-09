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
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

    }
};

int main() {
    Solution solve;
    string ransomNote = "aa", magazine = "aab";
    print(solve.canConstruct(ransomNote, magazine));
    return 0;
}