#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

int maxDepth(TreeNode* root) {
    int max_depth{1};
    if (nullptr != root) {
        int left_depth = maxDepth(root->left);
        int right_depth = maxDepth(root->right);
        max_depth += std::max(left_depth, right_depth);
    } else {
        max_depth = 0;
    }

    return max_depth;
};

void printTree(TreeNode* root) {
    if (nullptr != root) {
        std::queue<TreeNode*> node_queue;
        node_queue.push(root);

        while (!node_queue.empty()) {
            TreeNode* node = node_queue.front();
            node_queue.pop();
            std::cout << node->val << " ";
            if (nullptr != node->left) {
                node_queue.push(node->left);
            }
            if (nullptr != node->right) {
                node_queue.push(node->right);
            }
        }
    }

    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Prevent compiler warnings about unused parameters
    (void) argc;
    (void) argv;

    //   3
    //  / \
    // 9  20
    //   /  \
    //  15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    printTree(root);

    std::cout << "Max depth of binary tree is: " << maxDepth(root) << std::endl;

    return 0;
}