#include <iostream>
#include <string>
#include <vector>

using namespace std;

//=============================================== 1
// get all the sub strings of a string  -- O(N^2)
vector<string> subStrings(string s){
	vector<string> res;
	if(s.empty())
		return res;
	int len = s.size();
	for(int i=0; i<len; i++){
		for(int j=0; j<=i; j++){
			string sub = s.substr(j, i-j+1);
			// cout << sub << endl;
			res.push_back(sub);
		}
	}

	return res;
}

// O(N)
bool isPalindromic(string s){
	if(!s.empty()){
		int i=0, j=s.size() - 1;
		while(i<=j){
			if(s[i] == s[j]){
				i++;
				j--;
			}
			else break;
		}
		if(i > j)
			return true;
		else return false;
	}
}

//1. brute force  -- O(N^3), Not AC , Time Limit Exceeded
string longestPalindrome(string s) {
	if(s.empty() || s.size() <= 1)
		return s;

	vector<string> subs = subStrings(s);
	int max = 0;
	string res = "";
	for(int i=0; i<subs.size(); i++){
		string t = subs[i];
		if(isPalindromic(t)){
			if(t.size() > max){
				max = t.size();
				res = t;
			}
		}
	}

	return res;
}

// =================================================================
// 2. O(N^2) , AC
// use every char as pivot, and expand it left and right 
// NB. the length of result can be even or odd
string longestPalindrome2(string s) {
    if (s.empty()) 
    	return "";
    if (s.size() == 1) 
    	return s;

    int max = 0;
    int pivot = 0;
    int subLen = 0;
    int n = s.size();
    for(int i=0; i<n; i++){
    	for(int j=0; i-j>=0 && i+j<n; j++){
    		if(s[i-j] != s[i+j])
    			break;
    		subLen = 2 * j + 1;// expand
    	}

    	if(subLen > max ){
    		max = subLen;
    		pivot = i;
    	}
    		

    	for(int j=0; i-j>=0 && i+j+1<n; j++){
    		if(s[i-j] != s[i+j+1])
    			break;
    		subLen = 2 * j + 2;
    	}

    	if(subLen > max ){
    		max = subLen;
    		pivot = i;
    	}

    }
    cout << max << "," << pivot << endl;
    string res = "";
    if(max % 2 != 0){
    	res  = s.substr(pivot - max/2, max);
    }else{
    	res = s.substr(pivot-(max/2-1), max);
    }
    return res;
}



// =================================================================
//3. Manacher's Alg.  TODO  O(N)








// =================================================================
// https://leetcode.com/discuss/32204/simple-c-solution-8ms-13-lines
string longestPalindrome3(string s) {
    if (s.empty()) 
    	return "";
    if (s.size() == 1) 
    	return s;
    int min_start = 0, max_len = 1;
    for (int i = 0; i < s.size();) {
      	if (s.size() - i <= max_len / 2) 
      	break;
      	int j = i, k = i;
      	while (k < s.size()-1 && s[k+1] == s[k]) 
      		++k; // Skip duplicate characters.

      	i = k+1;
      	while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) {
       		++k; --j; 
       	} // Expand.
      	int new_len = k - j + 1;
      	if (new_len > max_len) { min_start = j; max_len = new_len; }
    }

    return s.substr(min_start, max_len);
}

int main(){
	// subStrings("abc");
	// cout << isPalindromic("a") << endl;
	// cout << longestPalindrome("abbac") << endl;
	cout << longestPalindrome2("12abcba") << endl;
	cout << longestPalindrome2("3abba") << endl;
	return 0;
}