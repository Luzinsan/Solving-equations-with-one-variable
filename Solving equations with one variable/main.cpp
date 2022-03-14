#include <iostream>
#include "Timer.h"
#include "IInputDevice.h"
#include "EquationScalar.h"


std::streambuf* redirectOutput(std::ofstream* fout);

int main()
{
	system("chcp 1251 > null");
	//setlocale(LC_ALL, "rus");
	char choice;

	
	
	do {
		choice = getSymbol({ '1','2','3','4' },
			"Введите способ ввода данных:\n1) с клавиатуры;\n2) из файла\n3) стандартный (из файла input.txt)\n4) завершить программу\n-> ");
		//choice = '3';
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
					EquationScalar res(pstr, a, b, eps, expr);
					do {
						switch (choice)
						{
						case '1':
						{
							char method = getSymbol({ '1','2','3','4','5','6','7' },
								"Введите метод вычисления функции:\n"
								"Интервальные:\n1) метод дихотомии\n2) метод хорд\n3) метод золотого сечения\n4) комбинированный метод\n"
								"Итерационные:\n5) метод Ньютона(касательных)\n6) метод итераций\n\n7) выйти\n-> ");
							if (method == '7') break;

							t.reset();
							res.setResult(choice);

							std::cout << std::setprecision(N) << res
								<< "\nВремя выполнения: " << t.elapsed() << std::endl;
							system("pause");
							system("cls");
							continue;
						}
						case '2': case '3':
						{
							std::string filename("output.txt");
							if (choice == '2')
							{
								std::cout << "Введите имя выходного файла:\n->";
								getline(std::cin, filename);
							}
							std::ofstream* fout = new std::ofstream(filename, std::ios_base::app);
							std::streambuf* original_cout = redirectOutput(fout);
							if (!original_cout) break;


							t.reset();
							try
							{
								res.setResult(method.getMethod());
								std::cout << "\n" << std::setprecision(N) << res
									<< "Время выполнения: " << t.elapsed()
									<< "\nКоличество итераций: " << res.getCount() << std::endl;
							}
							catch (std::exception err)
							{
								std::cout << "\nException: " << err.what();
							}
							std::cout.rdbuf(original_cout);
							fout->close();
							choice = '4';
						}
						break;
						case '4':
							break;
						}
						break;
					} while (true);


				}
				else std::cout << GetError() << std::endl;
				//free(pstr);
				expr[0] = '0';
				pstr[0] = '1';
				if (pstr) delete[] pstr;
				//pstr = nullptr;
			}
		}

	} while (choice);
	system("pause");
}

std::streambuf* redirectOutput(std::ofstream* fout)
{
	std::streambuf* original_cout = std::cout.rdbuf();
	while (!*fout)
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
		fout->open(filename);
	}
	//перенаправляем стандартный поток вывода на переданный файл
	std::cout.rdbuf(fout->rdbuf());
	return original_cout;
}