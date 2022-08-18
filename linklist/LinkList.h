//
// Created by huangjiyi on 2022/8/13.
//

#ifndef LEETCODE_LINKLIST_H
#define LEETCODE_LINKLIST_H

#include "utils.h"

class ListNode {
  public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(ListNode* next) : val(0), next(next) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class LinkList {
  private:
    ListNode* head;  // 虚拟头结点

  public:
    LinkList() : head(new ListNode(0, nullptr)) {}

    int get(int index);

    void addAtHead(int val);

    void addAtTail(int val);

    void addAtIndex(int index, int val);

    void deleteAtIndex(int index);

    void print();
};

int LinkList::get(int index) {
    auto node = head->next;
    while (index > 0 and node != nullptr) {
        node = node->next;
        index--;
    }
    if (node == nullptr) return -1;
    return node->val;
}

void LinkList::addAtHead(int val) {
    auto node = new ListNode(val, head->next);
    head->next = node;
}

void LinkList::addAtTail(int val) {
    auto node = head;
    while (node->next != nullptr)
        node = node->next;
    node->next = new ListNode(val, nullptr);
}

void LinkList::addAtIndex(int index, int val) {
    if (index < 0) {
        addAtHead(val);
        return;
    }
    auto node = head;
    while (index > 0 and node != nullptr) {
        node = node->next;
        index--;
    }
    if (index == 0 and node != nullptr) {
        auto insert_node = new ListNode(val, node->next);
        node->next = insert_node;
    }
}

void LinkList::deleteAtIndex(int index) {
    if (index < 0) return;
    auto node = head;
    while (index > 0 and node != nullptr) {
        node = node->next;
        index--;
    }
    if (node != nullptr and node->next != nullptr) {
        auto tmp = node->next;
        node->next = node->next->next;
        delete tmp;
    }
}

void LinkList::print() {
    auto node = head;
    while (node != nullptr) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << endl;
}

#endif //LEETCODE_LINKLIST_H
