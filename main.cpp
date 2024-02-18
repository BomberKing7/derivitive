#include "calc.h"
#include <iostream>
#include <iomanip>
#include "derivitive.h"
using namespace std;
//bug cos(x)^sin(x^2)^ln(x)


int main(int argc,char* argv[]) {
	string s="cos(x)^sin(x^2)^ln(x)";
	int c1=0,c2=0;
	cout<<fix(der(s));
	
}