//剑指 Offer 18. 删除链表的节点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//1. prev and cur
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
	//O(n) time, O(1) space
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* cur = head, *prev = dummy;
        while (cur)
        {
            if (cur->val == val)
            {
                prev->next = cur->next;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};

//2. cur
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
	//O(n) time, O(1) space
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* cur = dummy;
        while (cur->next)
        {
            if (cur->next->val == val)
            {
                cur->next = cur->next->next;
                break;
            }
            cur = cur->next;
        }
        return dummy->next;
    }
};
