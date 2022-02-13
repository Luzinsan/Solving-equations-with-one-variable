#include <iostream>
#include "Timer.h"
#include "IInputDevice.h"
#include "EquationScalar.h"




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
					Timer t;
					EquationScalar res(pstr, a, b, eps, expr, choice);
					do {
						choice = method.getMethod();
						if (choice == '7') break;
						t.reset();
						res.setResult(choice);
						std::cout << std::setprecision(N) << res
							      << "\nВремя выполнения: " << t.elapsed() << std::endl;
					} while (true);
					
				}
				else std::cout << GetError() << std::endl;
			}
		}
	
	} while (choice);
}

