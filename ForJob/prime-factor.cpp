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
}


int main(){
	prim(36, 2);
	return 0;
}