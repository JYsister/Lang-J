/*
v1.0----------���
v1.1----------�޸����� bug; ���Ӵ�����ʾ; �ɱ����Ϊ����
*/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

string s,t,nm;
bool f;
int tmp=1;
//vector<pair<string,pair<string,string>>>var;

struct vars{
	string name,in,grp,str;
	long long sum;
	int i_;
}var[100005];

int main()
{
	puts("���������(���������\"DONE.\"ʱֹͣ):");
	getline(cin,t);
	while(t!="DONE.")
	{
		if(s.size()) s=s+';'+t;
		else s=t;
		getline(cin,t);
	}
	s+=';';
	system("cls");
	puts("��ʼ����:");
	while(s.size())
	{
		nm="";
		switch(s[0])
		{
			case '>'://����
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
			case '<'://���
				if(s[1]=='\\')
				{
					switch(s[2])
					{
						case 'n':
							puts("");
							break;
						case '!':
							cout<<' ';
							break;
						default:
							cout<<"����: '\\"<<s[2]<<"'Ϊ�Ƿ�ת���ַ�";
							exit(0);
					}
					break;
				}
				nm=s.substr(1,s.find(';')-1);
				f=false;
				for(int i=1;i<tmp;i++)
				{
					if(var[i].name==nm)
					{
						f=true;
						if(var[i].grp=="int") cout<<var[i].sum;
	  					else cout<<var[i].str;
					}
				}
				if(!f)
				{
					cout<<"����: ����'"<<nm<<"'������";
					exit(0);
				}
				break;
			default:
				cout<<"����: \""<<s.substr(0,s.find(';'))<<"\"Ϊ�Ƿ����";
				exit(0);
		}
		s.erase(0,s.find(';')+1);
	}
	return 0;
}

