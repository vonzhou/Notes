#include <iostream>

using namespace std;


// 1. recursive 
int addDigits(int num) {
	if(num >= 0){
		if(num < 10)
			return num;

		int sum = 0;
		while(num > 0){
			sum += (num % 10);
			num /= 10;
		}

		addDigits(sum);
	}
}

// A naive implementation of the above process is trivial. Could you come up with other methods?
// What are all the possible results?
// How do they occur, periodically or randomly? 
// https://en.wikipedia.org/wiki/Digital_root    
// 2. Congrunce formula
int addDigits(int num) {
	if(num >= 0){
		return 1 + (num - 1) % 9;
	}
}

int main(){
	cout << addDigits(38) << endl;
	return 0;
}