#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define F first
#define S second
#define pb push_back
#define xout cout << "    "
#include "calc.h"
#include "derivitive.h"

int main()
{
    string f;
    while (1)
    {
        cout<<"    ";
        cin >> f;
        xout << fix(der(f)) << endl;
    }
}
