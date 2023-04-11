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
// bug  -(-2*x*x/(x^2))+(-x/x^2)
int main()
{
    string f;
    while (1)
    {
        cout<<"  >>";
        cin >> f;
        xout <<der(f)<<endl;;cout<<"\n\t"<< fix(f);
        cout<<"\n\t" <<fix(der(f))<< endl<<endl;
    }
}
