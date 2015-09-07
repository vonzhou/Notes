#include <iostream>

using namespace std;


// 1. left right digit compare 
bool isPalindrome(int x) {
   	if(x < 0 )
			return false;
		int divisor = 1;
		while(x / divisor >= 10)
			divisor *= 10;
		//System.out.println(divisor);
		
		while(x != 0){ 
			int left = x / divisor;
			int right = x % 10;
			if(left != right) return false;
			// 舍去最高最低数位
			x = (x % divisor) / 10;
			divisor /= 100;
		}
        return true;     
} 

//2. construct the symmetric half number, and see if they equal
// just traverse half length of the integer !
// 12321 - > 12 + 123
// 2222 -> 22 + 22
//https://leetcode.com/discuss/33500/an-easy-lines-code-only-reversing-till-half-and-then-compare
bool isPalindrome2(int x) {
    if(x<0 || (x!=0 && x%10 == 0)) 
    	return false;
    int sum=0;
    while(x>sum) {
        sum = sum*10 + x%10;
        x = x/10;
        cout << sum << "--" << x << endl;
    }
    return (x==sum)||(x==sum/10);
}

int main(){
	cout << isPalindrome2(61616) << endl;
	cout << isPalindrome2(22) << endl;
	return 0;
}