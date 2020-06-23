//剑指 Offer 07. 重建二叉树
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//1.递归
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //2020年6月23日11:04:06~2020年6月23日11:31:33
        //前序遍历cur，将中序遍历分成left和right两个数组，数组为空则说明无孩子节点
	//O(n) space, O(n) time
        int root_index = 0;
        return buildTree(preorder, root_index, inorder, 0, inorder.size()-1);
    }
    TreeNode* buildTree(vector<int>& preorder, int& root_index, vector<int>& inorder, int left, int right) {
        if (left > right)
            return NULL;
        TreeNode* root = NULL;
        for (int i = left; i <= right; ++i)
        {
            if (preorder[root_index] == inorder[i])
            {
                root = new TreeNode(preorder[root_index]);
                ++root_index;
                root->left = buildTree(preorder,root_index,inorder,left,i-1);
                root->right = buildTree(preorder,root_index,inorder,i+1,right);
                break;
            }
        }
        return root;
    }
};
//上面的改进
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //O(n) space, O(n) time
        int root_index = 0;
        for (int i = 0; i < inorder.size(); ++i)
        {
            pos[inorder[i]] = i;
        }
        return buildTree(preorder, root_index, inorder, 0, inorder.size()-1);
    }
    //以preorder[root_index]为根节点，inorder[left...right]建立树。左子树在inorder[left,i-1]，右子树在inorder[i+1,right]
    TreeNode* buildTree(vector<int>& preorder, int& root_index, vector<int>& inorder, int left, int right) {
        if (left > right)
            return NULL;
        TreeNode* root = new TreeNode(preorder[root_index]);
        int i = pos[preorder[root_index]];
        ++root_index;
        root->left = buildTree(preorder,root_index,inorder,left,i-1);
        root->right = buildTree(preorder,root_index,inorder,i+1,right);
        return root;
    }
private:
    unordered_map<int/*inorder val*/,int/*inorder pos*/> pos;
};

//2.迭代
 /*
    使用前序遍历的第一个元素创建根节点。
    创建一个栈，将根节点压入栈内。
    初始化中序遍历下标为 0。
    遍历前序遍历的每个元素，判断其上一个元素（即栈顶元素）是否等于中序遍历下标指向的元素。
        若上一个元素不等于中序遍历下标指向的元素，则将当前元素作为其上一个元素的左子节点，并将当前元素压入栈内。
        若上一个元素等于中序遍历下标指向的元素，则从栈内弹出一个元素，同时令中序遍历下标指向下一个元素，之后继续判断栈顶元素是否等于中序遍 历下标指向的元素，若相等则重复该操作，直至栈为空或者元素不相等。然后令当前元素为最后一个想等元素的右节点。
    遍历结束，返回根节点。
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size())
            return NULL;
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> record;
        record.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i)
        {
            TreeNode* node = record.top();
            int preVal = preorder[i];
            if (node->val != inorder[inorderIndex])
            {
                node->left = new TreeNode(preVal);
                record.push(node->left);
            }
            else
            {
                while (!record.empty() && record.top()->val == inorder[inorderIndex])
                {
                    node = record.top();
                    record.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preVal);
                record.push(node->right);
            }
        }
        return root;
    }
};
