//849. Maximize Distance to Closest Person
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        //case1: [1...1], n count zero in mid, distance (n+1)/2
        //case2: [0...1], n count zero in mid, distance n
        //case3: [1...0], same as case2, but when end iterate must one more compare!
        //O(n) time, O(1) space
        bool leftOne = false;
        int distance = 0, max_distance = 0;
        for (int i = 0; i < seats.size(); ++i)
        {
            if (seats[i] == 0)
            {
                ++distance;
            }
            else
            {
                if (leftOne)
                    max_distance = max(max_distance, (distance+1)/2);
                else
                    max_distance = max(max_distance, distance);
                leftOne = true;
                distance = 0;
            }
        }
        max_distance = max(max_distance, distance);        
        return max_distance;
    }
};
