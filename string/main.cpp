//
// Created by huangjiyi on 2022/8/18.
//
#include "utils.h"

class Solution {
  public:
    // 344. 反转字符串
    void reverseString(vector<char> &s) {
        int n = s.size() - 1;
        for (int i = 0; i < s.size() / 2; ++i) {
            swap(s[i], s[n - i]);
        }
    }

    // 541. 反转字符串 II
    string reverseStr(string s, int k) {
        for (auto iter = s.begin(); iter < s.end(); iter += 2 * k) {
            if (iter + k < s.end())
                reverse(iter, iter + k);
            else
                reverse(iter, s.end());
        }
        return s;
    }

    // 剑指 Offer 05. 替换空格
    // https://leetcode.cn/problems/ti-huan-kong-ge-lcof/submissions/
    string replaceSpace(string s) {
        // 双指针法
        // 先统计字符串中得空格数n，在字符串后面添加2n个元素
        // 将左指针指向原始字符串的末尾，将右指针指向新字符串的末尾
        // 左右指针从右向左遍历，不断将左指针指向的元素赋给右指针指向的位置
        // 如果左指针指向的是空格，则右指针连续赋值3个元素，即0,2,%(从右向左)
        int space_num = 0;
        for (const auto &ch: s)
            if (ch == ' ') space_num++;
        int left = s.size() - 1;
        s.resize(s.size() + 2 * space_num);
        for (int right = s.size() - 1; right >= 0; --right, --left) {
            if (s[left] == ' ') {
                s[right--] = '0';
                s[right--] = '2';
                s[right] = '%';
            } else
                s[right] = s[left];
        }
        return s;
    }

    // 151. 颠倒字符串中的单词
    // https://leetcode.cn/problems/reverse-words-in-a-string/submissions/
    string reverseWords(string s) {
        // 先获取字符串中的每个单词
        // 然后在输出单词倒序的字符串
        vector<string> words;
        auto left = s.begin(), right = s.begin();
        for (; right < s.end(); ++right) {
            if (*right == ' ') {
                if (*left == ' ')
                    left++;
                else {
                    words.emplace_back(left, right);
                    left = right + 1;
                }
            }
        }
        if (s.back() != ' ') words.emplace_back(left, s.end());
        s.clear();
        for (; !words.empty(); words.pop_back())
            s.append(words.back()).push_back(' ');
        s.pop_back();
        return s;
    }

    string reverseWords2(string s) {
        // 上一个函数用标准库实现的版本
        istringstream iss(s);
        vector<string> words(istream_iterator<string>{iss}, istream_iterator<string>());
        s.clear();
        for (; !words.empty(); words.pop_back())
            s.append(words.back()).push_back(' ');
        s.pop_back();
        return s;
    }

    string reverseWords3(string s) {
        // 先处理字符串中的空格
        int slow = 0, fast = 0;
        while (fast < s.size() and s[fast] == ' ') fast++;
        for (; fast < s.size() - 1; fast++) {
            if (s[fast] == ' ' and s[fast + 1] == ' ') continue;
            s[slow++] = s[fast];
        }
        if (s.back() != ' ') s[slow++] = s.back();
        s.resize(slow);
        // 再翻转字符串
        reverse(s.begin(), s.end());
        // 再翻转字符串中的每个单词
        slow = 0, fast = 0;
        for (; fast < s.size(); ++fast) {
            if (s[fast] == ' ') {
                reverse(s.begin() + slow, s.begin() + fast);
                slow = fast + 1;
            }
        }
        reverse(s.begin() + slow, s.begin() + fast);
        return s;
    }

    // 剑指 Offer 58 - II. 左旋转字符串
    // https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/submissions/
    string reverseLeftWords(string s, int n) {
        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }

    // 28. 实现 strStr()
    // https://leetcode.cn/problems/implement-strstr/
    int strStr2(string haystack, string needle) {
        // 内置函数直接秒了
        // 或者自己写KMP
        return haystack.find(needle);
    }

    // 获取KMP算法中的next数组
    vector<int> getNext(const string &needle) {
        // 参考: https://www.zhihu.com/question/21923021
        // k-前缀: 字符串的前 k 个字符, k-后缀: 字符串的后 k 个字符, k 必须小于字符串长度 (next[0] = 0)
        // next[i]: P[0]~P[i]这一段字符串, 使得k-前缀恰等于k-后缀的最大的k.
        // 维护左右两个指针, 右指针从1开始, 表示当前要计算next[i]的i，左指针则表示用来最大k-前缀的末尾下标
        // 令 left = next[right-1], 这样 t 中前 left 个元素与 t[right] 左边 left 个元素相等 (根据 next[i] 定义)
        // 比较 t[right] 和 t[left], 如果 t[right] == t[left], 则 next[right] = left + 1,
        // 如果 t[right] != t[left], 则令 left = next[left], 继续比较 t[right] 和 t[left],
        // 不断重复直到 left = 0, 还不相等就令 next[right] = 0
        vector<int> next(needle.length(), 0);
        int left = 0, right = 1;
        while (right < needle.length()) {
            if (needle[right] == needle[left])
                next[right++] = left++ + 1;
            else if (left)
                left = next[left - 1];
            else
                right++;
        }
        return next;
    }

    // KMP字符串匹配算法
    int strStr(const string &haystack, const string &needle) {
        // 先获取模式串的 next 数组
        // 后面匹配的逻辑与计算 next 数组时类似
        auto next = getNext(needle);
        int i = 0, cur = 0;
        while (i < haystack.length()) {
            if (haystack[i] == needle[cur]) {
                i++;
                cur++;
            } else if (cur) {
                cur = next[cur - 1];
            } else {
                i++;
            }
            if (cur == needle.length())
                return i - cur;
        }
        return -1;
    }

    // 459. 重复的子字符串
    bool repeatedSubstringPattern(string s) {
        int end = 0;  // 闭区间
        while (end < s.size() - 1 and s[end + 1] != s[0])
            end++;
        int left = 0, right = end + 1;
        while (right < s.size()) {
            if (s[right] != s[left]) {
                left = 0;
                right = end + 2;
                while (right < s.size() and s[right] != s[0]) right++;
                end = right - 1;
            } else {
                if ((right - end) % (end + 1) == 0) {
                    if (right == s.size() - 1)
                        return true;
                    left = 0;
                } else {
                    left++;
                }
                right++;
            }
        }
        return false;
    }

    bool repeatedSubstringPattern2(string s) {
        // 判断 s + s (首尾除外)中是否存在 s
        string s2(s.begin() + 1, s.end());
        s2.append(s.begin(), s.end() - 1);
        return s2.find(s) != string::npos;
    }

    bool repeatedSubstringPattern3(string s) {
        // 利用 KMP 的 next 数组
        // 观察由重复子串构成的字符串的 next 数组可以发现
        // 假设 s 由 n 个最小重复子串 t 构成
        // 那么 s 中 k-前缀和 k-后缀相等的最大 k 一定是 (n - 1) * t.length (因为 k 一定小宇 s.length)
        // 即 k > 0 and k % (s.length - k) == 0
        int next[s.size()];
        int left = 0, right = 1;
        while (right < s.length()) {
            if (s[right] == s[left])
                next[right++] = left++ + 1;
            else if (left)
                left = next[left - 1];
            else {
                next[right] = 0;
                right++;
            }
        }
        int k = next[s.size() - 1];
        return k > 0 and k % (s.length() - k) == 0;
    }
};

int main() {
    Solution solve;
    string s = "abac";
    print(solve.repeatedSubstringPattern3(s));
    return 1;
}