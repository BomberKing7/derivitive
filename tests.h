#include "all_includes.h"
bool isLetter(char x)
{
    return (x >= 'a' && x <= 'z') ||
           (x >= 'A' && x <= 'Z') ||
           x == '_';
}
bool isDigit(char x)
{
    return x >= '0' && x <= '9';
}
bool isBraced(string f)//O(n)
{
    if (f[0] != '(' || f[f.length() - 1] != ')')
        return 0;
    int b = 0, n = f.length();
    for (int i = 0; i < n; i++)
    {
        if (f[i] == '(')
            b++;
        if (f[i] == ')')
            b--;
        if (b == 0 && i != n - 1)
            return 0;
    }
    return 1;
}
bool isConst(string f)//O(n)
{
    f = '(' + f + ')';
    int n = f.length();
    for (int i = 1; i < n - 1; i++)
    {
        if (f[i] == 'x' && !isLetter(f[i - 1])
                &&!isLetter(f[i+1])
                &&!isDigit(f[i-1])
                &&!isDigit(f[i+1]))
            return 0;
    }
    return 1;
}
bool isAdd(string f)//O(n)
{
    int b = 0, n = f.length();
    for (int i = 0; i < n; i++)
    {
        if (f[i] == '(')
            b++;
        if (f[i] == ')')
            b--;
        if ((f[i] == '+' || f[i] == '-') && b == 0)
            return 1;
    }
    return 0;
}
bool isMull(string f){
    int b = 0, n = f.length();
    if(isAdd(f))return 0;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == '(')
            b++;
        if (f[i] == ')')
            b--;
        if ((f[i] == '*' || f[i] == '/') && b == 0)
            return 1;
    }
    return 0;
}
bool isPower(string f)//O(n)
{
    int b = 0, n = f.length();
    bool res = 0;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == '(')
            b++;
        if (f[i] == ')')
            b--;
        if ((f[i] == '+' || f[i] == '-' || f[i] == '*' || f[i] == '/') && b == 0)
            return 0;
        if (f[i] == '^' && b == 0)
            res = 1;
    }
    return res;
}
bool isNamedFunction(string f)//O(n)
{
    if (!isLetter(f[0]))
        return 0;
    int i = 1, n = f.length();
    while (i < n && f[i] != '(')
    {
        if (!(isLetter(f[i]) || isDigit(f[i])))
            return 0;
        i++;
    }
    if (i == n)
        return 0;
    int b = 0;
    while (i < n)
    {
        if (f[i] == '(')
            b++;
        if (f[i] == ')')
            b--;
        if (b == 0 && i != n - 1)
            return 0;
        i++;
    }
    return 1;
}
