#include <stdio.h>

// Fibonacci Numbers
int climbStairs(int n) {
        int pre = 0;
		int cur = 1; 
		int i=0;
		for(i = 1; i <= n; i++){
			int tmp = cur;
			cur += pre;
			pre = tmp;
		}
		
		return cur;
}

int main(){
	printf("%d\n", climbStairs(10));
	return 0;
}