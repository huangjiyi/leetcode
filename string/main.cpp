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
    int strStr(string haystack, string needle) {
        // 内置函数直接秒了
        // 或者自己写KMP
        return haystack.find(needle);
    }

    bool repeatedSubstringPattern(string s) {

    }
};

int main() {
    Solution solve;
    string s = "hello  world";
    print("[" + solve.reverseWords3(s) + "]");
    return 1;
}