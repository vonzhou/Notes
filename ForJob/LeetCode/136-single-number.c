#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    if(numsSize > 0){
    	int i=0;
    	int res = nums[0];
    	for(i=1; i<numsSize; i++){
    		res ^= nums[i];
    	}

    	return res;
    }
}

int main(){
	int arr[] = {1,2,2,1,3,4,4};
	printf("%d\n", singleNumber(arr, 7));
}