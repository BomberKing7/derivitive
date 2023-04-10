#include "tests.h"
string mulByN1(string f){
    if(f[0]!='+'&&f[0]!='-')f='+'+f;
    int b=0;
    for(int i=0;i<f.length();i++){
        if(f[i]=='(')b++;
        if(f[i]==')')b--;

        if(f[i]=='+'&&b==0)f[i]='-';
        else
        if(f[i]=='-'&&b==0)f[i]='+';
    }
    return f;
}
string fix(string f){
    if(f==""||f=="x")return f;
    if(isConst(f))return to_string(calc(f));
    if(isBraced(f)){
        while(isBraced(f))
        f=f.substr(1,f.length()-2);
        return fix(f);
        }
    if(isNamedFunction(f))
    {
        int i;
        for(i=0;i<f.length();i++)
            if(f[i]=='(')break;
        return f.substr(0,i)+"("+fix(f.substr(i,f.length()-i))+")";
    }
    if(isPower(f)){
        for(int i=0;i<f.length();i++)
            if(f[i]=='^')
            {
                string base=fix(f.substr(0,i));
                string po=fix(f.substr(i+1,f.length()-i-1));
                if(isMull(base)||isAdd(base)||isPower(base))base="("+base+")";
                if(isMull(po)||isAdd(po)||isPower(po))po="("+po+")";
                return base+"^"+po;
            }
    }
    if(isAdd(f)){
        if(f[0]!='-'&&f[0]!='+')f='+'+f;
        num CON=0;
        string get,res="";
        int b=0,id=0;
        f+='+';
        for(int i=1;i<f.length();i++){
            if(f[i]=='(')b++;
            if(f[i]==')')b--;
            if((f[i]=='-'||f[i]=='+')&&b==0){
                get=f.substr(id+1,i-id-1);
                get=fix(get);
                if(isConst(get))CON+=calc(f[id]+get);
                else
                if(f[id]=='-')
                    res+=mulByN1(get);
                else
                {
                    if(res!="")res+=f[id];
                    res+=get;
                }
                id=i;
            }
        }
        if(CON<0)res+=to_string(CON);
        else if(CON>0)res+="+"+to_string(CON);
        return res;
    }
    num CON=1;
    string get,res="";
    int b=0,id=0;
    f="*"+f+"*";
    for(int i=1;i<f.length();i++){
        if(f[i]=='(')b++;
        if(f[i]==')')b--;
        if((f[i]=='*'||f[i]=='/')&&b==0){
            get=f.substr(id+1,i-id-1);
            get=fix(get);
            if(isConst(get))CON*=calc(get);
            else
            {
            if(res!="")res+=f[id];
            if(isAdd(get))get="("+get+")";
            res+=get;
            }
        id=i;
        }
    }
    if(CON==0)res="0";
    else
    if(CON!=1&&CON!=-1)
    res=to_string(CON)+"*"+res;
    if(CON==-1)res="-"+res;

    return res;
}
