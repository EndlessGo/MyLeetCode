//剑指 Offer 27. 二叉树的镜像
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//1.前序遍历
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
	//time O(n), space O(n)
        if (!root) return NULL;
        swap(root->left, root->right);
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }
};

//2.循环
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if (!root) return NULL;
        //time O(n), space O(n)        
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty())
        {
            TreeNode* node = que.front();
            que.pop();
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
            swap(node->left, node->right);            
        }
        return root;
    }
};
