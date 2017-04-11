**解题思路：**  
判断两个列表是否都为空；然后依次按照顺序（升序）添加到新列表；一个列表添加完成后，直接将另一列表剩余结点添加到新列表即可。  
Tags : Linked List  
**1.第一次提交：**

	class Solution {
	public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
    {
        if(l1->next == NULL && l2->next == NULL)
            return l1;
        ListNode* L = new ListNode(0);
        ListNode* l = L;
        while(l1->next != NULL && l2->next != NULL)
        {
            if(l1->val <= l2->val)
            {
                l->val = l1->val;
                l->next = l1;
                l1 = l1->next;
            }
            else
            {
                l->val = l2->val;
                l->next = l2;
                l2 = l2->next;
            }
        }
        if(l1->next == NULL)
        {
            while(l2->next != NULL)
            {
                l->val = l2->val;
                l->next = l2;
                l2 = l2->next;
            }
        }
        if(l2->next == NULL)
        {
            while(l1->next != NULL)
            {
                l->val = l1->val;
                l->next = l1;
                l1 = l1->next;
            }
        }
        return L;
    }
	};  
**错误：member access within null pointer of type 'struct ListNode'**。  
**分析：**  
对于`l1->next == NULL 和 l2->next == NULL`的->next操作都是非法的！若没有结点，l1本身是NULL了，应该不存在next成员。  

**2.第二次提交：**  
还是有`Line 48: member access within null pointer of type 'struct ListNode'`
**分析：**对于l的操作有不合理的！  

**3.第三次提交：**  
出错：Input:[1][] Output:[0] Expected:[1]  
**分析：**  
对于l1，l2的判断不全面：`if(l1 == NULL && l2 == NULL)`和`while(l1 != NULL && l2 != NULL)`未能将l1和l2中一个列表为空的情况包含！  

**4.第四次提交：**  
出错：Input:[1][2] Output:[0] Expected:[1,2]  
**分析：**  
删除`ListNode* L = new ListNode(0);ListNode* l = L;`，改为`ListNode* l = NULL;`并`return l;`  

**5.第五次提交：**  
加入头结点后并修改指针指向后通过。  
  
	class Solution {
	public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
    {
        if(l1 == NULL)
            return l2;
        if(l2 == NULL)
            return l1;
        ListNode* head = NULL;
        if(l1->val <= l2->val){head = l1;l1 = l1->next;}
        else{head = l2;l2 = l2->next;}
        
        ListNode* l = head;
        while(l1 != NULL && l2 != NULL)
        {
            if(l1->val <= l2->val)
            {
                l->next = l1;
                l1 = l1->next;
            }
            else
            {
                l->next = l2;
                l2 = l2->next;
            }
            l = l->next;
        }
        if(l1 == NULL)
        {
            while(l2 != NULL)
            {
                l->next = l2;
                l2 = l2->next;
                l = l->next;
            }
        }
        if(l2 == NULL)
        {
            while(l1 != NULL)
            {
                l->next = l1;
                l1 = l1->next;
                l = l->next;
            }
        }
        return head;
    }
};  
**6.别人家的代码一：**  
使用head保存第一个节点。
      
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    
    if(NULL == l1) return l2;
    if(NULL == l2) return l1;
    
    ListNode* head=NULL;    // head of the list to return
    
    // find first element (can use dummy node to put this part inside of the loop)
    if(l1->val < l2->val)       { head = l1; l1 = l1->next; }
    else                        { head = l2; l2 = l2->next; }
    
    ListNode* p = head;     // pointer to form new list
    
    // I use && to remove extra IF from the loop
    while(l1 && l2){
        if(l1->val < l2->val)   { p->next = l1; l1 = l1->next; }
        else                    { p->next = l2; l2 = l2->next; }
        p=p->next;
    }
    
    // add the rest of the tail, done!一个列表截止，另外一个列表直接添加到合并的列表
    if(l1)  p->next=l1;
    else    p->next=l2;
    
    return head;
	}
**简洁性：**  
体会循环`while(l1 && l2)`和条件`if(l1)  p->next=l1;   else    p->next=l2;`的精炼和简单！ 
 
**7.别人家的代码二：**  
使用了头结点dummy，技巧：返回dummy->next。对于一个列表截止，另外一个列表直接添加到合并的列表的更简单的等效表达：`tail->next = l1 ? l1 : l2;`等同于6中的`if(l1)  p->next=l1;   else    p->next=l2;`。  

	class Solution {
	public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode dummy(INT_MIN);
        ListNode *tail = &dummy;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        //赋值tail->next=(l1?l1:l2),l1=NULL则tail->next=l2;
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
	};
