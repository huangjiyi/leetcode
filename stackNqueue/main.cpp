//
// Created by huangjiyi on 2022/8/15.
//
#include "queue.h"
#include "stack.h"

class Solution {
    unordered_map<char, char> bracket = {{'(', ')'},
                                         {'[', ']'},
                                         {'{', '}'}};

  public:
    Solution() = default;

    // 20. 有效的括号
    bool isValid(string s) {
        if (s.length() % 2 == 1) return false;
        stack<char> char_stack;
        for (const auto &ch: s) {
            if (!char_stack.empty() and ch == bracket[char_stack.top()])
                char_stack.pop();
            else
                char_stack.push(ch);
        }
        return char_stack.empty();
    }

    // 1047. 删除字符串中的所有相邻重复项
    string removeDuplicates(string s) {
        string result;
        for (const auto &ch: s) {
            if (!result.empty() and ch == result.back())
                result.pop_back();
            else
                result.push_back(ch);
        }
        return result;
    }

    // 150. 逆波兰表达式求值
    int evalRPN(vector<string> &tokens) {
        // 栈实现
        stack<int> calc_stack;
        for (const auto &token: tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = calc_stack.top();
                calc_stack.pop();
                int a = calc_stack.top();
                calc_stack.pop();
                if (token == "+") calc_stack.push(a + b);
                else if (token == "-") calc_stack.push(a - b);
                else if (token == "*") calc_stack.push(a * b);
                else calc_stack.push(a / b);
            } else {
                calc_stack.push(stoi(token));
            }
        }
        return calc_stack.top();
    }

    // 单调队列
    class MonoQueue {
      private:
        deque<int> que;

      public:
        MonoQueue() = default;

        void push(int x) {
            while (!que.empty() and que.back() < x)
                que.pop_back();
            que.push_back(x);
        }

        void pop() {
            que.pop_front();
        }

        int front() {
            return que.front();
        }
    };

    // 239. 滑动窗口最大值
    // https://leetcode.cn/problems/sliding-window-maximum/
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        // 单调队列实现（代码用deque实现）
        // 单调队列在队尾插入元素时，要从队尾开始不断将待插入元素与之前的元素进行，弹出比待插入元素小的元素，
        // 直到碰到更大的元素，这样队列中的元素是一个递减的顺序，单调队列队首元素是最大值
        // 在解决滑动窗口最大值问题时，先将初始窗口中的元素依次插入单调队列
        // 然后在滑动窗口时，将要滑出窗口的元素与单调队列队首元素进行比较，相等就弹出队首元素
        // 同时将要滑入窗口的元素插入到单调队列中
        vector<int> result;
        MonoQueue mono_que;
        int i = 0;
        for (; i < k; ++i)
            mono_que.push(nums[i]);
        result.push_back(mono_que.front());
        for (; i < nums.size(); ++i) {
            if (nums[i - k] == mono_que.front())
                mono_que.pop();
            mono_que.push(nums[i]);
            result.push_back(mono_que.front());
        }
        return result;
    }

    // 347. 前 K 个高频元素
    // https://leetcode.cn/problems/top-k-frequent-elements/
    vector<int> topKFrequent(vector<int> &nums, int k) {
        // 先用哈希表统计每个数出现的频率
        // 然后对频率进行排序再去除前 k 个数
        // 该函数直接使用标准库内置排序函数实现
        unordered_map<int, int> frequency;
        for (const auto &num: nums)
            frequency[num]++;
        vector<int> keys;
        for (auto &item: frequency)
            keys.push_back(item.first);
        sort(keys.begin(), keys.end(),
             [&frequency](const int &key1, const int &key2) {
                 return frequency.at(key1) > frequency.at(key2);
             });
        keys.erase(keys.end() - max(0, static_cast<int>(keys.size()) - k), keys.end());
        return keys;
    }

    class compare {
      public:
        bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
            return p1.second > p2.second;
        }
    };

    vector<int> topKFrequent2(vector<int> &nums, int k) {
        // 先用哈希表统计每个数出现的频率
        // 然后对频率进行排序再去除前 k 个数
        // 该函数使用优先级队列进行排序
        unordered_map<int, int> frequency;
        for (const auto &num: nums)
            frequency[num]++;
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pri_que;
        for (auto & item : frequency) {
            pri_que.push(item);
            if (pri_que.size() > k) pri_que.pop();
        }
        vector<int> result;
        while (!pri_que.empty()) {
            result.push_back(pri_que.top().first);
            pri_que.pop();
        }
        return result;
    }
};


int main() {
    Solution solve;
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    print(solve.topKFrequent2(nums, 2));
    // print(solve.maxSlidingWindow(nums, 3));

    return 1;
}