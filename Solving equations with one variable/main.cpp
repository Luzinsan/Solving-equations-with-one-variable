#include <iostream>
#include <string>
#include <iomanip>
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
			double a = method.getLeft(), b = method.getRight();
			double eps = method.getEps();
			int N = method.getNAfterComma();
			for (int i = 0; i < exprs.size(); i++)
			{
				std::string expr = exprs[i];

				char* pstr = CreatePolStr(expr.c_str(), 0);
				if (GetError() == ERR_OK && pstr)
				{

					// метод дихотомии
					double c;
					while ((b - a) / 2 > eps)
					{
						
						c = (a + b) / 2;
						if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, c, 0) <= 0)
							b = c;
						else a = c;
					}
					std::cout << expr << " = " << std::setprecision(N) <<  (a + b) / 2 << std::endl;


					//метод хорд








					delete[] pstr;
				}
				else std::cout << GetError() << std::endl;
			}
		}
	
	} while (choice);
}

