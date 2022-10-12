//
// Created by huangjiyi on 2022/10/11.
//
#include "utils.h"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
  public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
  public:
    // 102. 二叉树的层序遍历
    // https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
    vector<vector<int>> levelOrder(TreeNode *root) {
        if (root == nullptr)
            return {};
        vector<vector<int>> res{};
        queue<TreeNode *> node_queue;
        node_queue.push(root);
        while (not node_queue.empty()) {
            res.push_back({});
            int layer_size = node_queue.size();
            for (int i = 0; i < layer_size; ++i) {
                TreeNode *node = node_queue.front();
                res.back().push_back(node->val);
                if (node->left != nullptr)
                    node_queue.push(node->left);
                if (node->right != nullptr)
                    node_queue.push(node->right);
                node_queue.pop();
            }
        }
        return res;
    }

    // 117. 填充每个节点的下一个右侧节点指针 II
    // 1. 使用层序遍历求解
    // 2. 使用递归求解
    //    有问题，因为递归的深度优先搜索，可能出现遍历到某个结点时上一层还没有好next关系，
    //    从而导致当前结点寻找的next为nullptr，其实next在距离很远的地方
    // 3. 下面的方法
    Node *connect(Node *root) {
        if (root == nullptr)
            return root;
        Node *cur = root;
        while (cur != nullptr) {
            Node *dummy = new Node;  // 关键
            Node *pre = dummy;
            while (cur != nullptr) {
                if (cur->left != nullptr) {
                    pre->next = cur->left;
                    pre = pre->next;
                }
                if (cur->right != nullptr) {
                    pre->next = cur->right;
                    pre = pre->next;
                }
                cur = cur->next;
            }
            cur = dummy->next;
        }
        return root;
    }

    // 104. 二叉树的最大深度
    int maxDepth(TreeNode *root) {
        if (root == nullptr)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // 111. 二叉树的最小深度
    int minDepth(TreeNode *root) {
        if (root == nullptr)
            return 0;
        // 如果当前结点的左右孩子均存在，返回更小的最小深度 + 1
        if (root->left and root->right)
            return 1 + min(minDepth(root->left), minDepth(root->right));
        // 如果当前结点的左右孩子至少有一个不存在，因为不存在的那个结点的深度肯定 <= 存在的那个结点
        // 而当前结点的深度只取决于存在的结点，所以取更大的最小深度 + 1
        return 1 + max(minDepth(root->left), minDepth(root->right));
    }
};

int main() {
    vector<Node *> nodes{nullptr};
    for (int i = 0; i < 8; ++i)
        nodes.emplace_back(new Node(i + 1));
    Node *root = nodes[1];
    root->left = nodes[2];
    root->right = nodes[3];
    nodes[2]->left = nodes[4];
    nodes[2]->right = nodes[5];
    nodes[3]->right = nodes[6];
    nodes[4]->left = nodes[7];
    nodes[6]->right = nodes[8];

    Solution solve;
    solve.connect(root);
    void print_next(Node *node);
    print_next(nodes[1]);
    print_next(nodes[2]);
    print_next(nodes[4]);
    print_next(nodes[7]);
    cout << endl;
    cout << nodes[4]->next->val << endl;
    cout << nodes[4]->next->next->val << endl;
    cout << nodes[6]->right->val << endl;
    cout << (nodes[7]->next == nullptr) << endl;

    return 1;
}

void print_next(Node *node) {
    while (node != nullptr) {
        cout << node->val << " ";
        node = node->next;
    }
    cout << "# ";
}