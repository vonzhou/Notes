#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
//Given an array of integers, find if the array contains any duplicates. 
//Your function should return true if any value appears at least twice in the array, 
// and it should return false if every element is distinct.

// quite nice example of space-time tradeoff.

// 1. sort and compare neigbors -- O(NlogN)
bool containsDuplicate(vector<int>& nums) {
	if(nums.size() < 2)
		return false;

	sort(nums.begin(), nums.end());
	for(int i=1; i<nums.size(); i++)
		if(nums[i] == nums[i-1])
			return true;


	return false;
}

// 2. use a set, and see its size change smaller
bool containsDuplicate2(vector<int>& nums) {
	if(nums.size() < 2)
		return false;

	set<int> s;
	for(int i=0; i<nums.size(); i++)
		s.insert(nums[i]);

	if(nums.size() > s.size())
		return true;

	return false;
}

//The naive approach would be to run a iteration for each element 
// and see whether a duplicate value can be found: this results in O(N^2) time complexity.
// 3. Cannot AC ,  Time Limit Exceeded
bool containsDuplicate3(vector<int>& nums){
	 for(int i = 0; i < nums.size(); i++) {
            for(int j = i + 1; j < nums.size(); j++) {
                if(nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
}




int main(){

	vector<int> v = {3, 8, 34, 1, 3, 5, 7};
	cout << containsDuplicate(v) << endl;
	cout << containsDuplicate2(v) << endl;

	return 0;
}