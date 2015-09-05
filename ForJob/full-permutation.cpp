#include <iostream>
#include <algorithm> // std::copy
#include <iterator> // ostream_iterator

using namespace std;

void swap(int *p1, int *p2){
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void perm(int list[], int k, int m){
	if(k == m){
		copy(list, list+m, ostream_iterator<int>(cout, " "));
		cout << endl;
		return;
	}

	for(int i=k; i<=m; i++){
		swap(&list[k], &list[i]);
		perm(list, k+1, m);
		swap(&list[k], &list[i]);
	}
}

int main(){
	int list[] = {1,2,3,4};
	perm(list, 0, 3);
	return 0;
}