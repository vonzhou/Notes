

//Given an array of integers, every element appears twice except for one. Find that single one.
// XOR them

 int singleNumber(vector<int>& nums) {
 	int res = 0;
 	for(int i=0; i<nums.size(); i++)
 		res ^= nums[i];

 	return res;
 }