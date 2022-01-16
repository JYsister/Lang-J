/*
v1.0----------完成
v1.1----------修复部分 bug; 增加错误提示; 由编译改为半解释
v1.2----------提示改为英文; 更改代码写法 
*/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

string code,t,tname;
bool f;
int varsum;
struct vars{
	string name,in,grp,str;
	long long sum;
	int i;
};
vector<vars>var; 

void run()
{
	while(code.size())
	{
		tname="";
		vars _var;
		int innum=0;
		switch(code[0])
		{
			case '>'://input
				tname=code.substr(1,code.find(';')-1);
				_var.name=tname;
				cin>>_var.in;
				f=false;
				for(int i=0;i<_var.in.size();i++)
				{
					if(!isdigit(_var.in[i]))
					{
						f=true;
						break;
					}
					innum=innum*10+_var.in[i]-48;
				}
				if(!f)
				{
					_var.grp="int";
					_var.sum=innum;
				}
				else
				{
					_var.grp="str";
					_var.str=_var.in;
				}
				_var.i=++varsum;
				var.push_back(_var);
				break;
			case '<'://output
				if(code[1]=='\\')
				{
					switch(code[2])
					{
						case 'n':
							puts("");
							break;
						case '!':
							cout<<' ';
							break;
						default:
							cout<<"\nError: '\\"<<code[2]<<"' is not a right char.";
							exit(0);
					}
					break;
				}
				tname=code.substr(1,code.find(';')-1);
				f=false;
				for(int i=0;i<varsum;i++)
				{
					if(var[i].name==tname)
					{
						f=true;
						if(var[i].grp=="int") cout<<var[i].sum;
	  					else cout<<var[i].str;
					}
				}
				if(!f)
				{
					cout<<"\nError: there is not the var '"<<tname<<"'.";
					exit(0);
				}
				break;
			default:
				cout<<"\nError: \""<<code.substr(0,code.find(';'))<<"\" is not the right word.";
				exit(0);
		}
		code.erase(0,code.find(';')+1);
	}
}

int main()
{
	puts("Please write your code (when input \"DONE.\" then stop):");
	getline(cin,t);
	while(t!="DONE.")
	{
		if(code.size()) code+=';'+t;
		else code=t;
		getline(cin,t);
	}
	code+=';';
	system("cls");
	puts("Running:");
	run();
	puts("\nDone...");
	system("pause");
	return 0;
}

