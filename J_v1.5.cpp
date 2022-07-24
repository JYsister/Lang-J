/*
v1.0------------���;
v1.1------------�޸����� bug;                     ���Ӵ�����ʾ;
                �ɼٱ����Ϊ����;
v1.2------------��ʾ��ΪӢ��;                     ���Ĵ���д��;
v1.3------------���Ĵ���洢��ʽ;                 ��������ַ�����;
v1.3.2----------͹�Դ�����ʾ;                     ���Ӳ���ת���ַ�; 
v1.3.7----------����ע��;                         �޸�ת���ַ����޷������ bug;
                ���Ӳ���ת���ַ�; 
v1.3.7.1--------ȡ������ҳ��; 
v1.3.9----------�޸ı���������ʽ;                 ���ӱ���������;
v1.4.3----------�޸����������ʽ;                 �޸�ע����ʽ;
                �޸������ź����������ı��� bug; ֧������ת���ַ�
v1.5------------����ѭ��;                         ���Ĵ���д��;
*/
#include<bits/stdc++.h>
#include<windows.h>
#define ERROR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
#define ERROR_NO_CHAR(x) ERROR_RED,cout<<"\nError: '\\"<<x<<"' is not a right char."
#define ERROR_NO_VAR(x) ERROR_RED,cout<<"\nError: there is not the var '"<<x<<"'."
#define ERROR_NO_WORD(x) ERROR_RED,cout<<"\nError: \""<<x<<"\" is not the right word."
#define ERROR_NO_END_OF_REPEAT() ERROR_RED,cout<<"\nError: there is not that 'done'."
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
void repeat(string);

void debug()
{
	for(auto i:code) cout<<i<<endl;
}

void run()
{
	while(!code.empty())
	{
		if(code[0].find("var ")==0) make_new_vars(code[0]);
		else if(code[0].find("in ")==0) input(code[0]);
		else if(code[0].find("out ")==0) output(code[0]);
		else if(code[0].find("note ")==0) note(code[0]);
		else if(code[0].find("repeat ")==0)
		{
			repeat(code[0]);
			continue;
		}
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
	puts("Language J (v1.5)\nPlease write your code (when input \"DONE.\" then stop):\n");
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
	}//judge the number
	vector<string>repeat_code;
	code.erase(code.begin());
	int repeats=1,_=0;
	while(1)
	{
		if(code.empty())
		{
			ERROR_NO_END_OF_REPEAT();
			exit(0);
		}
		while(code[0][0]==' ')
		{
			code[0].erase(0,1);
		}
		if(code[0].find("repeat")==0) repeats++;//new repeat
		if(code[0]=="done")//the end of repeat
		{
			if(--repeats==0)
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
		for(auto recd:repeat_code)//copy and paste repeat code
		{
			code.insert(code.begin()+pos++,recd);
		}
	}
}

