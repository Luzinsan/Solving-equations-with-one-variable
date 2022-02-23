#include <iostream>
#include "Timer.h"
#include "IInputDevice.h"
#include "EquationScalar.h"


std::streambuf* redirectOutput(std::ofstream* fout);

int main()
{
	setlocale(LC_ALL, "rus");
	char choice;
	
	//do {
		//choice = getSymbol({ '1','2','3','4' },
		//	"������� ������ ����� ������:\n1) � ����������;\n2) �� �����\n3) ����������� (�� ����� input.txt)\n4) ��������� ���������\n-> ");
		choice = '3';
		//if (choice == '4') break;
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
					do {
						switch(choice) 
						{
						case '1': 
						{
							char method = getSymbol({ '1','2','3','4','5','6','7' },
								"������� ����� ���������� �������:\n"
								"������������:\n1) ����� ���������\n2) ����� ����\n3) ����� �������� �������\n4) ��������������� �����\n"
								"������������:\n5) ����� �������(�����������)\n6) ����� ��������\n\n7) �����\n-> ");
							if (method == '7') break;
							EquationScalar res(pstr, a, b, eps, expr, method);
							
							t.reset();
							res.setResult(choice);

							std::cout << std::setprecision(N) << res
								<< "\n����� ����������: " << t.elapsed() << std::endl;
							continue;
						}
						case '2': case '3':
						{
							std::string filename("output.txt");
							if (choice == '2')
							{
								std::cout << "������� ��� ��������� �����:\n->";
								getline(std::cin, filename);
							}
							std::ofstream* fout = new std::ofstream(filename, std::ios_base::app);
							std::streambuf* original_cout = redirectOutput(fout);
							if (!original_cout) break;

							EquationScalar res(pstr, a, b, eps, expr);
							t.reset();
							try 
							{
								res.setResult(method.getMethod());
								std::cout << "\n" << std::setprecision(N) << res
									<< "����� ����������: " << t.elapsed()
									<< "\n���������� ��������: " << res.getCount() << std::endl;
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
			}
		}
	
	//} while (choice);
}

std::streambuf* redirectOutput(std::ofstream* fout)
{
	std::streambuf* original_cout = std::cout.rdbuf();
	while (!*fout)
	{
		std::string filename;
		char choice;
		choice = getSymbol({ '1', '2' },
			"������ ���� �� ����� ���� ������, ���� �� ����������. ����������� ��� ���?\n1) ��\n2) �����\n->");
		if (choice == '1')
		{
			std::cout << "������� ��� �����:\n->";
			getline(std::cin, filename);
		}
		else return NULL;
		fout->open(filename);
	}
	//�������������� ����������� ����� ������ �� ���������� ����
	std::cout.rdbuf(fout->rdbuf());
	return original_cout;
}