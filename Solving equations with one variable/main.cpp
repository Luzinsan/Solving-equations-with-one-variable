#include <iostream>
#include <string>
#include "PolStr.h"
#include "IInputDevice.h"



int main()
{
	setlocale(LC_ALL, "rus");
	char choice;
	
	do {
		choice = getSymbol({ '1','2','3','4' },
			"Введите способ ввода данных:\n1) с клавиатуры;\n2) из файла\n3) стандартный (из файла input.txt)\n4) завершить программу\n-> ");
		if (choice == '4') break;
		IInputDevice method(choice);
		

		if (!method.isEmptyVectorString())
		{
			std::vector<std::string> exprs = method.getVectorString();
			for (int i = 0; i < exprs.size(); i++)
			{
				std::string expr = exprs[i];
				char* pstr = CreatePolStr(expr.c_str(), 0);
				if (GetError() == ERR_OK && pstr)
				{
					std::cout << pstr << std::endl;
					std::cout << expr << " = " << EvalPolStr(pstr, 1, 0) << std::endl;
					std::cout << expr << "' = " << EvalPolStr(pstr, 1, 1) << std::endl;
					std::cout << expr << "'' = " << EvalPolStr(pstr, 1, 2) << std::endl;
					delete[] pstr;
				}
				else std::cout << GetError() << std::endl;
			}
		}
	
	} while (choice);
}

