#include<fstream>
#include <iostream>
#include <string>

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

int main()
{
	Data(man);
	string arrfname[row]{};
	string fname = "file_";
	
	cout << "\n List of files:\n";
	for (int i = 0, j = 1; i < row; i++, j++)
	{
		string n{};
		n = to_string(j);
		arrfname[i] = fname + n + ".txt";
		cout << "\t" << arrfname[i] << endl;
	}

	for (int i = 0; i < row; i++)
	{
		ofstream out;
		out.open(arrfname[i]);
		if (!out)
		{
			cout << "\n\tCannot open the file " << arrfname[i];
			continue;
		}

		out
			<< man[i].sname << " " << man[i].name << endl
			<< man[i].age << " yers old" << endl
			<< man[i].date << endl
			<< man[i].group << endl
			<< man[i].direct;

		out.close();
	}

	return 0;
}