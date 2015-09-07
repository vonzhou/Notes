#include <iostream>
using namespace std;

int i=0;

class Something{
private:
    const int a;
    int b;
    int c;
public:
    Something(): a(5),b(i++),c(i++){
    	c = 100;
    } 

    void show(){
    	cout << "a: " << a << ", b: " << b << ", c: " << c << endl;
    }
};

int main(){
	Something s;
	s.show();
	return 0;
}