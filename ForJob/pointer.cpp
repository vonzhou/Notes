#include <iostream>
using namespace std;

int  main(int argc, char **argv){
	int *p1 = new int[10];
	int *p2 = new int[10]();

	cout << p1[0] << endl;
	cout << p2[0] << endl;

	p1[1] = 10;
	p2[2] = 9;

	cout << "hello" << endl;
}