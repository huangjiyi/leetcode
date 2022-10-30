//
// Created by huangjiyi on 2022/10/30.
//
#include "utils.h"

class Solution {
  public:
    // 509. 斐波那契数
    // 递推公式:
    // F(0) = 0，F(1) = 1
    // F(n) = F(n-1) + F(n-2)
    int fib(int n) {
        if (n < 2) return n;
        int first = 0, second = 1;
        for (int i = 2; i <= n; ++i) {
            int tmp = first;
            first = second;
            second += tmp;
        }
        return second;
    }

    // 70. 爬楼梯
    // 1. dp[i]: 爬 i 阶楼梯有多少种方法
    // 2. 递推: dp[i] = dp[i - 1] + dp [i - 2]
    // 3. 初始化: dp[0] = 1, dp[1] = 1
    int climbStairs(int n) {
        if (n < 2) return 1;
        int first = 1, second = 1;
        for (int i = 2; i < n + 1; ++i) {
            int tmp = first;
            first = second;
            second += tmp;
        }
        return second;
    }

    // 746. 使用最小花费爬楼梯
    // dp[i]: 爬到第 i 个楼梯需要的最小费用
    // 递推: dp[i] = min(dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1])
    // 初始化: dp[0] = 0, dp[1] = 0
    int minCostClimbingStairs(vector<int> &cost) {
        int n = cost.size();
        int first = 0, second = 0;
        for (int i = 2; i <= n; ++i) {
            int tmp = second;
            second = min(first + cost[i - 2], second + cost[i - 1]);
            first = tmp;
        }
        return second;
    }

    // 62. 不同路径
    // dp[i][j]: 走到坐标(i, j)有几条路径
    // dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
    // dp[0][j] = 1, dp[i][0] = 1;
    int uniquePaths(int m, int n) {
        int dp[m][n];
        for (int i = 0; i < m; ++i)
            dp[i][0] = 1;
        for (int j = 0; j < n; ++j)
            dp[0][j] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
        return dp[m - 1][n - 1];
    }

    // 63. 不同路径 II
    // 递推在 62 题上稍微改一下
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        vector<vector<int>> &dp = obstacleGrid;
        int m = dp.size(), n = dp[0].size();
        dp[0][0] = dp[0][0] ? 0 : 1;
        for (int i = 1; i < m; ++i) {
            if (dp[i - 1][0] and !dp[i][0]) dp[i][0] = 1;
            else dp[i][0] = 0;
        }
        for (int j = 1; j < n; ++j) {
            if (dp[0][j - 1] and !dp[0][j]) dp[0][j] = 1;
            else dp[0][j] = 0;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (!dp[i][j]) dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                else dp[i][j] = 0;
            }
        }
        return dp[m - 1][n - 1];
    }

    // 343. 整数拆分
    // dp[n]: 整数 n 分解的最大乘积
    // dp[n] = max(max(i * (n - i), i * dp[n - i]))
    // dp[2] = 1,
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int j = 2; j < i; ++j) {
                int product = max(j * (i - j), dp[j] * (i - j));
                if (product > dp[i]) dp[i] = product;
            }
        }
        return dp[n];
    }

    // 96.不同的二叉搜索树
    // dp[i]: i 个值互不相同结点的二叉搜索树的种数
    // dp[i] = sum_{j=0}^{i-1}{dp[j] * dp[i-1-j]}, j: 左子树结点数，i-j-1: 右子树结点数
    // dp[0] = 1, dp[1] = 1
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i < n + 1; ++i) {
            for (int j = 0; j < i / 2; ++j)
                dp[i] += dp[j] * dp[i - j - 1] * 2;
            if (i % 2)
                dp[i] += dp[i / 2] * dp[i / 2];
        }
        return dp[n];
    }

    // 01 背包
    // https://programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-1.html

};

int main() {
    Solution solve;
    vector<int> cost = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    solve.minCostClimbingStairs(cost);
    return 1;
}