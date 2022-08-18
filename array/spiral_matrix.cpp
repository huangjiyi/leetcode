//
// Created by huangjiyi on 2022/8/13.
//
#include "utils.h"

class Solution {
  public:
    // 59. 螺旋矩阵 II
    // vector<vector<int>> generateMatrix(int n) {
    //     vector<vector<int>> result(n, vector<int>(n, 0));
    //     // 记录当前的移动方向, 0: 向右、1: 向下、2: 向左、3: 向上
    //     // 如果按照当前方向继续前进的话会跳出边界或者遇到非0元素，则更新方向: direction = (direction + 1) % 4
    //     // 如果在同一个位置进行了连续2次转向则表示到头了
    //     int direction = 0, turn = 0;
    //     int i = 0, j = 0, num = 1;
    //     while (true) {
    //         if (result[i][j] == 0) {
    //             result[i][j] = num++;
    //             turn = 0;
    //         } else {
    //             turn++;
    //             if (turn > 1) break;
    //         }
    //         switch (direction) {
    //             case 0:
    //                 j++;
    //                 if (j == n or result[i][j] != 0) {
    //                     j--;
    //                     direction = (direction + 1) % 4;
    //                 }
    //                 break;
    //             case 1:
    //                 i++;
    //                 if (i == n or result[i][j] != 0) {
    //                     i--;
    //                     direction = (direction + 1) % 4;
    //                 }
    //                 break;
    //             case 2:
    //                 j--;
    //                 if (j < 0 or result[i][j] != 0) {
    //                     j++;
    //                     direction = (direction + 1) % 4;
    //                 }
    //                 break;
    //             case 3:
    //                 i--;
    //                 if (i < 0 or result[i][j] != 0) {
    //                     i++;
    //                     direction = (direction + 1) % 4;
    //                 }
    //                 break;
    //         }
    //     }
    //     return result;
    // }

    // 59. 螺旋矩阵 II
    vector<vector<int>> generateMatrix(int n) {
        // 将二维矩阵分为若干个框, 每个框可以分为 4 条长度相等的线 (左闭右开)
        // 从最外层的框开始遍历, 直到遍历完 n / 2 个框
        // 如果 n 是奇数，则还需要为正中间的一个元素赋值
        vector<vector<int>> result(n, vector<int>(n, 0));
        int start = 0, end = n / 2, num = 1;
        while (start < end) {
            int i = start, j = start;
            for (; j < n - start - 1; ++j) result[i][j] = num++;
            for (; i < n - start - 1; ++i) result[i][j] = num++;
            for (; j > start; --j) result[i][j] = num++;
            for (; i > start; --i) result[i][j] = num++;
            start++;
        }
        if (n % 2) result[end][end] = num;
        return result;
    }

    // 54. 螺旋矩阵
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        vector<int> result;
        int m = matrix.size(), n = matrix[0].size();
        int start = 0, end = m < n ? m / 2 : n / 2;
        while (start < end) {
            int i = start, j = start;
            for (; j < n - start - 1; ++j) result.push_back(matrix[i][j]);
            for (; i < m - start - 1; ++i) result.push_back(matrix[i][j]);
            for (; j > start; --j) result.push_back(matrix[i][j]);
            for (; i > start; --i) result.push_back(matrix[i][j]);
            start++;
        }
        if (m < n and m % 2) {
            for (int j = end; j < n - end; ++j)
                result.push_back(matrix[end][j]);
        } else if (n % 2) {
            for (int i = end; i < m - end; ++i)
                result.push_back(matrix[i][end]);
        }
        return result;
    }
};

int main() {
    Solution solve;
    // vector<vector<int>> matrix = {{3}, {2}};
    print(solve.generateMatrix(3));
    // print(solve.spiralOrder(matrix));
    return 1;
}