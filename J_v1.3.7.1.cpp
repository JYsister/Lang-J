/*
v1.0------------完成;
v1.1------------修复部分 bug;     增加错误提示;                 由假编译改为解释;
v1.2------------提示改为英文;     更改代码写法;
v1.3------------更改代码存储方式; 可以输出字符串了;
v1.3.2----------凸显错误提示;     增加部分转义字符; 
v1.3.7----------增加注释;         修复转义字符后无法输出的 bug; 增加部分转义字符; 
v1.3.7.1----------取消重置页面; 
*/
#include<bits/stdc++.h>
#include<windows.h>
#define ERROR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define ERROR_NO_CHAR(x) ERROR_RED,cout<<"\nError: '\\"<<x<<"' is not a right char."
#define ERROR_NO_VAR(x) ERROR_RED,cout<<"\nError: there is not the var '"<<x<<"'."
#define ERROR_NO_WORD(x) ERROR_RED,cout<<"\nError: \""<<x<<"\" is not the right word."
using namespace std;

string t,tname;
bool f;
int varsum;
struct vars{
	string name,in,str;
	char grp;
	long long sum;
	int i;
};
vector<vars>var;
vector<string>code;

void run()
{
	while(!code.empty())
	{
		tname="";
		vars _var;
		int innum=0;
		switch(code[0][0])
		{
			case '>'://input
				tname=code[0].substr(1,code[0].find(';')-1);
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
					_var.grp='i';
					_var.sum=innum;
				}
				else
				{
					_var.grp='s';
					_var.str=_var.in;
				}
				_var.i=++varsum;
				var.push_back(_var);
				break;
			case '<'://output
				if(code[0][1]=='"')
				{
					if(code[0].find('"',2)!=string::npos)
					{
						for(int i=2;code[0][i]!='"';i++)
						{
							if(code[0][i]=='\\')
							{
								switch(code[0][++i])
								{
									case 'n':
										puts("");
										break;
									case '\\':
										cout<<'\\';
										break;
									case '?':
										cout<<'\?';
										break;
									case 't':
										cout<<'\t';
										break;
									case 'v':
										cout<<'\v';
										break;
									case '0':
										cout<<'\0';
										break;
									case 'r':
										cout<<'\r';
										break;
									case 'b':
										cout<<'\b';
										break;
									case 'a':
										cout<<'\a';
										break;
									case 'f':
										cout<<'\f';
										break;
									default:
										ERROR_NO_CHAR(code[0][i]);
										exit(0);
								}
							}
							else cout<<code[0][i];
						}
					}
					else
					{
						ERROR_NO_WORD(code[0].substr(0));
						exit(0);
					}
				}
				else
				{
					tname=code[0].substr(1);
					f=false;
					for(int i=0;i<varsum;i++)
					{
						if(var[i].name==tname)
						{
							f=true;
							if(var[i].grp=='i') cout<<var[i].sum;
		  					else cout<<var[i].str;
						}
					}
					if(!f)
					{
						ERROR_NO_VAR(tname);
						exit(0);
					}
				}
				break;
			case '$'://note
				break; 
			default:
				ERROR_NO_WORD(code[0].substr(0,code.size()-1));
				exit(0);
		}
		code.erase(code.begin());
	}
}

int main()
{
	puts("Language J (v1.3.7.1)\nPlease write your code (when input \"DONE.\" then stop):\n");
	getline(cin,t);
	while(t!="DONE.")
	{
		if(t)code.push_back(t);
		getline(cin,t);
	}
	puts("\n-----\n\nRunning:");
	run();
	puts("\nDone...");
	system("pause");
	return 0;
}

