//
// Created by huangjiyi on 2022/10/28.
//
#include "utils.h"

class Solution {
  public:
    // 455. 分发饼干
    // 两种思路: 优先把小尺寸的饼干分给小胃口的孩子，或者优先把大尺寸的饼干分给大胃口的孩子
    int findContentChildren(vector<int> &g, vector<int> &s) {
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());
        // 从最小的开始遍历
        int res = 0;
        for (int i = 0, j = 0; i < g.size() and j < s.size(); j++) {
            if (g[i] <= s[j]) {
                i++;
                res++;
            }
        }
        return res;
    }

    // 376. 摆动序列
    int wiggleMaxLength(vector<int> &nums) {
        if (nums.size() < 2) return nums.size();
        int length = 1;
        // 找第一个峰值点核谷值点
        bool last_positive;
        int i = 0;
        for (; i < nums.size() - 1; ++i) {
            if (nums[i + 1] != nums[i]) {
                last_positive = nums[i + 1] > nums[i];
                length++;
                break;
            }
        }
        // 删除单调坡上的结点
        for (; i < nums.size() - 1; ++i) {
            if ((nums[i + 1] < nums[i] and last_positive) or
                (nums[i + 1] > nums[i] and !last_positive)) {
                length++;
                last_positive = !last_positive;
            }
        }
        return length;
    }

    // 53. 最大子序和
    int maxSubArray(vector<int> &nums) {
        int max_sum = INT32_MIN;
        int sum = 0;
        for (int &num: nums) {
            sum += num;
            if (sum > max_sum) max_sum = sum;
            if (sum < 0) sum = 0;
        }
        return max_sum;
    }

    // 122.买卖股票的最佳时机II
    int maxProfit(vector<int> &prices) {
        if (prices.size() <= 1) return 0;
        int sum = 0;
        for (int i = 1; i < prices.size(); ++i)
            if (prices[i] > prices[i - 1])
                sum += prices[i] - prices[i - 1];
        return sum;
    }

    // 55. 跳跃游戏
    // 维护一个 far 变量, far 以内的坐标都可以到达
    bool canJump(vector<int> &nums) {
        int far = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i]) {
                far = max(far, i + nums[i]);
                if (far >= nums.size() - 1) return true;
            } else if (far <= i) {
                return false;
            }
        }
        return true;
    }

    // 45. 跳跃游戏 II
    int jump(vector<int> &nums) {
        if (nums.size() == 1) return 0;
        int far = nums[0];
        if (far >= nums.size() - 1) return 1;
        int count = 0;
        for (int i = 0; i < nums.size() - 1;) {
            count++;
            // 遍历每一步可以到达范围内的坐标，找到下一步的最大范围
            for (int save = far; i <= save; ++i) {
                far = max(far, i + nums[i]);
                if (far >= nums.size() - 1) return ++count;
            }
        }
        return count;
    }

    // 1005. K 次取反后最大化的数组和
    int largestSumAfterKNegations(vector<int> &nums, int k) {
        std::sort(nums.begin(), nums.end(), [](int &a, int &b) { return abs(a) > abs(b); });
        int sum = 0;
        int i = 0;
        for (; i < nums.size(); ++i) {
            if (nums[i] < 0 and k > 0) {
                nums[i] = -nums[i];
                k--;
            }
            sum += nums[i];
        }
        if (k % 2) {
            sum -= 2 * nums.back();
            return sum;
        }
        for (; i < nums.size(); ++i)
            sum += nums[i];
        return sum;
    }

    // 134. 加油站
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int left = 0, start = 0, total_diff = 0;
        for (int i = 0; i < gas.size(); ++i) {
            int diff = gas[i] - cost[i];
            left += diff;
            total_diff += diff;
            if (left < 0) {
                start = i + 1;
                left = 0;
            }
        }
        if (total_diff < 0) return -1;
        if (start < gas.size()) return start;
        return -1;
    }

    // 135. 分发糖果
    // 两个方向分别遍历一次
    int candy(vector<int> &ratings) {
        vector<int> candys(ratings.size());
        candys[0] = 1;
        for (int i = 1; i < ratings.size(); ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candys[i] = candys[i - 1] + 1;
            } else {
                candys[i] = 1;
            }
        }
        for (int i = ratings.size() - 1; i > 0; --i) {
            if (ratings[i] < ratings[i - 1])
                candys[i - 1] = max(candys[i - 1], candys[i] + 1);
        }
        return accumulate(candys.begin(), candys.end(), 0);
    }

    // 860.柠檬水找零
    bool lemonadeChange(vector<int> &bills) {
        int five = 0, ten = 0;
        for (auto &bill: bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                five--;
                ten++;
            } else {
                if (ten) {
                    ten--;
                    five--;
                } else {
                    five -= 3;
                }
            }
            if (five < 0) return false;
        }
        return true;
    }

    // 406.根据身高重建队列
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
        auto compare = [](vector<int> &p1, vector<int> &p2) {
            return p1[0] > p2[0] or p1[0] == p2[0] and p1[1] > p2[1];
        };
        sort(people.begin(), people.end(), compare);
        for (int i = 0; i < people.size(); ++i) {
            if (i == people[i][1]) continue;
            // 这里的插入算法用链表实现更快
            for (int j = i; j > people[j][1]; --j)
                swap(people[j], people[j - 1]);
        }
        return people;
    }

    // 452. 用最少数量的箭引爆气球
    int findMinArrowShots(vector<vector<int>> &points) {
        auto compare = [](vector<int> &p1, vector<int> &p2) {
            return p1[0] < p2[0] or p1[0] == p2[0] and p1[1] < p2[1];
        };
        sort(points.begin(), points.end(), compare);
        int res = 0, far = 0, i = 0;
        while (i < points.size()) {
            res++;
            far = points[i++][1];
            while (i < points.size()) {
                if (points[i][0] > far) break;
                far = min(far, points[i][1]);
                i++;
            }
        }
        return res;
    }

    // 435. 无重叠区间
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        auto compare = [](vector<int> &p1, vector<int> &p2) {
            return p1[0] < p2[0] or p1[0] == p2[0] and p1[1] < p2[1];
        };
        sort(intervals.begin(), intervals.end(), compare);
        int res = 0, right = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < right) {
                res++;
                right = min(right, intervals[i][1]);
            } else {
                right = intervals[i][1];
            }
        }
        return res;
    }

    // 763.划分字母区间
    vector<int> partitionLabels(string s) {
        // 统计每个字符出现的最远边界
        array<int, 26> farest = {0};
        for (int i = 0; i < s.length(); ++i)
            farest[s[i] - 'a'] = i;

        vector<int> res;
        int start = 0, end = farest[s[0] - 'a'];
        for (int i = 0; i < s.length(); ++i) {
            end = max(end, farest[s[i] - 'a']);
            if (i == end) {
                res.emplace_back(end - start + 1);
                start = i + 1;
            }
        }
        return res;
    }

    vector<int> partitionLabels2(string s) {
        vector<vector<int>> appears(26, {-1, -1});
        for (int i = 0; i < s.length(); ++i) {
            if (appears[s[i] - 'a'][0] == -1)
                appears[s[i] - 'a'][0] = i;
            appears[s[i] - 'a'][1] = i;
        }
        vector<vector<int>> intervals;
        for (auto &ch_appear: appears) {
            if (ch_appear[0] > -1)
                intervals.push_back(std::move(ch_appear));
        }
        auto compare = [](vector<int> &p1, vector<int> &p2) {
            return p1[0] < p2[0] or p1[0] == p2[0] and p1[1] < p2[1];
        };
        sort(intervals.begin(), intervals.end(), compare);
        vector<int> res;
        int start = intervals[0][0], end = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < end) {
                end = max(end, intervals[i][1]);
            } else {
                res.emplace_back(end - start + 1);
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        res.push_back(end - start + 1);
        return res;
    }

    // 56. 合并区间
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        auto compare = [](vector<int> &p1, vector<int> &p2) { return p1[0] < p2[0]; };
        std::sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int>> res;
        int left = intervals[0][0], right = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= right) {
                right = max(right, intervals[i][1]);
            } else {
                res.push_back({left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        res.push_back({left, right});
        return res;
    }

    // 738. 单调递增的数字
    int monotoneIncreasingDigits(int n) {
        if (n / 10 == 0) return n;
        string n_str = std::to_string(n);
        int flag = n_str.size();
        for (int i = n_str.size() - 1; i > 0; ++i) {
            if (n_str[i] < n_str[i - 1]) {
                flag = i;
                n_str[i - 1]--;
            }
        }
        for (int i = flag; i < n_str.size(); ++i) {
            n_str[i] = '9';
        }
        return stoi(n_str);
    }

    // 714. 买卖股票的最佳时机含手续费
    int maxProfit(vector<int> &prices, int fee) {
        int total_profit = 0, buy = prices[0], sell = prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > buy) {
                // 要求重新购买小于之前能够卖出的最大值 - fee 才重新买入
                if (sell - prices[i] > fee) {
                    total_profit += sell - buy - fee;
                    buy = sell = prices[i];
                }
                sell = max(sell, prices[i]);
            } else {
                // 更新买入的最小值
                total_profit += max(0, sell - buy - fee);
                buy = sell = prices[i];
            }
        }
        total_profit += max(0, sell - buy - fee);
        return total_profit;
    }

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}

        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    // 968.监控二叉树
    int camera_num;

    // 返回输入结点被监视的情况
    // 0: 没被监视
    // 1: 有被监视，没摄像头
    // 2: 有被监视，有摄像头
    int isWatched(TreeNode *root) {
        // 空结点可以看作情况 1
        if (root == nullptr) return 1;
        int left_watched = isWatched(root->left);
        int right_watched = isWatched(root->right);
        // 只要有一个子节点没有被监视，当前结点就要上摄像头
        if (left_watched == 0 or right_watched == 0) {
            camera_num++;
            return 2;
        }
        // 只要有一个子节点有摄像头，当前结点算在情况 1
        if (left_watched == 2 or right_watched == 2) return 1;
        // 剩下的情况就是子节点都没有摄像头但被监视了
        return 0;
    }

    int minCameraCover(TreeNode *root) {
        camera_num = 0;
        if (isWatched(root) == 0) camera_num++;
        return camera_num;
    }
};