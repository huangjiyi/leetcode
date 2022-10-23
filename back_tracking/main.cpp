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
        for (int i = start_idx; i < n + 1; ++i) {
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
};


int main() {
    return 1;
}