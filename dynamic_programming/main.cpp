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
    // dp[i][j]: 坐标 0~i 的物品放入容量为 j 的背包产生的最大价值
    // if weights[i] > j:  // 物品 i 放不下背包，直接返回不放物品 i 的最大价值
    //     dp[i][j] = dp[i - 1][j]
    // else:  // 能放下，比较放与不放物品 i 的最大价值
    //     dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + value[i])
    // 遍历顺序: 行遍历
    // 初始化: dp[0][j] = weights[0] > j ? 0 : value[0];
    int zeroOneBage(vector<int> &weights, vector<int> &value, int capacity) {
        vector<vector<int>> dp(weights.size(), vector<int>(capacity + 1, 0));
        for (int j = 0; j <= capacity; ++j)
            dp[0][j] = weights[0] > j ? 0 : value[0];
        for (int i = 1; i < weights.size(); ++i) {
            for (int j = 1; j <= capacity; ++j) {
                if (weights[i] > j)
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + value[i]);
            }
        }
        return dp.back().back();
    }

    // 为 dp[i][j] 只与 dp[i-1][0~j] 有关
    // 因此没必要使用二维矩阵，可以使用一个一维滚动数组
    // 对于每一个 i，从数组末尾开始向前更新
    // if weights[i] <= j:
    //     dp[j] = max(dp[j], dp[j - weights[i]] + value[i])
    int zeroOneBage2(vector<int> &weights, vector<int> &value, int capacity) {
        vector<int> dp(capacity + 1, 0);
        // 初始化
        for (int j = 1; j < capacity; ++j)
            dp[j] = weights[0] > j ? 0 : value[0];

        for (int i = 0; i < weights.size(); ++i) {
            for (int j = capacity; j > 0; --j) {
                if (weights[i] <= j)
                    dp[j] = max(dp[j], dp[j - weights[i]] + value[i]);
            }
        }
        print(dp);
        return dp.back();
    }

    // 416. 分割等和子集
    // 思路: 找到元素和为 sum / 2 的子集
    // 试一下回溯
    // 结果：只能通过 37/140
    int sum_416;

    bool _canPartition(vector<int> &nums, int start_idx, int &target) {
        if (sum_416 == target) return true;
        for (int i = start_idx; i < nums.size(); ++i) {
            if (i > start_idx and nums[i] == nums[i - 1]) continue;
            sum_416 += nums[i];
            if (_canPartition(nums, i + 1, target)) return true;
            sum_416 -= nums[i];
        }
        return false;
    }

    bool canPartition2(vector<int> &nums) {
        std::sort(nums.begin(), nums.end());
        int target = std::accumulate(nums.begin(), nums.end(), 0);
        if (target % 2) return false;
        target /= 2;
        sum_416 = 0;
        return _canPartition(nums, 0, target);
    }

    // 使用背包问题求解
    // 背包容量为 sum / 2, 数组中每个数是一个物品，其重量和价值都是其数值
    bool canPartition(vector<int> &nums) {
        int target = std::accumulate(nums.begin(), nums.end(), 0);
        if (target % 2) return false;
        target /= 2;
        vector<int> dp(target + 1, 0);
        for (int j = 1; j <= target; ++j) {
            if (nums[0] <= j) dp[j] = nums[0];
        }
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = target; j > 0; --j) {
                if (nums[i] <= j) {
                    dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
                    if (dp[j] == target)
                        return true;
                }
            }
        }
        return false;
    }

    // 1049. 最后一块石头的重量 II
    // 相当于将石头分成重量之和尽可能相等的两堆，最后一块石头的重量就是两堆石头的重量差
    // 转化为背包问题:
    // 计算所有石头的重量之和 sum, 将背包的重量设为 sum / 2,
    // 最后一块石头的重量就是 sum - 2 * dp[sum / 2]
    int lastStoneWeightII(vector<int> &stones) {
        int sum = std::accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        vector<int> dp(target + 1);
        for (int j = 1; j <= target; ++j) {
            dp[j] = stones[0] > j ? 0 : stones[0];
        }
        for (int i = 0; i < stones.size(); ++i) {
            for (int j = target; j >= stones[i]; --j) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - 2 * dp[target];
    }

    // 494. 目标和
    // 可以把数分为两个子集，一组前面加正号pos，一组前面加负号neg
    // 计算所有数的总和 sum，目前和为 target
    // 则 pos_sum - neg_sum = pos_sum - (sum - pos_sum) = 2*pos_sum - sum = target
    // >> pos_sum = (sum + target) / 2 (如果 sum + target 是奇数则不存在，返回 0，过了 26 / 139个)
    // 知道了 pos_sum 的目标，然后用背包问题求解
    int findTargetSumWays(vector<int> &nums, int target) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int pos_sum = sum + target;
        if (pos_sum % 2) return 0;
        pos_sum /= 2;
        int res = 0;
        vector<int> dp(pos_sum + 1, 0);
        for (int j = 1; j <= pos_sum; ++j) {
            dp[j] = nums[0] > j ? 0 : nums[0];
        }
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = pos_sum; j >= nums[i]; --j) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
            if (dp[pos_sum] == pos_sum) res++;
        }
        return res;
    }
};

int main() {
    Solution solve;
    vector<int> nums = {1, 1, 1, 1, 1};
    print(solve.findTargetSumWays(nums, 3));
    return 1;
}