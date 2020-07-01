//剑指 Offer 24. 反转链表
//1. 迭代
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
    ListNode* reverseList(ListNode* head) {
        //O(n) time, O(1) space
        ListNode *cur = head, *prev = NULL;
        while (cur)
        {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};
//2.1 递归1
class Solution {
public:
    //返回反转链表后的尾节点
    ListNode* reverseList(ListNode* head) {
        //O(n) time, O(n) space
        if (!head) return NULL;
        ListNode* new_head = NULL, *tail = NULL;
        tail = reverseList(head, new_head);
        tail->next = NULL;
        return new_head;
    }
    ListNode* reverseList(ListNode* cur, ListNode*& head) {    
        if (!cur->next)
        {
            head = cur;
            return cur;
        }
        ListNode* tail = reverseList(cur->next, head);
        tail->next = cur;
        return cur;
    }
};
//2.2 递归2
class Solution {
public:
    //返回反转链表后的头节点
    ListNode* reverseList(ListNode* head) {
        //O(n) time, O(n) space
        if (!head || !head->next) return head;
        ListNode* ret = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return ret;
    }
};
