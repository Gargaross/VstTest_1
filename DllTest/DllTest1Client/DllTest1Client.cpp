// DllTest1Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "DllTest1.h"


int main()
{
	int a = 2;
	int b = 3;
	int c = add_int(a, b);

	std::cout << a << " + " << b << " = " << c << std::endl;

	return 0;
}
