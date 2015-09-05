#include <stdio.h>
#include <stdlib.h>

/* get distinct and random *m* numbers from 1~n
 */
void knuth(int n, int m){
	srand((unsigned int)time(0));
	int i=0;
	for( i=0; i<n; i++){
		int r = rand() % (n-i) ;
		//printf("trace : %d\n", r);
		if(r < m){
			printf("%d\n", i);
			m--;
		}
		// else{
		// 	printf("NO\n");
		// }
	}
}

/********************** 2 ************************/
int alreadyExist(int r, int *p, int bound){
	int i=0;
	for(i=0; i<bound; i++){
		if(p[i] == r)
			return 1;
	}
	return 0;
}

void method1(int n, int m){
	int result[m];
	int i=0;
	for(i=0; i<m; i++){
		int r;
		do{
			r = rand() % n;
		}while(alreadyExist(r, result, i));

		result[i] = r;
	}
	for(i=0; i<m ;i++)
		printf("%d\n", result[i]);
}

/****************** 3 **********************/
void shuffle(int *p, int *pEnd){
	// TODO
}
void method2(int n, int m){
	int arr[n];
	int i=0;
	for(i=0; i<n; i++){
		arr[i] = i;
	}

	shuffle(arr,arr+n);

	// just get first m elements in arr
	for(i=0; i<m ;i++)
		printf("%d\n", arr[i]);
}


int main(){
	//knuth(10, 5);
	method1(10, 5);
	return 0;
}