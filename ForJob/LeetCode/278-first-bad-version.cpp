#include <iostream>


// a range is Bad, so need to find the left most of this range
// a sorted arr, search sequncially or binary search.

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
	//1.  Not AC , Time Limit Exceeded
    int firstBadVersion1(int n) {
    	if(!isBadVersion(n)) // last is not , there is no
    		return -1;
    	for(int i=1; i<= n; i++)
    		if(isBadVersion(i))
    			return i;
        
    }
    // 2. 
    int firstBadVersion(int n) {
    	if(!isBadVersion(n)) // last is not , there is no
    		return -1;

    	int left=1, right=n;
    	while(left < right){
    		int mid = left + (right-left)/2;
    		if(isBadVersion(mid))
    			right = mid; // need the smallest bad
    		else left = mid+1;  // the bad is on the right
    	}

    	return isBadVersion(left) ? left : right;
    }
};



int main(){
	return 0;
}