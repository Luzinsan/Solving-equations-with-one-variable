#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "PolStr.h"

int main()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Введите способ ввода данных:\n"
		<< "1) с клавиатуры;\n"
		<< "2) из файла\n->";

	char choice;
	do {
		choice = _getche();
		std::cout << std::endl;
		if (choice != '1' && choice != '2')
			std::cout << "Недопустимое значение, попробуйте ещё раз.\n->";
	} while (choice != '1' && choice != '2');
    
	if (choice == '2')
	{
		FILE* ifile;
		freopen_s(&ifile, "input.txt", "r", stdin);
	}
	if (!std::cout)
	{
		std::cerr << "Uh oh, input.txt could not be opened for reading!" << std::endl;
		exit(1);
	}

	std::string expr;
	while (getline(std::cin, expr))
	{
		char* pstr = CreatePolStr(expr.c_str(), 0);
		if (GetError() == ERR_OK)
		{
			std::cout << pstr << std::endl;
			std::cout << expr << " = " << EvalPolStr(pstr, 1, 0) << std::endl;
			std::cout << expr << "' = " << EvalPolStr(pstr, 1, 1) << std::endl;
			std::cout << expr << "'' = " << EvalPolStr(pstr, 1, 2) << std::endl;
			delete[] pstr;
		}
		else std::cout << GetError() << std::endl;
	}

	return 0;

    
}

