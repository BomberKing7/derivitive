#include "tests.h"
#define all(n) n.begin(),n.end()
map<string,double> get_mp;
void map_parts_add(string f,double &CON){
    cout<<"   >>>>>>"<<f<<endl;
    if(f[0]!='-'&&f[0]!='+')f='+'+f;
    f+='+';
int b=0,id=0,n=f.length();
for(int i=1;i<n;i++)
{

    if(f[i]=='(')b++;else
    if(f[i]==')')b--;else
    if((f[i]=='+'||f[i]=='-')&&b==0){
        if(isConst(f.substr(id+1,i-id-1)))
            CON+=calc(f.substr(id,i-id));
        else
        if(f[id]=='+')
            get_mp[f.substr(id+1,i-id-1)]++;
        else
        if(f[id]=='-')
            get_mp[f.substr(id+1,i-id-1)]--;
        id=i;
    }
}
for(auto xx:get_mp)
    cout<<xx.first<<" "<<xx.second<<endl;
}
void separated(string f,string &get,double &con){
//f is mul
if(f[0]=='/'||f[0]=='*')f='1'+f;
int id=-1;
f+='*';
int b=0;
for(int i=0;i<f.length();i++){
    if(f[i]=='(')b++;
    else 
   if(f[i]==')')b--;
    else
    if((f[i]=='*'||f[i]=='/')&&b==0){
        if(!isConst(f.substr(0,i))){
            if(id==-1)
            {
            get=f.substr(0,f.length()-1);
            con=1;
            break;
            }else{
            get=f.substr(id,f.length()-id-1);
            con=calc(f.substr(0,id));
            break;
            }
        }
        id=i;
    }
}
}


string to_string_modified(num x){
string res=to_string(x);
int i=res.length()-1;
while(i>0&&res[i]=='0') { i--; }
if(res[i]=='.')i--;
return res.substr(0,i+1);
}

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

string powByN1(string f){
    if(f[0]!='*'&&f[0]!='/')f="*"+f;
    int b=0;
    for(int i=0;i<f.length();i++){
        if(f[i]=='(')b++;
        if(f[i]==')')b--;

        if(f[i]=='*'&&b==0)f[i]='/';
        else
        if(f[i]=='/'&&b==0)f[i]='*';
    }
    return f;
}

string fix(string f){
    if(f==""||f=="x")return f;
    if(isConst(f))return to_string_modified(calc(f));
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
        int b=0;
        for(int i=0;i<f.length();i++)
            if(f[i]=='(')b++; else
            if(f[i]==')')b--; else
            if(f[i]=='^'&&b==0)
            {
                string base=fix(f.substr(0,i));
                string po=fix(f.substr(i+1,f.length()-i-1));
                if(po=="0"||base=="1")return "1";
                if(po=="1")return base;

                if(isMull(base)||isAdd(base)||isPower(base))base="("+base+")";
                if(isMull(po)||isAdd(po))po="("+po+")";
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
                if(f[id]=='-'){
                    res+=mulByN1(get);
                }
                else
                {
                    if(res!=""&&get[0]!='-'&&get[0]!='+')res+=f[id];
                    res+=get;
                }
                id=i;
            }
        }

        if(res[0]=='+')res=res.substr(1,res.length()-1);
        if(CON<0)res+=to_string_modified(CON);
        else if(CON>0)res+="+"+to_string_modified(CON);
        return res;
    }
    num CON=1;
    string get,res="";
    string get_fun;double get_con;
    int b=0,id=0;
    f="*"+f+"*";
    for(int i=1;i<f.length();i++){
        if(f[i]=='(')b++;
        else
        if(f[i]==')')b--;
        else
        if((f[i]=='*'||f[i]=='/')&&b==0){
            get=f.substr(id+1,i-id-1);
            get=fix(get);

            if(isConst(get)){
            if(f[id]=='/')
            CON/=calc(get);
            else
            CON*=calc(get);}
            else
            {
            if(get[0]=='-'){
                CON*=-1;
                get=mulByN1(get);
                get=get.substr(1,get.length()-1);
            }
            if(isMull(get)&&f[id]=='/')
            {
               
                get=powByN1(get),f[id]='*';
            }


            if(isMull(get)){
                if(get[0]=='/')get='1'+get;
                
                separated(get,get_fun,get_con);
                if(get_fun[0]=='*')get_fun=get_fun.substr(1,get_fun.length()-1);
                if(f[id]=='/'){res+=f[id];}
                else if(res!=""&&get_fun[0]!='/'&&get_fun[0]!='*'){res+=f[id];}
                res+=get_fun;
                CON*=get_con;
            }else{
            if(f[id]=='/'){res+=f[id];}
            else if(res!=""&&get[0]!='/'&&get[0]!='*'){res+=f[id];}
            if(isAdd(get))
                res+="("+get+")";
            else
                res+=get;
            }
            }
        id=i;
        }
    }
    if(res=="")return to_string_modified(CON);
    if(CON==0)return "0";
    else
    if(CON!=1&&CON!=-1){
    if(res[0]!='/')res='*'+res;
    res=to_string_modified(CON)+res;
    }
    if(CON==-1){
    if(res[0]=='/')
        res="-1"+res;
    else
        res="-"+res;}
    else
    if(res[0]=='/')res="1"+res;
    if(isBraced(res))res=res.substr(1,res.length()-2);

    return res;
}
