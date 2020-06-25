//剑指 Offer 09. 用两个栈实现队列
//19点13分~19点20分
//two stack
//tail stack apend new value
//head stack delete value, when head stack is empty, dump all tail stack into head stack!
class CQueue {
public:
    CQueue() {

    }
    
    void appendTail(int value) {
	//O(1) time
        tail.push(value);
    }
    
    int deleteHead() {
	//O(1) time
        if (head.empty() && tail.empty())
            return -1;
        if (head.empty())
        {
            while (!tail.empty())
            {
                head.push(tail.top());
                tail.pop();
            }
        }
        int result = head.top();
        head.pop();
        return result;
    }
private:
    stack<int> tail;
    stack<int> head;
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
