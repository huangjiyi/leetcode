//
// Created by huangjiyi on 2022/8/15.
//

#ifndef LEETCODE_QUEUE_H
#define LEETCODE_QUEUE_H

#include "utils.h"

// 232. 用栈实现队列
class Queue {
  private:
    stack<int> input_stack, output_stack;

  public:
    Queue() = default;

    void push(int x) {
        input_stack.push(x);
    }

    int pop() {
        if (output_stack.empty()) {
            if (input_stack.empty())
                return 0;
            else
                stack_transfer();
        }
        int front = output_stack.top();
        output_stack.pop();
        return front;
    }

    int peek() {
        if (output_stack.empty()) {
            if (input_stack.empty())
                return 0;
            else
                stack_transfer();
        }
        return output_stack.top();
    }

    bool empty() {
        return input_stack.empty() and output_stack.empty();
    }

    void stack_transfer() {
        while (!input_stack.empty()) {
            output_stack.push(input_stack.top());
            input_stack.pop();
        }
    }
};



#endif //LEETCODE_QUEUE_H
