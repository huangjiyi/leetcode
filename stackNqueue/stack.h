//
// Created by huangjiyi on 2022/8/15.
//

#ifndef LEETCODE_STACK_H
#define LEETCODE_STACK_H

#include "utils.h"

class MyStack {
  private:
    queue<int> queue1, queue2;

  public:
    MyStack() = default;

    void push(int x) {
        queue1.push(x);
    }

    int pop() {
        int result = 0;
        while (true) {
            result = queue1.front();
            queue1.pop();
            if (queue1.empty()) break;
            queue2.push(result);
        }
        queue1.swap(queue2);
        return result;
    }

    int top() {
        return queue1.back();
    }

    bool empty() {
        return queue1.empty();
    }
};

#endif //LEETCODE_STACK_H
