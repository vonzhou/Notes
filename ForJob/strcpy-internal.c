#include <stdio.h>
#include <string.h>

// wrong case 
void test(){
	int a = 100;
	char str2[10];
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	char *s = "hello world !";
	int i=0;
	for(i=0; i<10; i++)
		str1[i] = 'a';

	strcpy(str2, str1);
	printf("str1 addr: %p, pad addr : %p, str2 addr:%p \n", str1, pad, str2);
	printf("%s\n", str2);
}

char * mystrcpy(char *dest, const char *src){
	if(src == NULL || dest == NULL){
		printf("%s\n", "Error!");
		return NULL;
	}

	char *addr = dest;
	while((*dest++ = *src++) != '\0');

	return dest;
}

void test2(){
	int a = 100;
	char str2[10];
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	char *s = "hello world !";
	int i=0;
	for(i=0; i<10; i++)
		str1[i] = 'a';

	mystrcpy(str2, str1);
	printf("str1 addr: %p, pad addr : %p, str2 addr:%p \n", str1, pad, str2);
	printf("str2 : %s\n", str2);
	printf("str1 : %s\n", str1);
}

void test3(){
	char str2[5];
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	char *s = "hello world !";
	int i=0;
	for(i=0; i<9; i++)
		str1[i] = 'a';
	str1[9] = '\0';

	printf("str1 addr: %p, str2 addr:%p \n", str1, str2);
	printf("str2 : %s\n", str2);
	printf("str1 : %s\n", str1);
	printf("pad : %s\n", pad);

	printf("%s\n", "after strcpy():");
	strcpy(str2, str1);
	// mystrcpy(str2, str1);
	
	printf("str2 : %s\n", str2);
	printf("str1 : %s\n", str1);
	printf("pad : %s\n", pad);
}

void test3_2(){
	char str2[5];
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	char *s = "hello world !";
	int i=0;
	for(i=0; i<9; i++)
		str1[i] = 'a';
	str1[9] = '\0';

	printf("str1 addr: %p, str2 addr:%p \n", str1, str2);
	printf("str2 : %s\n", str2);
	printf("str1 : %s\n", str1);
	printf("pad : %s\n", pad);

	printf("%s\n", "after strcpy():");
	mystrcpy(str2, str1);
	
	printf("str2 : %s\n", str2);
	printf("str1 : %s\n", str1);
	printf("pad : %s\n", pad);
}

void test4(){
	char *str2;
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	int i=0;
	for(i=0; i<9; i++)
		str1[i] = 'a';
	str1[9] = '\0';

	strcpy(str2, str1);
}

void test4_2(){
	char *str2 ;
	char pad[100] = "xxxxx"; // 5
	char str1[10];
	int i=0;
	for(i=0; i<9; i++)
		str1[i] = 'a';
	str1[9] = '\0';

	printf("str2 addr : %p\n", str2);
	mystrcpy(str2, str1);
}

int main(){
	// test3();
	// printf("--------\n");
	// test3_2();
	//test4();
	//printf("--------\n");
	test4_2();
	//test4();

	return 0;
}