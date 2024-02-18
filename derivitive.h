#include "all_includes.h"
#include "fix.h"
string der(string f,bool debug=0);
string derNamedFunction(string f) //here we put famous functions
{

    int i=0;
    while(f[i]!='(')
        i++;
    string name=f.substr(0,i);
    string body=f.substr(i+1,f.length()-name.length()-2)+',';
    //down
    vector<string> par;
    int j=1;
    i=0;
    while(i+j-1<body.length())
    {
        if(body[i+j-1]==',')
        {
            par.push_back(body.substr(i,j-1));
            i+=j;
            j=0;
        }
        j++;
    }
    i=par.size();
    if(i<1)
        return "NO_PARAMETERS";

    if(name=="sin")
        return "("+der(par[0])+")*cos("+par[0]+")";
    if(name=="cos")
        return "(-("+der(par[0])+"))*sin("+par[0]+")";
    if(name=="tan")
        return "("+der(par[0])+")/cos("+par[0]+")^2";
    if(name=="log"&&i>=2)
        return "("+der(par[0])+")/(("+par[0]+")*ln("+par[1]+"))";
    if(name=="ln")
        return "("+der(par[0])+")/("+par[0]+")";
    cout<<"no_such_function_"+name;
    return "0";
}
string der(string f,bool debug)
{

    //cout<<"der >>"+f<<endl;
    if (f == "")
        return "";
    if (f == "x")
        return "1";
    if (isConst(f))
        return "0";
    if (isBraced(f))
    {
        if(debug)
        cout<<"braced"<<endl;
        while (isBraced(f))
            f = f.substr(1, f.length() - 2);
        return der(f);
    }
    if(isNamedFunction(f))
    {
        if(debug)
        cout<<"named"<<endl;
        return derNamedFunction(f);
    }
    if(isPower(f))
    {
        if(debug)
        cout<<"power"<<endl;
        int b=0;
        for(int i=0; i<f.length(); i++)
            if(f[i]=='(')b++; else
            if(f[i]==')')b--; else
            if(f[i]=='^'&&b==0)
            {
                if(isConst(f.substr(i+1,f.length()-i-1)))
                    return "("+f.substr(i+1,f.length()-i-1)+")*("+der(f.substr(0,i))+")*"+f.substr(0,i)+"^("+f.substr(i+1,f.length()-i-1)+"-1)";
                return "(("+ der(f.substr(0,i))+")*"
                       +f.substr(i+1,f.length()-i-1)
                       +"/"+f.substr(0,i)
                       +"+("+der(f.substr(i+1,f.length()-i-1))
                       +")*ln("+f.substr(0,i)+"))*"+f;
            }
    }
    int n = f.length(), i = 0, j = 1, b = 0, g;
    vector<pair<int, int>> vp;
    string res = "";
    if (isAdd(f))
    {
        if(debug)
        cout<<"add"<<endl;
        while (i + j - 1 < n)
        {
            if (f[i+j-1] == '(')
                b++;
            if (f[i+j-1] == ')')
                b--;
            if ((f[i+j-1]=='-'||f[i+j-1] == '+')&&b==0)
            {
                vp.pb({i, j - 1});
                i += j;
                j = 0;
            }
            j++;
        }
        vp.pb({i, j - 1});
        g = 0;
        n = vp.size();
        for (auto x : vp)
        {
            if(x.S!=0)
                res += "("+der(f.substr(x.F, x.S))+")";
            if (g != vp.size() - 1)
                res += f[x.F + x.S];
            g++;
        }
        return res;
    }


    while (i + j - 1 < n)
    {
        if (f[i+j-1] == '(')
            b++;
        if (f[i+j-1] == ')')
            b--;
        if ((f[i+j-1]=='*'||f[i+j-1]=='/')&&b==0)
        {
            vp.pb({i, j - 1});
            i += j;
            j = 0;
        }
        j++;
    }

    vp.pb({i, j - 1});
    g = 0;
    for (auto x : vp)
    {
        if(g==0||f[x.F-1]=='*')
        {
            res+=f.substr(0,x.F)+"("+
                 der(f.substr(x.F,x.S))+")"+
                 f.substr(x.F+x.S,n-x.F-x.S);

        }
        else
        {
            res+=f.substr(0,x.F-1)+"*"+
                 der(f.substr(x.F,x.S))+"/("+
                 f.substr(x.F,x.S)+")^2"+
                 f.substr(x.F+x.S,n-x.F-x.S);
        }
        if(g!=vp.size()-1)
        {
            if(f[x.F+x.S]=='/')
                res+='-';
            else
                res+='+';
        }
        g++;
    }
    return res;
}

