//剑指 Offer 25. 合并两个排序的链表
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//1.迭代
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //O(m+n) time, O(1) space
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        while (l1 || l2)
        {
            if (!l1)
            {
                cur->next = l2;
                break;
            }
            if (!l2)
            {
                cur->next = l1;
                break;
            }                            
            if (l1->val <= l2->val)
            {
                cur->next = l1;
                l1 = l1->next;
            }
            else
            {
                cur->next = l2;                
                l2 = l2->next;
            }
            cur = cur->next;
        }
        return dummy->next;
    }
};
//2.递归
class Solution {
public:
    //返回合并后的头节点
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //O(n+n) time, O(m+n) space
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode* head = NULL;    
        if (l1->val <= l2->val)
        {
            head = l1;
            head->next = mergeTwoLists(l1->next,l2);
        }
        else
        {
            head = l2;
            head->next = mergeTwoLists(l1,l2->next);
        }
        return head;
    }
};
