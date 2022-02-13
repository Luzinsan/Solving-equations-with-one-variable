#include <iostream>
#include <string>
#include <iomanip>
#include "PolStr.h"
#include "IInputDevice.h"
#include <cmath>



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
					/*double c;
					while ((b - a) / 2 > eps)
					{
						c = (a + b) / 2;
						if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, c, 0) <= 0)
							b = c;
						else a = c;
					}
					std::cout << expr << " = " << std::setprecision(N) <<  (a + b) / 2 << std::endl;*/


					//метод хорд
					//double c;
					//double x; // начальное приближение
					//if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, a, 2) > 0) 
					//	 x = a;
					//else x = b;
					//do{
					//	c = a -					EvalPolStr(pstr, a, 0)				* (b - a)
					//			/ (EvalPolStr(pstr, b, 0) - EvalPolStr(pstr, a, 0));
					//	if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, c, 0) <= 0)
					//		b = c;
					//	else a = c;
					//	x = x - EvalPolStr(pstr, x, 0) / EvalPolStr(pstr, x, 1);
					//} while (abs(c - x) > eps);
					//std::cout << expr << " = " << std::setprecision(N) << c << std::endl;


					// метод золотого сечения
					//double c,d,h = (sqrt(5) + 1) / 2;
					//while ((b - a) / 2 > eps)
					//{
					//	d = a + (b - a) / h; // новая правая граница
					//	c = a + b - d; // c - a = b - d / или новая левая граница
					//	if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, d, 0) <= 0)
					//		b = d;
					//	else a = c;
					//}
					//std::cout << expr << " = " << std::setprecision(N) <<  (a + b) / 2 << std::endl;

					//метод Ньютона
					//double x1;
					//double x0; // начальное приближение
					//if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, a, 2) > 0) 
					//	 x0 = a;
					//else x0 = b;
					//x1 = x0;
					//do{
					//	x0 = x1;
					//	x1 = x1 - EvalPolStr(pstr, x1, 0) / EvalPolStr(pstr, x1, 1);
					//} while (abs(x1 - x0) > eps);
					//std::cout << expr << " = " << std::setprecision(N) << x1 << std::endl;


					//метод итераций
					//double x0 = (a + b) / 2; // начальное приближение
					//a = EvalPolStr(pstr, a, 1);
					//b = EvalPolStr(pstr, b, 1);
					//double x1 = x0;
					//do{
					//	x0 = x1;
					//	x1 = x1 - EvalPolStr(pstr, x1, 0) / a > b ? a : b;
					//} while (abs(x1 - x0) > eps);
					//std::cout << expr << " = " << std::setprecision(N) << x1 << std::endl;


					// комбинированный метод
					double c;
					do{
						c = a -					EvalPolStr(pstr, a, 0)				* (b - a)
								/ (EvalPolStr(pstr, b, 0) - EvalPolStr(pstr, a, 0));
						if (EvalPolStr(pstr, a, 0) * EvalPolStr(pstr, a, 2) > 0)
						{
							a = a - EvalPolStr(pstr, a, 0) / EvalPolStr(pstr, a, 1);
							b = c;
						}
						else 
						{
							a = c;
							b = b - EvalPolStr(pstr, b, 0) / EvalPolStr(pstr, b, 1);
						}
						
					} while ((b-a)/2 > eps);
					std::cout << expr << " = " << std::setprecision(N) << (a+b)/2 << std::endl;

					delete[] pstr;
				}
				else std::cout << GetError() << std::endl;
			}
		}
	
	} while (choice);
}

