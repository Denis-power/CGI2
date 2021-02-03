#include <iostream>
#include <fstream>
#include "cgi.h"

using namespace std;
const char* header = "Вторая страница сайта";
void show_menu()
{
	ifstream f;
	f.open("template/menu.txt");
	if (f.is_open())
	{
		while (!f.eof())
		{
			char* line = new char[256];
			f.getline(line, 256);
			char* part2;
			strtok_s(line, " ", &part2);
			cout << "<div class='menuitem'><a href='"
				<< line << "'>" <<
				part2 << "</a></div>";
		}
		f.close();
	}
}

void show_form(const char* data)
{
	char* param_value = nullptr;
	get_param_value(param_value, "firstname", data);
	cout << "<form method='post' action='page2.cgi'>\n";
	cout << "<table><tr><td>Ваше имя: </td><td>" <<
		"<input type='text' name='firstname' value='" << param_value << "'>" <<
		"<tr><td>Ваш возраст: </td><td>";
	get_param_value(param_value, "age", data);
	cout << "<input type = 'text' name = 'age' value='" << param_value << "'> " <<
		"</td></tr>" <<
		"<tr><td colspan='2'><input type='submit'>" <<
		"</td></tr></table></form>";
	delete[] param_value;
}

void show_user_data(const char* data)
{
	cout << "<br>" << data << "<br>";
	char* param_value = nullptr;
	get_param_value(param_value, "firstname", data);
	cout << "<br>First name:" << param_value << "<br>";
	get_param_value(param_value, "age", data);
	cout << "<br>Age:" << param_value << "<br>";
	delete[] param_value;
}

void show_content()
{
	char* data = nullptr;
	get_form_data(data);
	show_form(data);
	show_user_data(data);
	delete[] data;
}

void main()
{
	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f;
	f.open("template/main");
	if (f.is_open())
	{
		while (!f.eof())
		{
			char* line = new char[65536];
			f.getline(line, 65535);
			if (strcmp(line, "<!--header-->") == 0)
				cout << header;
			else if (strcmp(line, "<!--menu-->") == 0)
				show_menu();
			else if (strcmp(line, "<!--content-->") == 0)
				show_content();
			else
				cout << line;
		}
		f.close();
	}
	else
	{
		cout << "Can't open template file :(";
	}
}
