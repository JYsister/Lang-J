/*
v1.0------------完成;
v1.1------------修复部分 bug;     增加错误提示;
                由假编译改为解释;
v1.2------------提示改为英文;     更改代码写法;
v1.3------------更改代码存储方式; 可以输出字符串了;
v1.3.2----------凸显错误提示;     增加部分转义字符; 
v1.3.7----------增加注释;         修复转义字符后无法输出的 bug;
                增加部分转义字符; 
v1.3.7.1--------取消重置页面; 
v1.3.9----------修改变量定义形式; 增加变量名限制;
v1.4.3----------修改输入输出形式; 修改注释形式;
                修复后引号后可添加无用文本的 bug; 支持所有转义字符 
*/
#include<bits/stdc++.h>
#include<windows.h>
#define ERROR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define ERROR_NO_CHAR(x) ERROR_RED,cout<<"\nError: '\\"<<x<<"' is not a right char."
#define ERROR_NO_VAR(x) ERROR_RED,cout<<"\nError: there is not the var '"<<x<<"'."
#define ERROR_NO_WORD(x) ERROR_RED,cout<<"\nError: \""<<x<<"\" is not the right word."
using namespace std;

string t;
bool f;
int varsum;
struct vars{
	string name,in,str;
	char grp;
	long long num;
	int i;
};
vector<vars>var;
vector<string>code;

void make_new_vars(string);
void input(string);
void output(string);
void note(string);

void debug()
{
	for(auto i:var) cout<<i.name<<' ';
	cout<<endl;
}

void run()
{
	while(!code.empty())
	{
		if(code[0].find("var ")==0) make_new_vars(code[0]);
		else if(code[0].find("in ")==0) input(code[0]);
		else if(code[0].find("out ")==0) output(code[0]);
		else if(code[0].find("note ")==0) note(code[0]);
		else
		{
			ERROR_NO_WORD(code[0]);
			exit(0);
		}
		code.erase(code.begin());
	}
}

int main()
{
	puts("Language J (v1.4.3)\nPlease write your code (when input \"DONE.\" then stop):\n");
	getline(cin,t);
	while(t!="DONE.")
	{
		if(t!="") code.push_back(t);
		getline(cin,t);
	}
	puts("\n-----\n\nRunning:");
	run();
	puts("\nDone...");
	system("pause");
	return 0;
}

void make_new_vars(string cd)
{
	vars _var;
	string tname="";
	for(int i=4;i<cd.size();i++)
	{
		if(cd[i]==' ')//have spaces
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else if(cd[i]==',')//done a var
		{
			if(tname=="")
			{
				ERROR_NO_WORD(cd);
				exit(0);
			}
			_var.name=tname;
			var.push_back(_var);
			tname="";
		}
		else if(!(isdigit(cd[i])||isalpha(cd[i])||cd[i]=='_')||isdigit(cd[i])&&i==4)//not simple name
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else tname+=cd[i];
	}
	if(tname=="")//do not make new vars
	{
		ERROR_NO_WORD(cd);
		exit(0);
	}
	_var.name=tname;
	_var.i=++varsum;
	var.push_back(_var);
}

void input(string cd)
{
	string tname="";
	int wr,innum=0;
	bool f;
	for(int i=3;i<cd.size();i++)
	{
		if(cd[i]==' ')//have spaces
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else if(cd[i]==',')//done a var
		{
			if(tname=="")
			{
				ERROR_NO_WORD(cd);
				exit(0);
			}
			f=false;
			for(int j=0;j<var.size();j++)
			{
				if(var[j].name==tname)
				{
					f=true;
					wr=j;
					break;
				}
			}
			cin>>var[wr].in;//input things
			f=false;
			for(int j=0;j<var[wr].in.size();j++)
			{
				if(!isdigit(var[wr].in[i]))
				{
					f=true;
					break;
				}
				innum=innum*10+var[wr].in[j]-48;
			}
			if(!f)
			{
				var[wr].grp='i';//integer
				var[wr].num=innum;
			}
			else
			{
				var[wr].grp='s';//string
				var[wr].str=var[wr].in;
			}
			tname="";
		}
		else if(!(isdigit(cd[i])||isalpha(cd[i])||cd[i]=='_')||isdigit(cd[i])&&i==4)//not simple name
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else tname+=cd[i];
	}
	if(tname=="")//do not make new vars
	{
		ERROR_NO_WORD(cd);
		exit(0);
	}
	f=false;
	for(int i=0;i<var.size();i++)
	{
		if(var[i].name==tname)
		{
			f=true;
			wr=i;
			break;
		}
	}
	cin>>var[wr].in;//input things
	f=false;
	for(int i=0;i<var[wr].in.size();i++)
	{
		if(!isdigit(var[wr].in[i]))
		{
			f=true;
			break;
		}
		innum=innum*10+var[wr].in[i]-48;
	}
	if(!f)
	{
		var[wr].grp='i';//integer
		var[wr].num=innum;
	}
	else
	{
		var[wr].grp='s';//string
		var[wr].str=var[wr].in;
	}
}

void output(string cd)
{
	bool f;
	string tname="";
	if(cd[4]=='"')//output a string
	{
		if(cd.find('"',5)!=string::npos&&cd[cd.size()-1]=='"')
		{
			for(int i=5;cd[i]!='"';i++)
			{
				if(cd[i]=='\\')
				{
					switch(cd[++i])
					{
						case 'n':
							puts("");
							break;
						case '\\':
							putchar('\\');
							break;
						case '?':
							putchar('\?');
							break;
						case 't':
							putchar('\t');
							break;
						case 'v':
							putchar('\v');
							break;
						case '0':
							putchar('\0');
							break;
						case 'r':
							putchar('\r');
							break;
						case 'b':
							putchar('\b');
							break;
						case 'a':
							putchar('\a');
							break;
						case 'f':
							putchar('\f');
							break;
						case '\"':
							putchar('\"');
							break;
						case '\'':
							putchar('\'');
							break;
						default:
							ERROR_NO_CHAR(cd[i]);
							exit(0);
					}
				}
				else cout<<cd[i];
			}
		}
		else
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
	}
	else//output a var
	{
		tname=cd.substr(4);
		f=false;
		for(int i=0;i<var.size();i++)
		{
			if(var[i].name==tname)
			{
				f=true;
				if(var[i].grp=='i') cout<<var[i].num;
				else cout<<var[i].str;
				break;
			}
		}
		if(!f)
		{
			ERROR_NO_VAR(tname);
			exit(0);
		}
	}
}

void note(string cd){}

