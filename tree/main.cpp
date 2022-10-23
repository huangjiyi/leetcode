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

    // 226. 翻转二叉树
    TreeNode *invertTree(TreeNode *root) {
        if (root == nullptr)
            return root;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }

    // 101. 对称二叉树
    // 思路：判断对称二叉树根节点的左右子树是不是翻转的, 采用递归同时对左右子树进行遍历，
    // 其中左子树采用左右中的后续变绿，右子树采用右左中的后续遍历
    bool compare(TreeNode *left, TreeNode *right) {
        if (left == nullptr and right == nullptr)
            return true;
        else if (left != nullptr and right != nullptr and left->val == right->val)
            return compare(left->left, right->right) and compare(left->right, right->left);
        else
            return false;
    }

    bool isSymmetric(TreeNode *root) {
        if (root == nullptr)
            return false;
        return compare(root->left, root->right);
    }

    // 572. 另一棵树的子树
    bool isSametree(TreeNode *p, TreeNode *q) {
        if (!p and !q)
            return true;
        else if (p and q and p->val == q->val)
            return isSametree(p->left, q->left) and isSametree(p->right, q->right);
        else
            return false;
    }

    bool isSubtree(TreeNode *root, TreeNode *subRoot) {
        if (root == nullptr)
            return false;
        if (isSametree(root, subRoot))
            return true;
        else
            return isSubtree(root->left, subRoot) or isSubtree(root->right, subRoot);
    }

    // 222. 完全二叉树的节点个数
    // 思路：
    // （1）层序遍历
    // （2）递归实现
    int countNodes1(TreeNode *root) {
        if (root == nullptr)
            return 0;
        else
            return countNodes1(root->left) + countNodes1(root->right) + 1;
    }

    // （3）对于某个结点，先不断遍历它的左节点和右结点确定左右深度，
    // 如果左右深度相等（叶子结点必相等），则以该结点的根结点的树为满二叉树，返回 2^d - 1
    // 如果左右深度不相等，则递归返回左右子树的结点数之和 + 1
    int countNodes(TreeNode *root) {
        if (root == nullptr)
            return 0;
        int left_depth = 1, right_depth = 1;
        TreeNode *node = root->left;
        while (node != nullptr) {
            node = node->left;
            ++left_depth;
        }
        node = root->right;
        while (node != nullptr) {
            node = node->right;
            ++right_depth;
        }
        if (left_depth == right_depth)
            return (2 << left_depth) - 1;
        else
            return countNodes(root->left) + countNodes(root->right) + 1;
    }

    // 110. 平衡二叉树
    // 获取以输入结点为根节点的树的高度，如果高度为 -1 则不是平衡二叉树
    int getHeight(TreeNode *node) {
        if (node == nullptr)
            return 0;
        int left_height = getHeight(node->left);
        if (left_height == -1)
            return -1;
        int right_height = getHeight(node->right);
        if (right_height == -1)
            return -1;
        if (abs(left_height - right_height) > 1)
            return -1;
        return max(left_height, right_height) + 1;
    }

    bool isBalanced(TreeNode *root) {
        return getHeight(root) != -1;
    }

    // 257. 二叉树的所有路径
    vector<string> res;

    void transversePath(TreeNode *node, string path) {
        path.append(to_string(node->val));
        if (node->left == nullptr and node->right == nullptr) {
            res.push_back(path);
            return;
        }
        path.append("->");
        if (node->left != nullptr)
            transversePath(node->left, path);
        if (node->right != nullptr)
            transversePath(node->right, path);
    }

    vector<string> binaryTreePaths(TreeNode *root) {
        res.clear();
        transversePath(root, "");
        return res;
    }

    // 404. 左叶子之和
    int _sumOfLeftLeaves(TreeNode *node, bool left) {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr and node->right == nullptr)
            return left ? node->val : 0;
        return _sumOfLeftLeaves(node->left, true) + _sumOfLeftLeaves(node->right, false);
    }

    int sumOfLeftLeaves(TreeNode *root) {
        return _sumOfLeftLeaves(root, false);
    }

    // 513. 找树左下角的值
    // 思路：找到深度最大的、按先序遍历第一个出现的叶子结点
    int max_depth, bottom_left_val;

    void getDepth(TreeNode *node, int depth) {
        if (node->left != nullptr) {
            getDepth(node->left, depth + 1);
        }
        if (node->right != nullptr) {
            getDepth(node->right, depth + 1);
        }
        if (node->left == nullptr and node->right == nullptr) {
            if (depth > max_depth) {
                max_depth = depth;
                bottom_left_val = node->val;
            }
        }
    }

    int findBottomLeftValue(TreeNode *root) {
        max_depth = -1;
        getDepth(root, 0);
        return bottom_left_val;
    }

    // 112. 路径总和
    bool find_path;

    void transverseSum(TreeNode *node, int path_sum, int &target_sum) {
        path_sum += node->val;
        if (node->left == nullptr and node->right == nullptr) {
            if (path_sum == target_sum)
                find_path = true;
            return;
        }
        if (node->left != nullptr)
            transverseSum(node->left, path_sum, target_sum);
        if (node->right != nullptr)
            transverseSum(node->right, path_sum, target_sum);
    }

    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr)
            return false;
        find_path = false;
        transverseSum(root, 0, targetSum);
        return find_path;
    }

    // 113. 路径总和 II
    vector<vector<int>> res_paths;
    vector<int> path;

    void transversePath2(TreeNode *node, int path_sum, int &target_sum) {
        path_sum += node->val;
        if (node->left == nullptr and node->right == nullptr) {
            if (path_sum == target_sum)
                res_paths.push_back(path);
            return;
        }
        if (node->left != nullptr) {
            path.push_back(node->left->val);
            transversePath2(node->left, path_sum, target_sum);
            path.pop_back();
        }
        if (node->right != nullptr) {
            path.push_back(node->right->val);
            transversePath2(node->right, path_sum, target_sum);
            path.pop_back();
        }
    }

    vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
        res_paths.clear();
        if (root == nullptr) return {};
        path.clear();
        path.push_back(root->val);
        transversePath2(root, 0, targetSum);
        return res_paths;
    }

    // 106. 从中序与后序遍历序列构造二叉树
    // 原理：以后序数组的最后一个元素（根节点）为切割点，先切中序数组，
    // 根据中序数组，反过来在切后序数组。一层一层切下去，每次后序数组最后一个元素就是节点元素
    typedef vector<int>::iterator int_iter;

    TreeNode *_buildTree(vector<int> &inorder, vector<int> &postorder,
                         int_iter in_begin, int_iter in_end, int_iter post_begin, int_iter post_end) {
        int root_val = *(--post_end);
        TreeNode *root = new TreeNode(root_val);
        auto in_iter = std::find(in_begin, in_end, root_val);
        if (in_iter != in_begin)
            root->left = _buildTree(inorder, postorder, in_begin, in_iter,
                                    post_begin, post_begin + (in_iter - in_begin));
        in_iter++;
        if (in_iter != in_end)
            root->right = _buildTree(inorder, postorder, in_iter, in_end,
                                     post_end - (in_end - in_iter), post_end);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return _buildTree(inorder, postorder,
                          inorder.begin(), inorder.end(),
                          postorder.begin(), postorder.end());
    }

    // 105. 从前序与中序遍历序列构造二叉树
    unordered_map<int, int> in_idx_map;

    TreeNode *_buildTree2(vector<int> &preorder, vector<int> &inorder,
                          int pre_begin, int pre_end, int in_begin, int in_end) {
        int root_val = preorder[pre_begin++];
        TreeNode *root = new TreeNode(root_val);
        int in_cut_idx = in_idx_map[root_val];
        if (in_cut_idx > in_begin) {
            root->left = _buildTree2(preorder, inorder,
                                     pre_begin, pre_begin + in_cut_idx - in_begin,
                                     in_begin, in_cut_idx);
        }
        in_cut_idx++;
        if (in_cut_idx < in_end) {
            root->right = _buildTree2(preorder, inorder,
                                      pre_end - (in_end - in_cut_idx), pre_end,
                                      in_cut_idx, in_end);
        }
        return root;
    }

    TreeNode *buildTree2(vector<int> &preorder, vector<int> &inorder) {
        in_idx_map.clear();
        for (int i = 0; i < inorder.size(); ++i)
            in_idx_map[inorder[i]] = i;
        return _buildTree2(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }

    // 654. 最大二叉树
    typedef vector<int>::iterator i_iter;

    TreeNode *_construct(vector<int> &nums, i_iter begin, i_iter end) {
        auto max_iter = max_element(begin, end);
        TreeNode *root = new TreeNode(*max_iter);
        if (max_iter != begin)
            root->left = _construct(nums, begin, max_iter);
        max_iter++;
        if (max_iter != end)
            root->right = _construct(nums, max_iter, end);
        return root;
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        return _construct(nums, nums.begin(), nums.end());
    }

    // 617. 合并二叉树
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }

    // 700. 二叉搜索树中的搜索
    TreeNode *searchBST(TreeNode *root, int val) {
        if (root == nullptr)
            return nullptr;
        if (root->val == val)
            return root;
        else if (root->val < val)
            return searchBST(root->right, val);
        else
            return searchBST(root->left, val);
    }

    // 98. 验证二叉搜索树
    // 思路：二叉搜索树中序遍历为升序序列
    TreeNode *pre;

    bool _isValidBST(TreeNode *root) {
        if (root == nullptr)
            return true;
        if (!_isValidBST(root->left))
            return false;
        if (pre != nullptr and pre->val >= root->val)
            return false;
        pre = root;
        return _isValidBST(root->right);
    }

    bool isValidBST(TreeNode *root) {
        pre = nullptr;
        return _isValidBST(root);
    }

    // 530. 二叉搜索树的最小绝对差
    // 同样是先序遍历，记录相邻两个数差值的最小值
    int min_diff;
    TreeNode *last;

    void _getMinimumDifference(TreeNode *node) {
        if (node->left)
            _getMinimumDifference(node->left);
        if (last != nullptr)
            min_diff = min(min_diff, node->val - last->val);
        last = node;
        if (node->right)
            _getMinimumDifference(node->right);
    }

    int getMinimumDifference(TreeNode *root) {
        min_diff = INT32_MAX;
        last = nullptr;
        _getMinimumDifference(root);
        return min_diff;
    }

    // 501.二叉搜索树中的众数
    vector<int> modes;
    int last_num, count, max_count;

    void _findMode(TreeNode *root) {
        if (root->left)
            _findMode(root->left);
        if (root->val == last_num) {
            count++;
        } else {
            if (count > max_count) {
                modes.clear();
                modes.push_back(last_num);
                max_count = count;
            } else if (count == max_count) {
                modes.push_back(last_num);
            }
            last_num = root->val;
            count = 1;
        }
        if (root->right)
            _findMode(root->right);
    }

    vector<int> findMode(TreeNode *root) {
        last_num = INT32_MIN;
        count = 0;
        max_count = 0;
        _findMode(root);
        if (count > max_count) {
            modes.clear();
            modes.push_back(last_num);
        } else if (count == max_count) {
            modes.push_back(last_num);
        }
        return modes;
    }

    // 236. 二叉树的最近公共祖先
    // 思路：
    // 后序遍历一定是先遍历到2个目标子节点然后再遍历到最近公共祖先
    // 2个目标结点一定分别位于最近公共左线的左右子树中
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == p or root == q or root == nullptr) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr and right != nullptr)
            return root;
        if (left == nullptr)
            return right;
        return left;
    }

    // 235. 二叉搜索树的最近公共祖先
    // 1. 上一题的答案就可以
    // 2. 进行先序遍历，最近公共祖先为第一次遍历到 val 在区间 [p->val, q->val] 中的结点，
    TreeNode *_lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == nullptr) return nullptr;
        if (root->val > q->val)
            return _lowestCommonAncestor2(root->left, p, q);
        else if (root->val < p->val)
            return _lowestCommonAncestor2(root->right, p, q);
        else
            return root;
    }

    TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (p->val > q->val) swap(p, q);
        return _lowestCommonAncestor2(root, p, q);
    }

    // 701. 二叉搜索树中的插入操作
    TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr)
            return new TreeNode(val);
        if (val < root->val)
            root->left = insertIntoBST(root->left, val);
        else if (val > root->val)
            root->right = insertIntoBST(root->right, val);
        return root;
    }

    void _insertIntoBST(TreeNode *root, int val) {
        if (val < root->val) {
            if (root->left != nullptr)
                _insertIntoBST(root->left, val);
            else
                root->left = new TreeNode(val);
        } else if (val > root->val) {
            if (root->right != nullptr)
                _insertIntoBST(root->right, val);
            else
                root->right = new TreeNode(val);
        }
    }

    TreeNode *insertIntoBST2(TreeNode *root, int val) {
        if (root == nullptr)
            return new TreeNode(val);
        _insertIntoBST(root, val);
        return root;
    }

    // 450. 删除二叉搜索树中的节点
    // https://leetcode.cn/problems/delete-node-in-a-bst/
    TreeNode *deleteNode(TreeNode *root, int key) {
        // 1. 找不到待删除结点
        if (root == nullptr) return root;
        if (key < root->val) root->left = deleteNode(root->left, key);
        else if (key > root->val) root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr and root->right == nullptr) {
                // 2. 待删除结点左右孩子均为空
                delete root;
                return nullptr;
            } else if (root->left != nullptr and root->right != nullptr) {
                // 4. 待删除结点左右孩子均不为空
                TreeNode *pre = root, *left_max = root->left;
                // 找到左子树右下角 left_max（最大的结点）
                while (left_max->right) {
                    pre = left_max;
                    left_max = left_max->right;
                }
                // 将待删除结点用左子树 left_max 替换，先将 root->val 替换为 left_max 的 val，然后删除 left_max
                // 需要注意 left_max 可能有左子树但没有右子树，需要修改 left_max 父结点的的子树
                root->val = left_max->val;
                if (pre == root)
                    root->left = left_max->left;
                else
                    pre->right = left_max->left;
                delete left_max;
                return root;
            } else {
                // 3. 待删除结点只有一个孩子为空, 直接用孩子取代
                TreeNode *node = root->left ? root->left : root->right;
                delete root;
                return node;
            }
        }
        return root;
    }

    // 用指针规避几乎所有的条件判断
    TreeNode *deleteNode2(TreeNode *root, int key) {
        TreeNode **p = &root; //指向待删除节点的指针
        while (*p && (*p)->val != key)
            p = (*p)->val < key ? &(*p)->right : &(*p)->left;
        if (!*p) return root;
        TreeNode **t = &(*p)->right; //指向右树的最左空指针的指针（这里把左树合到右树，反之同理即可）
        while (*t) t = &(*t)->left;
        *t = (*p)->left;
        TreeNode *node = *p;
        *p = (*p)->right;
        delete node;
        return root;
    }

    // 669. 修剪二叉搜索树
    void clearTree(TreeNode *root) {
        if (root == nullptr)
            return;
        clearTree(root->left);
        clearTree(root->right);
        delete root;
    }

    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (root == nullptr) return nullptr;
        if (root->val < low) {
            clearTree(root->left);
            root->left = nullptr;
            TreeNode *next = root->right;
//            delete root;  // 删除 root 的话还要把 root 父结点的孩子指针置空，比较麻烦
            return trimBST(next, low, high);
        } else if (root->val > high) {
            clearTree(root->right);
            TreeNode *next = root->left;
//            delete root;
            return trimBST(next, low, high);
        } else {
            if (root->left) root->left = trimBST(root->left, low, high);
            if (root->right) root->right = trimBST(root->right, low, high);
            return root;
        }
    }

    // 108. 将有序数组转换为二叉搜索树
    TreeNode *_sortedArrayToBST(vector<int> &nums, size_t begin, size_t end) {
        if (begin == end) return nullptr;
        size_t root_idx = (begin + end) / 2;
        TreeNode *root = new TreeNode(nums[root_idx]);
        root->left = _sortedArrayToBST(nums, begin, root_idx);
        root->right = _sortedArrayToBST(nums, root_idx + 1, end);
        return root;
    }

    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return _sortedArrayToBST(nums, 0, nums.size());
    }

    // 538. 把二叉搜索树转换为累加树
    // 思路：中序遍历（右中左）
    int sum;

    void _convertBST(TreeNode *root) {
        if (root->right)
            _convertBST(root->right);
        sum += root->val;
        root->val = sum;
        if (root->left)
            _convertBST(root->left);
    }

    TreeNode *convertBST(TreeNode *root) {
        if (root == nullptr)
            return nullptr;
        sum = 0;
        _convertBST(root);
        return root;
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