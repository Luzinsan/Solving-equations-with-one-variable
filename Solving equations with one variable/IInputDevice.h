#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>

char getSymbol(std::initializer_list<char> list,
	std::string notification_message = "",
	std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

double getDouble(double min = 0, 
	double max = 1, 
	std::string = "", 
	std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

int getNAfterComma();

class IInputDevice
{
private:
	std::streambuf* original_cin;
	std::ifstream* fin;
	std::vector<std::string> expr;
public:

	IInputDevice(char method = '1') 
		: original_cin{ NULL },
		  fin{ NULL }  
	{
		switch (method)
		{
		case '1': 
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

		std::string string;
		switch (method) 
		{
		case '1':
			
			while (true)
			{
				std::cout << "Введите выражение:\n-> ";
				
				getline(std::cin, string);
				if (string.empty())
					std::cerr << "Нельзя обработать пустую строку.\n";		
				else expr.push_back(string);
				method = getSymbol({ '1','2' }, "1) продолжить;\n2) завершить ввод данных\n-> ");
				if (method == '1') continue;
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