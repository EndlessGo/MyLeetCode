//剑指 Offer 68 - I. 二叉搜索树的最近公共祖先
//235. Lowest Common Ancestor of a Binary Search Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //2020年6月22日10:54:50~2020年6月22日11:13:24
        //O(logn) time, O(logn) space
        //recursive: cur node is lowest common ancestor when p,q in left and right
        //it means val relation: p->val < root->val < q->val
        if (!root || root == p || root == q)
            return root;
        if (p->val > q->val)
            swap(p,q);
        if (root->val < p->val)
            return lowestCommonAncestor(root->right, p, q);
        if (root->val > q->val)
            return lowestCommonAncestor(root->left, p, q);        
        return root;
    }
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* cur = root;
        if (p->val > q->val)
            swap(p,q);
        while (cur)
        {
            if (cur->val < p->val)
                cur = cur->right;
            else if (cur->val > q->val)
                cur = cur->left;
            else
                break;
        }
        return cur;
    }
};
