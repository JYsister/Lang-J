/**********
Update of Language J:
v1.0------------完成;
v1.1------------修复部分 bug;							增加错误提示;
                由假编译改为解释;
v1.2------------提示改为英文;							更改代码写法;
v1.3------------更改代码存储方式;						可以输出字符串了;
v1.3.2----------凸显错误提示;							增加部分转义字符;
v1.3.7----------增加注释;								修复转义字符后无法输出的 bug;
                增加部分转义字符;
v1.3.7.1--------取消重置页面;
v1.3.9----------修改变量定义形式;						加变量名限制;
v1.4.3----------修改输入输出形式;						修改注释形式;
                修复后引号后可添加无用文本的 bug;		支持所有转义字符;
v1.5------------增加循环;								更改代码写法;
v1.7------------将 var 语句改为 newvar 语句;			增加了删除变量(delvar 语句);
                修复了变量名可以为关键字的 bug;			修复了重复定义变量的 bug;
				修复了错误提示后背景颜色未恢复的 bug; 
**********/
#include<bits/stdc++.h>
#include<windows.h>
#define ERROR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define ERROR_WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define ERROR_NO_CHAR(x) ERROR_RED,cout<<"\nError: '\\"<<x<<"' is not a right char.",ERROR_WHITE
#define ERROR_NO_VAR(x) ERROR_RED,cout<<"\nError: there is not the var '"<<x<<"'.",ERROR_WHITE
#define ERROR_NO_WORD(x) ERROR_RED,cout<<"\nError: \""<<x<<"\" is not the right word.",ERROR_WHITE
#define ERROR_NO_END_OF_REPEAT() ERROR_RED,cout<<"\nError: there is not that 'done'.",ERROR_WHITE
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
unordered_map<string,int>alive_var;
unordered_map<string,bool>keywords;

 
void newvar(string);
void input(string);
void output(string);
void note(string);
void repeat(string);
void delvar(string);

void debug(){for(auto i:code) cout<<i<<endl;}

void init(){keywords["newvar"]=keywords["in"]=keywords["out"]=keywords["note"]=keywords["repeat"]=keywords["delvar"]=1;}

void run()
{
	while(!code.empty())
	{
		if(code[0].find("newvar ")==0) newvar(code[0]);
		else if(code[0].find("in ")==0) input(code[0]);
		else if(code[0].find("out ")==0) output(code[0]);
		else if(code[0].find("note ")==0) note(code[0]);
		else if(code[0].find("repeat ")==0)
		{
			repeat(code[0]);
			continue;//back to repeat
		}
		else if(code[0].find("delvar ")==0) delvar(code[0]);
		else
		{
			ERROR_NO_WORD(code[0]);
			exit(0);
		}
		if(code.empty()) break;
		code.erase(code.begin());
	}
}

int main()
{
	init();
	puts("Language J (v1.7)\nPlease write your code (when input \"DONE.\" then stop):\n");
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

void newvar(string cd)
{
	vars _var;
	string tname="";
	for(int i=7;i<cd.size();i++)
	{
		if(cd[i]==' ')//have spaces
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else if(cd[i]==',')//done a var
		{
			if(tname==""||keywords[tname]||alive_var[tname]||isdigit(tname[0]))
			{
				ERROR_NO_WORD(cd);
				exit(0);
			}
			alive_var[tname]=1;
			_var.name=tname;
			var.push_back(_var);
			tname="";
		}
		else if(!(isdigit(cd[i])||isalpha(cd[i])||cd[i]=='_')||isdigit(cd[i])&&i==7)//not simple name
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else tname+=cd[i];
	}
	if(tname==""||keywords[tname]||alive_var[tname])//do not make new vars / is keywords / is alive
	{
		ERROR_NO_WORD(cd);
		exit(0);
	}
	alive_var[tname]=1;
	_var.name=tname;
	_var.i=++varsum;
	var.push_back(_var);
}

void input(string cd)
{
	string tname="";
	int wr;
	long long innum=0;
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
	if(tname==""||keywords[tname]||!alive_var[tname])//do not make new vars / is keywords / is not alive
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
				if(cd[i]=='\\')//special char
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

void note(string cd){}//nothing

void repeat(string cd)
{
	bool f=true;
	int times=0;
	for(int i=7;i<cd.size();i++)
	{
		if(!isdigit(cd[i]))
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		times=times*10+cd[i]-48;
	}//judge the number or the var 
	vector<string>repeat_code;
	code.erase(code.begin());
	int repeats=1;
	while(1)
	{
		if(code.empty())//is not the right repeat...done
		{
			ERROR_NO_END_OF_REPEAT();
			exit(0);
		}
		while(code[0][0]==' ')//delete spaces ahead codes in repeat...done
		{
			code[0].erase(0,1);
		}
		if(code[0].find("repeat")==0) repeats++;//new repeat
		if(code[0]=="done")//the end of repeat
		{
			if(!--repeats)
			{
				code.erase(code.begin());
				break;
			}
		}
		repeat_code.push_back(code[0]);
		code.erase(code.begin());
	}
	int pos=0;
	while(times--)
	{
		for(auto recd:repeat_code)//copy and paste repeat codes
		{
			code.insert(code.begin()+pos++,recd);
		}
	}
}

void delvar(string cd)
{
	vars _var;
	string tname="";
	for(int i=7;i<cd.size();i++)
	{
		if(cd[i]==' ')//have spaces
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else if(cd[i]==',')//done a var
		{
			if(tname==""||keywords[tname]||!alive_var[tname])
			{
				ERROR_NO_WORD(cd);
				exit(0);
			}
			alive_var[tname]=0;
			for(int i=0;i<var.size();i++)
			{
				if(var[i].name==tname)
				{
					var.erase(var.begin()+i);
					break;
				}
			}
			tname="";
		}
		else if(!(isdigit(cd[i])||isalpha(cd[i])||cd[i]=='_')||isdigit(cd[i])&&i==7)//not simple name
		{
			ERROR_NO_WORD(cd);
			exit(0);
		}
		else tname+=cd[i];
	}
	if(tname==""||keywords[tname]||!alive_var[tname])//do not make new vars / is keywords / is not alive
	{
		ERROR_NO_WORD(cd);
		exit(0);
	}
	alive_var[tname]=0;
	for(int i=0;i<var.size();i++)
	{
		if(var[i].name==tname)
		{
			var.erase(var.begin()+i);
			break;
		}
	}
}

