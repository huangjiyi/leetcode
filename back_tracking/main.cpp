//
// Created by huangjiyi on 2022/10/23.
//
#include "utils.h"

class Solution {
  public:
    // 77. 组合
    vector<vector<int>> combine_res;
    vector<int> cur_combine;

    void _combine(int n, int k, int start_idx) {
        if (cur_combine.size() == k) {
            combine_res.push_back(cur_combine);
            return;
        }
        for (int i = start_idx; i < n + 2 - (k - cur_combine.size()); ++i) {
            cur_combine.push_back(i);
            _combine(n, k, i + 1);
            cur_combine.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        combine_res.clear();
        cur_combine.clear();
        _combine(n, k, 1);
        return combine_res;
    }

    // 216. 组合总和 III
    vector<vector<int>> res_216;
    vector<int> path_216;
    int sum_216;

    void _combinationSum3(int k, int n, int start_idx) {
        if (path_216.size() == k) {
            if (sum_216 == n) res_216.push_back(path_216);
            return;
        }
        for (int i = start_idx; i < 11 - (k - path_216.size()); ++i) {
            sum_216 += i;
            if (sum_216 > n) {
                sum_216 -= i;
                return;
            }
            path_216.push_back(i);
            _combinationSum3(k, n, i + 1);
            path_216.pop_back();
            sum_216 -= i;
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        res_216.clear();
        path_216.clear();
        sum_216 = 0;
        _combinationSum3(k, n, 1);
        return res_216;
    }

    // 17.电话号码的字母组合
    array<string, 8> digit_letters = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    vector<string> res_17;
    string path_17;

    void _letterCombinations(const string &digits, int idx) {
        if (idx == digits.length()) {
            res_17.push_back(path_17);
            return;
        }
        for (const char &letter: digit_letters[digits[idx] - '2']) {
            path_17.push_back(letter);
            _letterCombinations(digits, idx + 1);
            path_17.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        res_17.clear();
        path_17.clear();
        _letterCombinations(digits, 0);
        return res_17;
    }

    // 39. 组合总和
    // 关键：
    // candidates 中同一个数字可以无限制重复被选取
    // 2 <= candidates[i] <= 40
    vector<vector<int>> res_39;
    vector<int> path_39;
    int sum_39;

    void _combinationSum(vector<int> &candidates, int target, int start_idx) {
        if (sum_39 == target) {
            res_39.push_back(path_39);
            return;
        }
        for (int i = start_idx; i < candidates.size(); ++i) {
            sum_39 += candidates[i];
            if (sum_39 > target) {
                sum_39 -= candidates[i];
                return;
            }
            path_39.push_back(candidates[i]);
            _combinationSum(candidates, target, i);
            sum_39 -= candidates[i];
            path_39.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        res_39.clear();
        path_39.clear();
        sum_39 = 0;
        sort(candidates.begin(), candidates.end());
        _combinationSum(candidates, target, 0);
        return res_39;
    }

    // 40. 组合总和 II
    // 关键：每个数字在每个组合中只能使用一次
    vector<vector<int>> res_40;
    vector<int> path_40;
    int sum_40;

    void _combinationSum2(vector<int> &candidates, int target, int start_idx) {
        if (sum_40 == target) {
            res_40.push_back(path_40);
            return;
        }
        for (int i = start_idx; i < candidates.size(); ++i) {
            if (i > start_idx and candidates[i] == candidates[i - 1]) continue;
            sum_40 += candidates[i];
            if (sum_40 > target) {
                sum_40 -= candidates[i];
                return;
            }
            path_40.push_back(candidates[i]);
            _combinationSum2(candidates, target, i + 1);
            sum_40 -= candidates[i];
            path_40.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        res_40.clear();
        path_40.clear();
        sum_40 = 0;
        _combinationSum2(candidates, target, 0);
        return res_40;
    }

    // 131.分割回文串
    vector<vector<string>> res_131;
    vector<string> part_131;
    vector<vector<bool>> palindrome_matrix;

    bool isPalindrome(string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }

    // 预先计算所有可能的子串是不是回文串
    // 如果 s[a+1,b-1] 不是回文串，那么 s[a,b] 也不是回文串
    vector<vector<bool>> computePalindrome(string &s) {
        vector<vector<bool>> res;
        res.resize(s.length());
        for (int i = s.length() - 1; i >= 0; --i) {
            res[i].resize(s.length() - i);
            // 倒序计算，在计算 s[a,b] 时需要保证 s[a+1, b-1] 已经计算完成
            for (int j = i; j < s.length(); ++j) {
                if (j == i) res[i][j] = true;
                else if (j == i + 1) res[i][j] = (s[i] == s[j]);
                else res[i][j] = (s[i] == s[j] && res[i + 1][j - 1]);
            }
        }
        return res;
    }

    void _partition(string &s, int left) {
        if (left == s.length()) {
            res_131.push_back(part_131);
            return;
        }
        for (int right = s.length() - 1; right >= left; --right) {
//            if (isPalindrome(s, left, right)) {
            if (palindrome_matrix[left][right]) {
                part_131.push_back(s.substr(left, right - left + 1));
                _partition(s, right + 1);
                part_131.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        res_131.clear();
        part_131.clear();
        palindrome_matrix.clear();
        palindrome_matrix = computePalindrome(s);
        _partition(s, 0);
        return res_131;
    }

    // 93.复原IP地址
    vector<string> res_93;
    vector<string> path_93;

    void _restoreIpAddresses(string &s, int left) {
        if (s.length() - left < 4 - path_93.size() or s.length() - left > (4 - path_93.size()) * 3)
            return;
        if (path_93.size() == 4) {
            string ip;
            for (string &num: path_93)
                ip.append(num).append(".");
            ip.pop_back();
            res_93.push_back(ip);
            return;
        }
        for (int len = 1; len <= 3 && left + len <= s.length(); ++len) {
            if (len == 3 and stoi(s.substr(left, 3)) > 255)
                return;
            path_93.push_back(s.substr(left, len));
            _restoreIpAddresses(s, left + len);
            path_93.pop_back();
            if (s[left] == '0') return;
        }
    }

    vector<string> restoreIpAddresses(string s) {
        res_93.clear();
        path_93.clear();
        _restoreIpAddresses(s, 0);
        return res_93;
    }

    // 78. 子集
    vector<vector<int>> res_78;
    vector<int> path_78;

    void _subsets(vector<int> &nums, int start_idx) {
        for (int i = start_idx; i < nums.size(); ++i) {
            path_78.push_back(nums[i]);
            res_78.push_back(path_78);
            _subsets(nums, i + 1);
            path_78.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        res_78.clear();
        path_78.clear();
        res_78.push_back({});
        _subsets(nums, 0);
        return res_78;
    }

    // 90.子集II
    vector<vector<int>> res_90;
    vector<int> path_90;

    void _subsetsWithDup(vector<int> &nums, int start_idx) {
        for (int i = start_idx; i < nums.size(); ++i) {
            if (i > start_idx and nums[i] == nums[i - 1]) continue;
            path_90.push_back(nums[i]);
            res_90.push_back(path_90);
            _subsetsWithDup(nums, i + 1);
            path_90.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        res_90.clear();
        path_90.clear();
        res_90.push_back({});
        std::sort(nums.begin(), nums.end());
        _subsetsWithDup(nums, 0);
        return res_90;
    }

    // 491. 递增子序列
    vector<vector<int>> res_491;
    vector<int> path_491;

    void _findSubsequences(vector<int> &nums, int start) {
        if (path_491.size() > 1)
            res_491.push_back(path_491);
        array<bool, 201> appears = {false};
        for (int i = start; i < nums.size(); ++i) {
            if (appears[nums[i] + 100])
                continue;
            appears[nums[i] + 100] = true;
            if (!path_491.empty() and nums[i] < path_491.back())
                continue;
            path_491.push_back(nums[i]);
            _findSubsequences(nums, i + 1);
            path_491.pop_back();
        }
    }

    vector<vector<int>> findSubsequences(vector<int> &nums) {
        res_491.clear();
        path_491.clear();
        _findSubsequences(nums, 0);
        return res_491;
    }

    // 46.全排列
    vector<vector<int>> res_46;
    vector<int> path_46;

    void _permute(vector<int> &nums, vector<bool> &used) {
        if (path_46.size() == nums.size()) {
            res_46.push_back(path_46);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = true;
            path_46.push_back(nums[i]);
            _permute(nums, used);
            used[i] = false;
            path_46.pop_back();
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        res_46.clear();
        path_46.clear();
        vector<bool> used(nums.size(), false);
        _permute(nums, used);
        return res_46;
    }

    // 47. 全排列 II
    vector<vector<int>> res_47;
    vector<int> path_47;

    void _permuteUnique(vector<int> &nums, bool *used) {
        if (path_47.size() == nums.size()) {
            res_47.push_back(path_47);
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 and nums[i] == nums[i - 1] and !used[i - 1]) continue;
            used[i] = true;
            path_47.push_back(nums[i]);
            _permuteUnique(nums, used);
            used[i] = false;
            path_47.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums) {
        res_47.clear();
        path_47.clear();
        bool *used = new bool[nums.size()] {false};
        std::sort(nums.begin(), nums.end());
        _permuteUnique(nums, used);
        delete[] used;
        return res_47;
    }
};


int main() {
    return 1;
}