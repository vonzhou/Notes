#include <iostream>
using namespace std;

int main(){

	int *a = new int(10);
	int *b = new int[2];

	cout << *a << "," << b[0] << endl;

	return 0;
}