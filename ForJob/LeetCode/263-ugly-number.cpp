#include <iostream>
#include <vector>

using namespace std;


// 1. what i think: factor this num to prime's and to see if only contain 2,3,5
// But Not AC , Time Limit Exceeded , Last executed input: 905391974


// get prime factors of m 
vector<int> prim(int m, int n){
	vector<int> res;
	// cout << m << "--" << n << endl;
	if(m >= n){
		while(m % n)
			n++;
		m /= n;
		// cout <<"before " <<  m << endl;
		vector<int> temp = prim(m, n);
		// cout << n << endl;
		res.insert(res.end(), temp.begin(), temp.end());
		res.push_back(n);
	}

	return res;
}

bool isUgly(vector<int> v){
	for(int i=0; i<v.size(); i++){
		int x = v[i];
		cout <<i << "= " <<  x << endl;
		if(x != 2 && x != 3 && x != 5)
			return false;
	}
		

	return true;
}

bool isUgly(int num) {
	if(num == 1)
		return true;

	vector<int> res = prim(num, 2);

	return isUgly(res);
}


// 2. Just divide by 2, 3 and 5 as often as possible and then check whether we arrived at 1. 
// Also try divisor 4 if that makes the code simpler / less repetitive.
bool isUgly2(int num) {
	if(num > 0){
		for(int i=2; i<6; i++)
			while(num%i == 0)
				num /= i;

		return num == 1;
	}
	return false;
}

int main(){
	bool is = isUgly(3);
	cout << (is ? "IS" : "NO") << endl;
}