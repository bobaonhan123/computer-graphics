#include<iostream>

using namespace std;

int main() {
	int a=1,b=2;
	int &c=a;
	int &d=b;
	c=2;
	d=3;
	cout<<a<<" "<<b<<endl;
	return 0;
}
