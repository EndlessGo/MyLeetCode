//剑指 Offer 22. 链表中倒数第k个节点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//1.考虑越界
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head, *slow = head;
        for (int i = 1; i <= k; ++i)
        {
            if (fast)
                fast = fast->next;
            else
                return NULL;
        }
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
//2.不考虑越界
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = head, *slow = head;
        int step = 0;
        while (fast)
        {
            if (step >= k)
                slow = slow->next;            
            fast = fast->next;
            ++step;
        }
        return slow;
    }
};
