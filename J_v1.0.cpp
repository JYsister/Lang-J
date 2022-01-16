#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

string s,t,nm;
int tmp=1;

struct node{
	string name,in,grp,str;
	long long sum;
	int i_;
}var[100005];

void ready_run()
{
	for(int i=1;i<=3;i++)
	{
		system("cls");
		puts("编译中.");
		Sleep(100);
		system("cls");
		puts("编译中..");
		Sleep(100);
		system("cls");
		puts("编译中...");
		Sleep(100);
	}
	system("cls");
	puts("开始运行:");
}

int main()
{
	puts("请输入代码(到出现语句\"DONE.\"时停止):");
	getline(cin,t);
	while(t!="DONE.")
	{
		if(s.size()) s=s+';'+t;
		else s=t;
		getline(cin,t);
	}
	s+=';';
	ready_run();
	while(s.size())
	{
		nm="";
		switch(s[0])
		{
			case '>':
				for(int i=1;s[i]!=';';i++)
				{
					nm+=s[i];
				}
				var[tmp].name=nm;
				cin>>var[tmp].in;
				if(isdigit(var[tmp].in[0]))
				{
					var[tmp].grp="int";
					for(int i=0;i<var[tmp].in.size();i++)
					{
						var[tmp].sum=var[tmp].sum*10+(var[tmp].in[i]-48);
					}
				}
				else
				{
					var[tmp].grp="str";
					var[tmp].str=var[tmp].in;
				}
				var[tmp].i_=tmp++;
				break;
			case '<':
				if(s[1]=='\\')
				{
					switch(s[2])
					{
						case 'n':
							cout<<endl;
							break;
						case '!':
							cout<<' ';
							break;
					}
					break;
				}
				for(int i=1;s[i]!=';';i++)
				{
					nm+=s[i];
				}
				for(int i=1;i<tmp;i++)
				{
					if(var[i].name==nm)
					{
						if(var[i].grp=="int") cout<<var[i].sum;
						else cout<<var[i].str;
					}
				}
		}
		s.erase(0,s.find(';')+1);
	}
	return 0;
}

