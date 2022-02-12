#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "PolStr.h"

char getSymbol(std::initializer_list<char> list, 
	std::string notification_message = "",
	std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->")
{
	char choice = NULL;
	std::cout << notification_message;
	
	bool flag = true;
	do {
		choice = _getche();
		std::cout << std::endl;
		for(auto it = list.begin(); it != list.end(); it++)
			if (it[0] == choice) { flag = false; break; }

		if (flag) std::cerr << error_message;
	} while (flag);
	return choice;
}

std::ifstream* redirectInput(char choice)
{
	std::string filename("input.txt");
	if (choice == '2') 
	{
		std::cout << "Введите имя файла:\n->";
		getline(std::cin, filename);
	}
	std::ifstream* fin = new std::ifstream(filename);
		
	while (!*fin)
	{
		choice = getSymbol({ '1', '2' }, "Данный файл не может быть открыт. Попробовать ещё раз?\n1) да\n2) выйти\n->");
		if (choice == '1') 
		{
			std::cout << "Введите имя файла:\n->";
			getline(std::cin, filename);
		}
		else return NULL;
		fin->open(filename);
	}
	std::cin.rdbuf(fin->rdbuf()); //redirect std::cin to input.txt
	return fin;
}



int main()
{
	setlocale(LC_ALL, "rus");
	
	
	char choice;
	do{
		choice = getSymbol({ '1','2','3','4'},
			"Введите способ ввода данных:\n1) с клавиатуры;\n2) из файла\n3) стандартный (из файла input.txt)\n4) завершить программу\n-> ");
		if (choice == '4') break;
		std::streambuf* original_cin = std::cin.rdbuf(); //save old buf
		std::ifstream* fin = NULL;
		if (choice == '2' || choice == '3') 
			if(!(fin = redirectInput(choice))) continue; 
		
		std::string expr;
		do {
			if (choice == '1') std::cout << "Введите выражение:\n-> ";
			expr.clear();
			getline(std::cin, expr);
				
			if (expr.empty())
			{
				if (choice == '2' || choice == '3') break;

				std::cerr << "Нельзя обработать пустую строку.\n";
				if (choice == '1') choice = getSymbol({ '1','2' }, "1) продолжить;\n2) выйти\n-> ");
				if (choice != '1') { choice = '4'; break; } // чтобы не попало под условие закрытия файла
				else continue;
			}
			
			
			
			char* pstr = CreatePolStr(expr.c_str(), 0);
			if (GetError() == ERR_OK)
			{
				std::cout << pstr << std::endl;
				std::cout << expr << " = " << EvalPolStr(pstr, 1, 0) << std::endl;
				std::cout << expr << "' = " << EvalPolStr(pstr, 1, 1) << std::endl;
				std::cout << expr << "'' = " << EvalPolStr(pstr, 1, 2) << std::endl;
				delete[] pstr;
				//expr.clear();
			}else std::cout << GetError() << std::endl;

			if (choice == '1')
			{
				choice = getSymbol({ '1','2' },
					"1) продолжить;\n2) выйти\n-> ");
				if (choice == '2') { choice = '4'; break; } // чтобы не попало под условие закрытия файла
			}
		} while (true);
		
		if (choice == '2' || choice == '3') { std::cin.rdbuf(original_cin); fin->close(); }   //reset to standard input again
	} while (choice);
	return 0;

    
}

