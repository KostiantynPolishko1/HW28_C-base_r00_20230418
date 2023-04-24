#include <iostream>
#include <string>
#include<fstream>
#include<stdio.h>
#include<Windows.h>
#include <cstdlib>

using namespace std;

//Write a programme that exchanges data between two or more files.
//Allow the user to choose which data in which files should be swapped between them.

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

void printDataF(int *p, string arrfname[]);

int checkV();

void Data(Man* man)
{
	man[0] = { "Mirzahany",		"Edmund",		27, "1996.10.20", "BR211", "Devop" };
	man[1] = { "Savoyskiy",		"Yarosl",		17, "2004.04.19", "BR211", "Admin" };
	man[2] = { "Polishkoi",		"Kostia",		38, "1985.02.06", "BR211", "Devop" };
	man[3] = { "Kovalskiy",		"Olegov",		20, "2003.12.02", "BR211", "Admin" };
	man[4] = { "Rymyancev",		"Arinan",		19, "2004.04.16", "BR211", "Devop" };
	man[5] = { "Borodinan",		"Gannan",		21, "2002.05.08", "BR211", "Devop" };
}

void fileList(Man man[], string  arrfname[])
{
	string fname = "file_";

	cout << "\n  DATA: list of files:\n";
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

int *fillArrFiles(int &qty)
{
restart1:

	cout << "\n Qty files : ";
	qty = checkV();

	if (qty > row || qty % 2 != 0)
	{
		cout << "\n !ERROR! Uncorrect input";
		cout << "\n Input pair number & <= " << row;
		goto restart1;
	}

	int* arr = new int[qty];
	int i = 0, j = 0;


	while (i < qty)
	{
		cout << "\n File package N" << j + 1;
		cout << "\n\t1-st file: Num -> ";
		arr[(i++)] = checkV();
		cout << "\t2-nd file: Num -> ";
		arr[(i++)] = checkV();
		j++;
	}

	return arr;
}

void fileFullExchange(string arrfname[])
{
	//Function for select files for exchange data
	int* arr = 0, qty = 0;
	arr = fillArrFiles(qty);

	//Function: Full exchange data between Files

	int n = 0;
restart3:
	while (n < qty)
	{
		int x = 0, y = 0;
		int* px = 0, * py = 0;

		x = arr[n++];
		y = arr[n++];
		x--, y--;
		px = &x, py = &y;

		cout << "\n DATA of FILES BEFORE:";
		printDataF(px, arrfname);
		printDataF(py, arrfname);
		
		char ch{};
		cout << "\n Confirm: Y - YES / N - NO";
		cout << "\n Enter Y/N: ";
		cin >> ch;
		if (ch == 'N' || ch == 'n')
		{
			cout << "\n !CHANGES CANCELLED!";
			goto restart3;
		}

		//Exchange data between files
		// 
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
			int pos = 0;

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

		system("CLS");

		cout << "\n DATA of FILES AFTER:";
		printDataF(px, arrfname);
		printDataF(py, arrfname);
	}

	delete[] arr;
	arr = nullptr;
}

void fileRowExchange(string arrfname[])
{
	//Create array of files for exchange data
restart1:
	int qty = 0;
	cout << "\n Qty of files for exchange: ";
	qty = checkV();

	if (qty > row || qty % 2 != 0)
	{
		cout << "\n !ERROR! Uncorrect input";
		cout << "\n Input pair number & <= " << row;
		goto restart1;
	}

	int fx = 0, fy = 0;
	int i = 0, j = 1;

restart3:
	while (i < qty)
	{
		cout << "\n File package N" << j++;
		cout << "\n\t1-st file: Num -> ";
		fx = checkV();
		i++;
		cout << "\t2-nd file: Num -> ";
		fy = checkV();
		i++;

		int x = 0, y = 0;
		int* px = 0, * py = 0;

		fx--, fy--;

		px = &fx;
		py = &fy;

		cout << "\n DATA of FILES BEFORE:";
		printDataF(px, arrfname);
		printDataF(py, arrfname);

		//Create array of rows for exchange

		{
		restart2:
			int qtyr = 0;
			cout << "\n Qty rows for exchange: ";
			qtyr = checkV();

			if (qty > 5 || qty == 0)
			{
				cout << "\n !ERROR! Uncorrect input";
				cout << "\n Input number > 0 & <= " << 5;
				goto restart2;
			}

			int* arrows = new int[qtyr];
			int i2 = 0, j2 = 0;

			cout << " Enter the numbers:\n";
			while (i2 < qtyr)
			{
				cout << "\t\tRow ";
				arrows[(i2++)] = checkV();
				j2++;
			}

			char ch{};
			cout << "\n Confirm : y - YES / n - NO";
			cout << "\n Enter Y/N: ";
			cin >> ch;
			if (ch == 'N' || ch == 'n')
			{
				cout << "\n\t!CHANGES CANCELLED!";
				goto restart3;
			}

			//Exchange data between rows
			int n = 0;
			fstream fiox, fioxt;
			fstream fioy, fioyt;
			fiox.open(arrfname[fx], ios::in | ios::out);
			fioy.open(arrfname[fy], ios::in | ios::out);

			if (!fiox.is_open() || !fioy.is_open())
			{
				cout << "\n\tCannot open the file";
			}
			else
			{
				int rown = 0;
				while (!fiox.eof())
				{
					bool tf = false;
					string strx{}, stry{};
					getline(fiox, strx);
					getline(fioy, stry);
					rown++;

					int n = 0;
					while (n < j2)
					{
						if (rown == arrows[n])
						{
							tf = true;
							break;
						}
						n++;
					}
					if (tf)
					{
						int posx = fiox.tellg();
						int posy = fioy.tellg();

						fiox.seekg(-fiox.tellg(), ios::cur);
						fiox << stry << "\n";

						fioy.seekg(-fioy.tellg(), ios::cur);
						fioy << strx << "\n";

						fiox.seekg(fioy.tellg(), ios::beg);
						fioy.seekg(fiox.tellg(), ios::beg);
					}
				}
			}

			fiox.close();
			fioy.close();

			delete[] arrows;
			arrows = nullptr;

			system("CLS");

			cout << "\n DATA of FILES AFTER:";
			printDataF(px, arrfname);
			printDataF(py, arrfname);
		}
	}
}

int main()
{
	int num = 0;
	Data(man);
	string arrfname[row]{};
	fileList(man, arrfname);

	cout
		<< "\n\tMenu:"
		<< "\n\t1 - exchange Full data"
		<< "\n\t2 - exchange Row data";

restart0:
	cout << "\n Operations: ";

	num = checkV();
	switch (num)
	{
	case 1: fileFullExchange(arrfname);
		break;
	case 2: fileRowExchange(arrfname);
		break;
	default: 
		{
			cout << "\n !ERROR! Uncorrect input..";
			goto restart0;
		}
	}
	
	return 0;
}

//Overload functions
//================================================//

void printDataF(int *p, string arrfname[])
{
	ifstream fin;
	fin.open(arrfname[*p]);
	int i = 1;
	if (!fin.is_open())
	{
		cout << "\n\tCannot open the file";
	}
	else
	{
		cout 
			<< "\n\t" << (*p)%2+1 << ((*p)%2 == 0? "-st" : "-nd")
			<< " File: " << arrfname[*p] << "\n";
		while (!fin.eof())
		{
			string str{};
			getline(fin, str);
			cout << "\tRow " << i++ << " | " << str << "\n";
		}
	}
	fin.close();
}

int checkV()
{
	int a;
	while (true) // the cycle continues until the user enters the correct value
	{
		cin >> a;
		if (cin.fail()) // if the previous extraction was unsuccessful,
		{
			cout << " Uncorrect input. Enter int value: ";
			cin.clear(); // then return the cin to 'normal' mode of operation
			cin.ignore(32767, '\n'); // and remove the previous input values from the input buffer
		}
		else // if all is well, return a
		{
			cin.ignore(32767, '\n'); // and remove the previous input values from the input buffer
			return abs(a);
		}
	}

	return 0;
}