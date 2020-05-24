//146. LRU Cache
class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        //cout<<"get "<<key<<endl;
        auto iter = pos_map.find(key);
        if (iter == pos_map.end())
        {
            return -1;
        }
        int value = iter->second->second;
        cache.erase(iter->second);
        cache.push_front(pair<int,int>(key, value));
        pos_map[key] = cache.begin();
        //cout<<"get "<<key<<":"<<value<<endl;
        return value;
    }
    
    void put(int key, int value) {
        //cout<<"put "<<key<<":"<<value<<endl;
        auto iter = pos_map.find(key);
        if (iter != pos_map.end())
        {
            cache.erase(iter->second);
            cache.push_front(pair<int,int>(key, value));
            pos_map[key] = cache.begin();
        }
        else
        {
            if (cache.size() >= cap)
            {
                pos_map.erase(cache.back().first);
                cache.pop_back();                
            }
            cache.push_front(pair<int,int>(key, value));
            pos_map[key] = cache.begin();
        }
        return;
    }
private:
    list<pair<int,int>> cache;//head is recent
    typedef list<pair<int,int>>::iterator Pos;
    unordered_map<int, Pos> pos_map;
    int cap;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
