#include <iostream>
#include <stdint.h> // uint32_t is in stdint.h header file

using namespace std;

int hammingWeight(uint32_t n) {
	int count = 0;
	for(int i=0; i<32; i++){
		uint32_t mask = 1 << i;
		// cout << "mask: " << mask << endl;
		// cout << (n & mask) << endl;
		if((n & mask) != 0) // bug: oprator priority != > &
			count ++;
	}   

	return count;
}

// O(m)  Each time of "n &= n - 1", we delete one '1' from n
int hammingWeight2(uint32_t n){
    int res = 0;
    while(n)    {
        n &= n - 1;
        ++ res;
    }
    return res;
}

int main(){
	uint32_t n = 11;
	cout << hammingWeight(n) << endl;

	return 0;
}