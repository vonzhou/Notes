#include <stdio.h>
#include <stdlib.h>

int maxF(int a, int b){
	if(a > b)
		return a;
	return b;
}

//1. O(n) Simple 
int maxSubArray1(int* nums, int numsSize) {
    if(numsSize > 0){
    	int preSum = nums[0];
		int max = nums[0];
		int i = 0;
		for(i = 1; i < numsSize; i++){
			preSum = maxF(nums[i], preSum + nums[i]);  // update the sub
			max = maxF(max, preSum);
		}
 		return max;
    }
}

// 2. state transform condition: sum[i] = max{sum[i-1] + A[i], A[i]}
int maxSubArray2(int* nums, int numsSize) {
	if(numsSize > 0){
		int max = nums[0];
		//int sum[] = int[numsSize];
		int *sum = malloc(numsSize * sizeof(int));
		sum[0] = nums[0];
		int i = 0;
		for(i=1; i<numsSize; i++){
			sum[i] = maxF(sum[i-1] + nums[i], nums[i]);
			max = maxF(max, sum[i]);
		}

		free(sum);
		return max;
	}
}

int main(){
	int arr[] = {1,2};
	printf("%d\n", maxSubArray1(arr, 2));
	printf("%d\n", maxSubArray2(arr, 2));
	return 0;
}