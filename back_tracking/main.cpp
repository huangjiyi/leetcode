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

};


int main() {
    return 1;
}