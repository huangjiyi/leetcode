//
// Created by huangjiyi on 2022/8/13.
//
#include "utils.h"
#include "LinkList.h"

class Solution {
  public:
    // 203. 移除链表元素
    // https://leetcode.cn/problems/remove-linked-list-elements/
    ListNode *removeElements(ListNode *head, int val) {
        // 先处理头结点，保证头结点不是要被删除的结点
        while (head != nullptr and head->val == val) {
            auto tmp = head;
            head = head->next;
            delete tmp;
        }
        if (head == nullptr) return head;
        // 然后遍历删除头结点之后的结点
        auto node = head;
        while (node->next != nullptr)
            if (node->next->val == val) {
                auto tmp = node->next;
                node->next = node->next->next;
                delete tmp;
            } else {
                node = node->next;
            }
        return head;
    }

    ListNode *removeElements2(ListNode *head, int val) {
        // 构造一个虚拟头结点，其下一个节点为输入的头结点
        // 然后遍历删除虚拟头结点之后的结点
        auto *tmp_head = new ListNode(0, head);
        auto node = tmp_head;
        while (node->next != nullptr)
            if (node->next->val == val) {
                auto tmp = node->next;
                node->next = node->next->next;
                delete tmp;
            } else {
                node = node->next;
            }
        head = tmp_head->next;
        delete tmp_head;
        return head;
    }

    // 206. 反转链表
    // https://leetcode.cn/problems/reverse-linked-list/
    ListNode *reverseList(ListNode *head) {
        // 先找到尾结点，然后从头结点开始遍历
        if (head == nullptr) return head;
        auto tail = head;
        while (tail->next != nullptr)
            tail = tail->next;
        while (head != tail) {
            auto node = head;
            head = head->next;
            node->next = tail->next;
            tail->next = node;
        }
        return head;
    }

    ListNode *reverseList2(ListNode *head) {
        // 双指针法
        // 定义2个指针，cur指针指向当前结点，prev指针指向当前结点在当前链表的前驱结点
        // 初始化 cur = head, prev = nullptr, next = cur.next
        ListNode *prev = nullptr, *next;
        while (head != nullptr) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }

    // 24. 两两交换链表中的节点
    ListNode *swapPairs2(ListNode *head) {
        if (head == nullptr or head->next == nullptr) return head;
        ListNode *first = head, *second = head->next, *last_first = new ListNode();
        head = second;
        while (true) {
            last_first->next = second;
            first->next = second->next;
            second->next = first;
            last_first = first;
            first = first->next;
            if (first == nullptr) break;
            second = first->next;
            if (second == nullptr) break;
        }
        return head;
    }

    ListNode *swapPairs(ListNode *head) {
        // 递归实现
        if (head == nullptr or head->next == nullptr) return head;
        ListNode *second = head->next;
        head->next = swapPairs(second->next);
        second->next = head;
        return second;
    }

    // 19. 删除链表的倒数第 N 个结点
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // 快慢指针
        // 快指针先走n步，然后快慢指针一起移动，直到快指针到表尾
        auto tmp_head = new ListNode(0, head);
        auto fast = head, slow = tmp_head;
        for (; n > 1 and fast != nullptr; n--)
            fast = fast->next;
        if (fast == nullptr) return head;
        while (fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        auto tmp = slow->next;
        slow->next = tmp->next;
        delete tmp;
        head = tmp_head->next;
        delete tmp_head;
        return head;
    }

    // 面试题 02.07. 链表相交
    // https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // 用栈实现
        // 使用2个栈将2个链表结点的指针先后入栈，然后不断对比2个栈的栈顶元素和出栈，直到栈顶元素不相同
        if (headA == nullptr or headB == nullptr) return nullptr;
        stack<ListNode *> stackA, stackB;
        auto node = headA;
        while (node != nullptr) {
            stackA.push(node);
            node = node->next;
        }
        node = headB;
        while (node != nullptr) {
            stackB.push(node);
            node = node->next;
        }
        node = nullptr;
        while (!stackA.empty() and !stackB.empty()) {
            if (stackA.top() == stackB.top()) {
                node = stackA.top();
                stackA.pop();
                stackB.pop();
            } else break;
        }
        return node;
    }

    ListNode *getIntersectionNode2(ListNode *headA, ListNode *headB) {
        // 先将2个表在末尾进行对齐，然后进行遍历
        int lenA = 0, lenB = 0;
        auto curA = headA, curB = headB;
        for (; curA != nullptr; curA = curA->next)
            lenA++;
        for (; curB != nullptr; curB = curB->next)
            lenB++;
        if (lenA == 0 or lenB == 0)
            return nullptr;
        curA = headA, curB = headB;
        if (lenA > lenB) {
            for (; lenA > lenB; lenA--)
                curA = curA->next;
        } else {
            for (; lenB > lenA; lenB--)
                curB = curB->next;
        }
        for (; lenA > 0; lenA--) {
            if (curA == curB)
                return curA;
            curA = curA->next;
            curB = curB->next;
        }
        return nullptr;
    }

    ListNode *getIntersectionNode3(ListNode *headA, ListNode *headB) {
        // leetcode 官方题解 (另一种双指针)
        // 让2个指针分别从2个链表头结点开始遍历，如果碰到链表尾就转到另一个链表头，当2个指针指向的元素相同时停止
        // 原理：2个指针都遍历了一个链表+另一个链表不相交的部分，即2个链表中不相交的部分 + 相交的部分。
        // 当存在相交的部分时，2个指针在交点停止，否则在2个指针都遍历完了2个链表后指向空指针停止
        if (headA == nullptr or headB == nullptr) return nullptr;
        auto curA = headA, curB = headB;
        while (curA != curB) {
            curA = curA == nullptr ? headB : curA->next;
            curB = curB == nullptr ? headA : curB->next;
        }
        return curA;
    }

    // 142. 环形链表 II
    // https://leetcode.cn/problems/linked-list-cycle-ii/
    ListNode *detectCycle(ListNode *head) {
        // 用哈希表记录每个结点被遍历的次数
        // 如果一个结点被遍历了2次，则该结点就是连接点
        // 如果遍历到空指针，则表示没有环
        // 时间复杂度: O(n), 空间复杂度: O(n)
        unordered_map<ListNode*, int> visit_nums;
        auto node = head;
        for (; node != nullptr; node = node->next)
            if (++visit_nums[node] > 1) {
                return node;
            }
        return nullptr;
    }

    ListNode *detectCycle2(ListNode *head) {
        // 快慢指针法
        // 快指针和慢指针同时从头结点出发，其中快指针每次走2步，慢指针每次走1步
        // 如果没环，快指针最后会指向空指针
        // 如果有环，快指针和慢指针会在环内相遇
        // 设此时慢指针走了k步，环长为s，相遇点到入口点的距离为t
        // 快指针比慢指针多走k步，因为在环内相遇，快指针比慢指针多走n圈
        // 因此 k = ns => k - t = ns - t
        // 即若将2个指针分别放在相遇点和头结点以相同的速度出发，则他们必定在入口点相遇
        auto slow = head, fast = head;
        while (fast != nullptr and fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};


int main() {
    LinkList list;
    list.addAtHead(7);
    list.addAtHead(2);
    list.addAtHead(1);
    list.addAtIndex(3, 0);
    list.deleteAtIndex(2);
    list.addAtHead(6);
    list.addAtTail(4);
    list.print();
    print(list.get(4));
    list.addAtHead(4);
    list.addAtIndex(5, 0);
    list.addAtHead(6);

    return 1;
}