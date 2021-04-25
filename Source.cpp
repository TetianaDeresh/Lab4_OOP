/*
Cтворити базовий клас ЗМАГАННЯ З ФУТБОЛУ (задаються назва, дати початку і завершення). 
Створити похідний клас ЧЕМПІОНАТ (задається перелік команд-призерів; 
призерам чемпіонату умовно нараховують 5, 3 і 1 бали). 
Для введених даних про змагання різних років обчислити сумарну кількість призових місць 
різного типу для заданої команди і її сумарний нарахований бал.
*/
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <string.h>

using namespace std;


class Competiton
{
	friend istream& operator>>(istream& inp, Competiton& Comp)
	{
		cout << "\nEnter (Name - Start - End) " << endl;
		return inp >> Comp.Name >> *Comp.Start >> *Comp.End;
	}
	friend ostream& operator<<(ostream& out, const Competiton& Comp)
	{
		return out << "Name: " << *Comp.Name << "Date: " << *Comp.Start << " - " << *Comp.End << endl;
	}

protected:
	char* Name = new char[20];
	int* Start = new int;
	int* End = new int;

public:
	Competiton() { *Name = 'N'; *Start = 0; *End = 0; }
	Competiton(char name, int start, int end) { *Name = name; *Start = start; *End = end; }

	~Competiton() { delete Name; delete Start; delete End; }

	char Get_Name() { return *this->Name; }
	int Get_Start() { return *this->Start; }
	int Get_End() { return *this->End; }

	void Set_Name(char* a) { this->Name = a; }
	void Set_Start(int a) { *this->Start = a; }
	void Set_End(int a) { *this->End = a; }
};

class Championship : public Competiton
{
	friend istream& operator>>(istream& inp, Championship& Champ)
	{
		cout << "\nEnter (Name - Start - End - First place - Second place - Third place) " << endl;
		return inp >> Champ.Name >> *Champ.Start >> *Champ.End >> Champ.First >> Champ.Second >> Champ.Third;
	}
	friend ostream& operator<<(ostream& out, const Championship& Champ)
	{
		return out << "Name: " << *Champ.Name << "\nDate: " << *Champ.Start << " - " << *Champ.End << "\nFirst place : " << *Champ.First << "\nSecond place: " << *Champ.Second << "\nThird place: " << *Champ.Third << endl;
	}

private:
	char* First = new char[20];
	char* Second = new char[20];
	char* Third = new char[20];

public:
	Championship() : Competiton()
	{
		*First = 'N'; *Second = 'N'; *Third = 'N';
	}

	Championship(char name, int start, int end, char* first, char* second, char* third) : Competiton(name, start, end)
	{
		*First = *first; *Second = *second; *Third = *third;
	}

	~Championship() { delete First; delete Second; delete Third; }

	char* Get_First() { return this->First; }
	char* Get_Second() { return this->Second; }
	char* Get_Third() { return this->Third; }

	void Set_First(char* a) { this->First = a; }
	void Set_Second(char* a) { this->Second = a; }
	void Set_Third(char* a) { this->Third = a; }

};

Championship* Array_of_championships[5];
char* Array_of_Teams[100];
int Array_of_First[300];
int Array_of_Second[300];
int Array_of_Third[300];
int Array_of_Points[300];

int Real_Teams = 0;

int input();
void Count(int);

int main()
{
	char str[40];

	int len = input();

	for (int i = 0; i < 2 * len; i++)
	{
		Array_of_Teams[i] = str;
	}

	Count(len);


	for (int i = 0; i < Real_Teams; i++)
	{
		cout << "\nTeam: " << Array_of_Teams[i] << "   " << "Score: " << Array_of_Points[i] << "   " << "First place: " << Array_of_First[i] << "   " << "Second place: " << Array_of_Second[i] << "   " << "Third place: " << Array_of_Third[i] << endl;
	}
}

void Count(int len)
{
	for (int i = 0; i < len; i++)
	{
		bool First = true;
		bool Second = true;
		bool Third = true;
		char* str2 = new char[40];
		int Real_Teams_Now = Real_Teams;

		for (int j = 0; j <= Real_Teams_Now; j++)
		{
			Real_Teams_Now = Real_Teams;
			str2 = Array_of_championships[i]->Get_First();
			if (strcmp(Array_of_Teams[j], str2) == 0)
			{
				Array_of_Points[j] = Array_of_Points[j] + 5;
				Array_of_First[j] = Array_of_First[j] + 1;
				First = false;
			}
			str2 = Array_of_championships[i]->Get_Second();
			if ((strcmp(Array_of_Teams[j], str2) == 0))
			{
				Array_of_Points[j] = Array_of_Points[j] + 3;
				Array_of_Second[j] = Array_of_Second[j] + 1;
				Second = false;
			}
			str2 = Array_of_championships[i]->Get_Third();
			if ((strcmp(Array_of_Teams[j], str2) == 0))
			{
				Array_of_Points[j] = Array_of_Points[j] + 1;
				Array_of_Third[j] = Array_of_Third[j] + 1;
				Third = false;
			}
			if (j == Real_Teams)
			{
				if (First)
				{
					Array_of_Teams[Real_Teams] = Array_of_championships[i]->Get_First();
					Array_of_Points[Real_Teams] = Array_of_Points[Real_Teams] + 5;
					Array_of_First[Real_Teams] = Array_of_First[Real_Teams] + 1;
					Real_Teams++;
				}
				if (Second)
				{
					Array_of_Teams[Real_Teams] = Array_of_championships[i]->Get_Second();
					Array_of_Points[Real_Teams] = Array_of_Points[Real_Teams] + 3;
					Array_of_Second[Real_Teams] = Array_of_Second[Real_Teams] + 1;
					Real_Teams++;
				}
				if (Third)
				{
					Array_of_Teams[Real_Teams] = Array_of_championships[i]->Get_Third();
					Array_of_Points[Real_Teams] = Array_of_Points[Real_Teams] + 1;
					Array_of_Third[Real_Teams] = Array_of_Third[Real_Teams] + 1;
					Real_Teams++;
				}
			}
		}
	}
}

int input()
{
	int n;
	cout << "Enter number of Championships: ";
	cin >> n;
	int i = 0;
	cout << "\nEnter Championships:\n";
	while (i < n)
	{
		Array_of_championships[i] = new Championship;
		cin >> *Array_of_championships[i];
		i++;
	}
	return i;
}
