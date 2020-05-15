//4. Median of Two Sorted Arrays
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //O(log(min(n,m)))
        int n = nums1.size();
        int m = nums2.size();
        if (n > m)
        {
            return findMedianSortedArrays(nums2, nums1);
        }
        int l = 0, r = n;
        while(l <= r)
        {
            int posn = (l+r)/2;
            int posm = (n+m+1)/2 - posn;
            
            int nleft = posn == 0 ? INT_MIN : nums1[posn-1];
            int nright = posn == n ? INT_MAX : nums1[posn];
            
            int mleft = posm == 0 ? INT_MIN : nums2[posm-1];
            int mright = posm == m ? INT_MAX : nums2[posm];
            
            if (nleft <= mright && mleft <= nright)
            {
                if ((m+n)%2)
                    return (double)max(nleft,mleft);
                else
                    return (max(nleft,mleft) + min(nright, mright) )/ 2.0;
            }
            else if (nleft > mright)
                r = posn - 1;
            else
                l = posn + 1;
        }
        throw 0.0;
    }
};
