#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    string binaryString(int p){
        // string s = 
        return "";
    }
    vector<int> grayCode(int n) {

        vector<int> out = {0}; //  error: in C++98 ‘out’ must be initialized by constructor, not by ‘{...}’

        for (int i = 0; i < n ; ++i)
        {
            int p = 1<<i;
            int s = out.size();
            cout << "========" << i << endl;
            while (s)
            {
                int v = p | out[--s];
                cout <<bitset<10>(p).to_string()  << "," << bitset<10>(v).to_string() <<endl;
                out.push_back(v);
            }
        }

        return out;
    }
};

int main(){
    Solution s;
    std::vector<int> v = s.grayCode(4);
    int len = v.size();
    for(int i=0; i<len;i++)
        cout << v[i] << " ";
    cout << endl;

    return 0;
}