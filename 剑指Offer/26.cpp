//剑指 Offer 26. 树的子结构
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
    //判断B是否为A的子结构
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        //time O(mn), space O(m)
        if (!B) return false;
        if (!A) return false;
        return isSame(A,B) || isSubStructure(A->left,B) || isSubStructure(A->right,B);
    }
    bool isSame(TreeNode* A, TreeNode* B)
    {
        if (!B) return true;
        if (!A || A->val != B->val) return false;
        return isSame(A->left,B->left) && isSame(A->right,B->right);
    }
};
