#include <iostream>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class AbsClass {
	// Private section
	public:
		virtual int GetMoney()= 0;

};

class DerivedClass: public AbsClass {
	int inside;
	// Private section
	public:
		DerivedClass(int stock) {
			inside = stock;
		}
	int GetMoney() {
		return inside;
	}
};


int main(int argc, char** argv) {
	DerivedClass * a;
	a = new DerivedClass(3556);
	cout << a->GetMoney();
	
	return 0;
}
