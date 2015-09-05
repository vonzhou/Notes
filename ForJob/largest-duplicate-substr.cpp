#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;

const int MAXLINE = 5000;

bool strCompare(char *str1, char *str2);
int getCommonPrefixLen(char *str1, char *str2);
void getSuffixStrArr(char *src, char *suffixStrArr[]);
void getLargestDuplicateSubstr(char *str);

int main(){
	char str[MAXLINE];
	cin.getline(str, MAXLINE);
	getLargestDuplicateSubstr(str);
	return 0;
}

void getLargestDuplicateSubstr(char *str){
	int len = strlen(str);
	char *suffixStr[MAXLINE];
	int commonPrefixLen;
	int maxLen = 0;
	int maxIndex = -1;

	getSuffixStrArr(str, suffixStr);

	sort(suffixStr, suffixStr+len, strCompare);

	for(int i=0; i<len-1; i++){
		commonPrefixLen = getCommonPrefixLen(suffixStr[i], suffixStr[i+1]);

		if(commonPrefixLen > maxLen){
			maxLen = commonPrefixLen;
			maxIndex = i;
		}
	}

	for(int i=0; i<maxLen; i++){
		cout << suffixStr[maxIndex][i];
	}
	cout << endl;
}

void getSuffixStrArr(char *src, char *suffixStrArr[]){
	int len = strlen(src);
	for(int i=0; i<len; i++)
		suffixStrArr[i] = &src[i];
}

int getCommonPrefixLen(char *str1, char *str2){
	int len = 0;
	while(*str1 && *str2){
		if(*str1 == *str2)
			len ++;
		else break;

		str1 ++;
		str2 ++;
	}
	

	return len;
}

// string ascending order  - O(N)
bool strCompare(char *str1, char *str2){
	if(strcmp(str1, str2) >= 0)
		return false;
	return true;
}