#include <iostream>

using namespace std;

void prim(int m, int n){
	if(m >= n){
		while(m % n)
			n++;
		m /= n;
		cout <<"before " <<  m << endl;
		prim(m, n);
		cout << n << endl;
	}
	//cout << m << endl;
}


int main(){
	prim(56, 2);
	return 0;
}