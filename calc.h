#include <iostream>
using namespace std;
#include <vector>
#include <stack>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <float.h>
#define num double   //you can change num later to any variable type
num calculate1(string f);
num calculate2(string f);

bool belongTo(char c, string s) {//if the character belongs to the string
    for (char x : s)if (x == c)return true;
    return false;
}

map<string, num> variable={{"e",2.7182818284590452353602},{"pi",3.141592653589}};


num string_to_num(string f) {//modified stod
    if (f[0] >= 'a' && f[0] <= 'z' || f[0] >= 'A' && f[0] <= 'Z' || f[0] == '_') {
        return variable[f];
    }
    if (f[0] == '*' || f[0] == '/' || f[0] == '^') {
        f = f.substr(1, f.length() - 1);
    }
    if (f == "" || f == "+" || f == "-")f = "0";
    if (f[f.length() - 1] == 'n') {
        f = f.substr(0, f.length() - 1);
        return -stof(f);
    }
    return stod(f);//string to double
}
vector <pair<num, char>> vec;

num calculate1(string f) {//calculate a formula that contains only number , variables  ,operators and without brackets
    //make sure to not start with operator
    vec.clear();
    if (f[0] == '-' || f[0] == '+')f = '0' + f;
    else
        if (belongTo(f[0], "/*^"))f = '1' + f;

    int i = 0, j = 1,//the two pointers
        n = f.length()
        , m = 0;// length of vec (changes)

    // O(n) two pointers loop
    while (i + j - 1 <= n) {
        if (i + j - 1 == n) {//when loop ends
            vec.push_back({ string_to_num(f.substr(i,j - 1)),'+' });
            m++;
            break;
        }
        if (f[i + j - 1] >= '0' && f[i + j - 1] <= '9' || f[i + j - 1] == '.' || f[i + j - 1] >= 'a' && f[i + j - 1] <= 'z' || f[i + j - 1] >= 'A' && f[i + j - 1] <= 'Z' || f[i + j - 1] == '_')
        {
            j++;
        }
        else
            if (belongTo(f[i + j - 1], "+-*/^=")) {
                if (f.substr(i, j - 1) == "")
                {
                    j++;
                    continue;
                }

                vec.push_back({ string_to_num(f.substr(i,j - 1)),f[i + j - 1] });
                m++;
                i = i + j;
                j = 1;
            }
    }
    n = m;
    for (int i = n-2; i >=0; i--) {
        if (vec[i].second=='=') {
            vec[i].second = vec[i+1].second;
            vec[i].first = num(vec[i].first == vec[i + 1].first);
            vec[i + 1].second = 'd';
        }
    }

    for (int i = n - 2; i >= 0; i--) {// apply power first  x^y^z^w =x^(y^(z^w))
        if (vec[i].second == '^') {
            if (vec[i].first == 0 && vec[i + 1].first < 0)
                vec[i].first = DBL_MAX;
            else
                if (vec[i + 1].first == 0 && vec[i].first == 0)
                    vec[i].first = 1;
                else
                    vec[i].first = pow(vec[i].first, vec[i + 1].first);

            vec[i].second = vec[i + 1].second;
            vec.erase(vec.begin()+i + 1); n--;
        }
    }

    for (int i = 1; i < n; i++) {
        if (vec[i - 1].second == '/') {//apply divistion  x , / , y   =>  x/y , * , 1     //   1/x/y = 1/(x*y)
            vec[i - 1].second = '*';
            if (vec[i].first != 0)
                vec[i].first = 1 / vec[i].first;
            else
                vec[i].first = DBL_MAX;
        }
        if (vec[i - 1].second == '-') {//apply subtraction  x , - , y =>  x , + , -y
            vec[i - 1].second = '+';
            vec[i].first = -vec[i].first;
        }
    }
    bool got = 0;
    j = 0;
    num res = 0;
    for (int i = 0; i < n; i++) {//lastly multibly and add
        if (vec[i].second == '*' && !got) {
            j = i;
            got = 1;
            continue;
        }
        else
            if (vec[i].second == '+' && !got)
                res += vec[i].first;

        if (vec[i].second != 'd' && got) {
            vec[j].first *= vec[i].first;
            if (vec[i].second != '*')
                got = 0, res += vec[j].first;;
            vec[i].second = 'd';
        }
    }
    vec.clear();
    return res;
}
vector<num> parameter;
num applyFunction(string f, string x) {// f is function name   // x is everything inside brackets
    parameter.clear();
    x += ',';
    int i = 0, j = 1, n = x.length();
    //two pointers
    while (i + j - 1 < n) {
        if (x[i + j - 1] == ',') {
            parameter.push_back(calculate1(x.substr(i, j - 1)));
            i += j;
            j = 1;
        }
        else { j++; }
    }
    n = parameter.size();
    if (n < 1)return 0;//there are no parameters
    if (f == "")
        return parameter[0];
    if (f == "pow") {
        if (n < 2)return parameter[0];
        return pow(parameter[0], parameter[1]);
    }
    if (f == "sin") {
        return sin(parameter[0]);
    }
    if (f == "cos") {
        return cos(parameter[0]);
    }
    if (f == "tan") {
        return tan(parameter[0]);
    }
    if (f == "cot") {
        return 1 / tan(parameter[0]);
    }
    if (f == "asin") {
        return asin(parameter[0]);
    }
    if (f == "acos") {
        return acos(parameter[0]);
    }
    if (f == "ln")
    {
        return log(parameter[0]);
    }
    if (f == "log") {
        if (n < 2)return log(parameter[0]) / log(10);
        return log(parameter[0]) / log(parameter[1]);
    }
    if (f == "abs") {
        return abs(parameter[0]);
    }
    if (f == "floor")
        return floor(parameter[0]);
    if (f == "ceil")
        return ceil(parameter[0]);
    if (f == "round")
        return round(parameter[0]);
    if (f == "sqrt") {
        return sqrt(parameter[0]);
    }
    if (f == "cubrt") {
        if (parameter[0] < 0)return -pow(-parameter[0], 1.0 / 3);
        return pow(parameter[0], 1.0 / 3);
    }
    if (f == "s") {
        if (n < 2)return parameter[0] - floor(parameter[0]);
        if (parameter[1] == 0)return parameter[0];
        return parameter[0] - parameter[1] * floor(parameter[0] / parameter[1]);
    }
    return 0;//any non defined function simply returns 0
}

num calculate2(string f) {//calculate with brackets
    stack<int> brace;// bracket index  '('
    stack<int> Func;//function name start index
    string get;
    int n = f.length(), j;
    for (int i = 0; i < n; i++) {
        if (f[i] == '(') {
            brace.push(i);
            j = i - 1;
            while (j >= 0 && (f[j] >= 'a' && f[j] <= 'z' || f[j] >= 'A' && f[j] <= 'Z')) {
                j--;
            }
            j++;
            Func.push(j);
        }
        if (f[i] == ')') {
            get = f.substr(Func.top(), brace.top() - 1 - (Func.top()) + 1);
            get = to_string(applyFunction(get, f.substr(brace.top() + 1, (i - 1 - (brace.top() + 1) + 1))));
            if (get[0] == '-') {
            get=get.substr(1,get.length()-1)+'n';
            }
            j = Func.top() + get.length() - 1;
            get = f.substr(0, Func.top()) + get + f.substr(i + 1, n - (i + 1));
            i = j;
            f = get;
            n = f.length();
            brace.pop();
            Func.pop();
        }
    }
    return calculate1(f);
}

num calc(string f,float x=5){
    variable["x"]=x;
    return calculate2(f);
}
