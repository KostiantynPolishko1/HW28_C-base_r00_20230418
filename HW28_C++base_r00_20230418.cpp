#include <iostream>
#include <string>
#include<fstream>
#include<stdio.h>

using namespace std;

//Ќаписать программу котора€ будет мен€ть данные двух и более файлов между собой.
//ƒать пользователю возможность выбирать какие данные в каких файлах нужно помен€ть между собой.

const int row = 6;

struct Man

{
	string
		sname,
		name;
	int age;
	string
		date,
		group,
		direct;

} man[row];

void Data(Man* man)
{
	man[0] = { "Mirzahanyan",	"Edmund",		27, "1996.10.20", "BR211", "Devop" };
	man[1] = { "Savoyskiy",		"Yaroslav",		17, "2004.04.19", "BR211", "Admin" };
	man[2] = { "Polishko",		"Kostiantyn",	38, "1985.02.06", "BR211", "Devop" };
	man[3] = { "Kovalskiy",		"Oleg",			20, "2003.12.02", "BR211", "Admin" };
	man[4] = { "Rymyanceva",	"Arina",		19, "2004.04.16", "BR211", "Devop" };
	man[5] = { "Borodina",		"Ganna",		21, "2002.05.08", "BR211", "Devop" };
}

void fileList(Man man[], string  arrfname[])
{
	string fname = "file_";

	cout << "\n  List of files:\n";
	for (int i = 0, j = 1; i < row; i++, j++)
	{
		string n{};
		n = to_string(j);
		arrfname[i] = fname + n + ".txt";
		cout << " | " << i + 1 << " | " << arrfname[i] << " |\n";
	}

	for (int i = 0; i < row; i++)
	{
		ofstream fout;
		fout.open(arrfname[i]);
		if (!fout)
		{
			cout << "\n\tCannot open the file " << arrfname[i];
			continue;
		}

		fout
			<< man[i].sname << " " << man[i].name << endl
			<< man[i].age << " yers old" << endl
			<< man[i].date << endl
			<< man[i].group << endl
			<< man[i].direct;

		fout.close();
	}
}

int main()
{
	Data(man);
	string arrfname[row]{};
	fileList(man, arrfname);

	//Menu
restart1:
	int qty = 0;
	cout << "\n Qty of files for exchange: ";
	cin >> qty;

	if (qty > row || qty % 2 != 0)
	{
		cout << "\n ERROR. incorrect input";
		goto restart1;
	}

	int* arr = new int[qty];
	int i = 0, j = 0;


	while (i < qty)
	{
		cout << "\n File package N" << j + 1;
		cout << "\n\t1-st file: Num -> ";
		cin >> arr[(i++)];
		cout << "\t2-nd file: Num -> ";
		cin >> arr[(i++)];
		j++;
	}


	//Function of exchange data between Files
	
	int n = 0;
	while (n < qty)
	{
		int x = 0, y = 0;
		x = arr[n++];
		y = arr[n++];
		x--, y--;

		//move data File X -> File temp
		ofstream fout_t;
		fout_t.open("file_t.txt", ios::trunc);
		fout_t.close();

		fout_t.open("file_t.txt", ios::app);

		ifstream fin_x;
		fin_x.open(arrfname[x]);

		if (!fin_x.is_open() || !fout_t.is_open())
		{
			cout << "\n\tCannot open the file";
		}
		else
		{
			while (!fin_x.eof())
			{
				string str{};
				getline(fin_x, str);
				fout_t << str << "\n";
			}
		}
		fin_x.close();
		fout_t.close();

		//move data File Y -> File Y
		ifstream fin_y;
		fin_y.open(arrfname[y]);

		ofstream fout_x;
		fout_x.open(arrfname[x], ios::out);
		fout_x.close();

		fout_x.open(arrfname[x], ios::app);

		if (!fin_y.is_open() || !fout_x.is_open())
		{
			cout << "\n\tCannot open the file";
		}
		else
		{
			while (!fin_y.eof())
			{
				string str{};
				getline(fin_y, str);
				fout_x << str << "\n";
			}
		}
		fin_y.close();
		fout_x.close();

		//move data File temp -> File Y
		ifstream fin_t;
		fin_t.open("file_t.txt");

		ofstream fout_y;
		fout_y.open(arrfname[y], ios::out);
		fout_y.close();

		fout_y.open(arrfname[y], ios::app);

		if (!fin_t.is_open() || !fout_y.is_open())
		{
			cout << "\n\tCannot open the file";
		}
		else
		{
			while (!fin_t.eof())
			{
				string str{};
				getline(fin_t, str);
				fout_y << str << "\n";
			}
		}
		fin_t.close();
		fin_t.open("file_t.txt");
		fout_y.close();

		remove("file_t.txt");
	}

	return 0;
}