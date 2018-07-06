#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
using namespace std;

typedef struct Stos
{
	string znak;	
	Stos *next=NULL;
} Stos;

typedef struct Lista
{
	string znak;
	Lista *next=NULL;
}Lista;

Lista *head=NULL;
Stos *glowa=NULL;
Lista *temp=NULL;
Stos *tempo=NULL;
fstream plik1, plik2;
string zawartosc;

void push(Lista *z)
{
	Stos *nowa = new Stos;
	nowa->znak=z->znak;
	if(glowa==NULL)
	{
		glowa=nowa;
	}
	else
	{
		nowa->next=glowa;
		glowa=nowa;
	}
}

void pop()
{
	tempo=glowa;
	glowa=glowa->next;
	plik2<<tempo->znak<<" ";
}

char sprcyf[2];

int main()
{
	plik1.open("WE.txt", std::ios::in);
	plik2.open("WY.txt", std::ios::app);
	if (!plik1.good())
	{
		cout << "Nie posiadasz pliku o nazwie WE.txt!" << endl;
		return 0;
	}
	else
	{
		while(!plik1.eof())
		{
			getline(plik1, zawartosc);
			int a = zawartosc.length();
			for(int i=0;i<a;i++)
			{
				Lista *nowy = new Lista;
				nowy->znak=zawartosc[i];
				if(head == NULL)
				{
					head=nowy;
				}
				else
				{
					temp=head;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=nowy;
				}
			}
			temp=head;
			while(temp!=NULL)
			{
				if(temp->znak=="(")
				{
					push(temp);
				}
				else if(temp->znak=="+"||temp->znak=="-")
				{
					push(temp);
				}
				else if(temp->znak=="*"||temp->znak=="/"||temp->znak=="^")
				{
					push(temp);
					if(temp->next->znak!="(")
					{
						temp=temp->next;
						start1:
						plik2<<temp->znak;
						if(temp->next!=NULL)
						{
							strcpy(sprcyf,temp->next->znak.c_str());
						}
						if((sprcyf[0]>=48&&sprcyf[0]<=57)&&temp->next!=NULL)
						{
							temp=temp->next;
							goto start1;
						}
						else
						{
							plik2<<" ";
						}
						pop();
					}
				}
				else if(temp->znak==")")
				{
					while(glowa->znak!="(")
					{
						pop();
					}
					tempo=glowa;
					glowa=glowa->next;
					delete tempo;
					if(temp->znak=="*"||temp->znak=="/"||temp->znak=="^")
					{
						pop();
					}
				}
				else
				{
					start:
					plik2<<temp->znak;
					if(temp->next!=NULL)
					{
						strcpy(sprcyf,temp->next->znak.c_str());
					}
					if((sprcyf[0]>=48&&sprcyf[0]<=57)&&temp->next!=NULL)
					{
						temp=temp->next;
						goto start;
					}
					else
					{
						plik2<<" ";
					}
				}
				temp=temp->next;
			}
			while(glowa!=NULL)
			{
				if(glowa->znak=="(")
				{
					tempo=glowa;
					glowa=glowa->next;
					delete tempo;
				}
				else
				{
					pop();
				}
			}
			while(head!=NULL)
			{
				temp=head;	
				head=head->next;
				delete temp;
			}
			head=NULL;
			glowa=NULL;
			plik2<<endl;
		}
		plik1.close();
		plik2.close();
		return 0;
	}
}
