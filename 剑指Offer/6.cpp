//剑指 Offer 06. 从尾到头打印链表
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> temp;
        while (head)
        {
            temp.push(head->val);
            head = head->next;
        }
        vector<int> result;
        while (!temp.empty())
        {
            result.push_back(temp.top());
            temp.pop();
        }
        return result;
    }
};
