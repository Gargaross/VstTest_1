#include <iostream>
#include <thread>
#include <atomic>

using std::cout;
using std::string;
using std::endl;

struct TestStringStruct {
	string str1;
	string str2;
};

TestStringStruct testString = { "1", "2" };
const int cIterations = 1000;

void print(const string& str)
{
	cout << str.c_str() << endl;
}

void PrintValues()
{
	for (int i = 0; i < cIterations; i++) {
		cout << testString.str1.c_str() << testString.str2.c_str() << endl;
	}
}


void ChangeValues()
{
	for (int i = 0; i < cIterations; i++) {
		if (i % 2) {
			testString = { "3", "4" };
		}
		else {
			testString = { "1", "2" };
		}
	}
}


struct A {
	int a;
};

struct B {
	string a;
};


int main()
{
	std::thread first(PrintValues);
	std::thread second(ChangeValues);

	first.join();
	second.join();

	print("Joined the threads");

	cout << std::is_trivially_copyable<A>::value << endl;
	cout << std::is_trivially_copyable<B*> ::value << endl;

	return 0;
}