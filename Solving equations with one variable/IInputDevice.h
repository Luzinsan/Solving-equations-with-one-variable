#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>

char getSymbol(std::initializer_list<char> list,
	std::string notification_message = "",
	std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

double getDouble(double min = -DBL_MAX,
	double max = DBL_MAX,
	std::string = "", 
	std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

int getNAfterComma(double eps = 0);

class IInputDevice
{
private:
	std::streambuf* original_cin;
	std::ifstream* fin;
	std::vector<std::string> expr;
	char method;
	int NAfterComma;
	double a, b;
public:

	IInputDevice(char choice = '1') 
		: original_cin{ NULL },
		  fin{ NULL }  
	{
		switch (choice)
		{
		case '1': 
			method = getSymbol({'1','2','3','4','5','6'}, 
				"Введите метод вычисления функции:\n"
				"Интервальные:\n1) метод дихотомии\n2) метод хорд\n3) метод золотого сечения\n4) комбинированный метод\n"
				"Итерационные:\n5) метод Ньютона(касательных)\n6) метод итераций\n-> ");
			a = getDouble(-DBL_MAX, DBL_MAX, "Введите левую границу интервала\n-> ");
			b = getDouble(-DBL_MAX, DBL_MAX, "Введите правую границу интервала\n-> ");
			NAfterComma = getNAfterComma();
			break;
		case '2':
		{
			std::string filename;
			std::cout << "Введите имя файла:\n->";
			getline(std::cin, filename);
			fin = new std::ifstream(filename);
			//сохраняем старый поток и перенаправляем стандартный поток на пользовательский файл
			original_cin = redirectInput(fin);
			break;
		}
		case '3':
			fin = new std::ifstream("input.txt");
			//сохраняем старый поток и перенаправляем стандартный поток на файл input.txt
			original_cin = redirectInput(fin);
			break;
		case '4': break;
		default:
			throw std::invalid_argument("Нет подходящего метода ввода данных...\n");
		}
		InputData(choice);
	}

	void InputData(char choice) 
	{
		std::string string;
		switch (choice)
		{
		case '1':
			while (true)
			{
				std::cout << "Введите выражение:\n-> ";

				getline(std::cin, string);
				if (string.empty())
					std::cerr << "Нельзя обработать пустую строку.\n";
				else expr.push_back(string);
				choice = getSymbol({ '1','2' }, "1) продолжить;\n2) завершить ввод данных\n-> ");
				if (choice == '1') continue;
				else break;
			}
			break;
		case '2': case '3':
			while (true)
			{
				string.clear();
				getline(std::cin, string);
				if (!string.empty()) { expr.push_back(string); continue; }
				if (expr.empty())
					std::cerr << "Нельзя обработать пустую строку.\n";
				break;
			}
			method = expr[0][0];
			std::stringstream stream(expr[2]);
			getline(stream, string, ' ');
			a = std::stoi(string);
			getline(stream, string, ' ');
			b = std::stoi(string);
			NAfterComma = getNAfterComma(std::stod(expr[3]));
			// взяли все нужные данные, теперь переместим выражение в начало вектора и отрежем всё ненужное
			// это нужно, так как при считывании с клавиатуры, expr может хранить больше выражений, 
			// нежели считывать из файла только одно
			expr[0] = expr[1];
			expr.resize(1);
			break;
		}
	}

	std::streambuf* redirectInput(std::ifstream* fin = NULL)
	{
		std::streambuf* original_cin = std::cin.rdbuf();
		while (!*fin)
		{
			std::string filename; 
			char choice;
			choice = getSymbol({ '1', '2' }, 
				"Данный файл не может быть открыт, либо не существует. Попробовать ещё раз?\n1) да\n2) выйти\n->");
			if (choice == '1')
			{
				std::cout << "Введите имя файла:\n->";
				getline(std::cin, filename);
			}
			else return NULL;
			fin->open(filename);
		}
		//перенаправляем стандартный поток вывода на переданный файл
		std::cin.rdbuf(fin->rdbuf()); 
		return original_cin;
	}

	~IInputDevice() 
	{
		if (original_cin) 
			std::cin.rdbuf(original_cin); // сбрасываем до стандартного ввода с клавиатуры
		if(fin)
			fin->close();
	}

	bool isEmptyVectorString()
	{
		return expr.empty();
	}
	std::vector<std::string> getVectorString() 
	{ 
		return expr; 
	}

};
#endif