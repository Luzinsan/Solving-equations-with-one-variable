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
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

double getDouble(double min = -DBL_MAX,
	double max = DBL_MAX,
	std::string = "", 
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

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
				"������� ����� ���������� �������:\n"
				"������������:\n1) ����� ���������\n2) ����� ����\n3) ����� �������� �������\n4) ��������������� �����\n"
				"������������:\n5) ����� �������(�����������)\n6) ����� ��������\n-> ");
			a = getDouble(-DBL_MAX, DBL_MAX, "������� ����� ������� ���������\n-> ");
			b = getDouble(-DBL_MAX, DBL_MAX, "������� ������ ������� ���������\n-> ");
			NAfterComma = getNAfterComma();
			break;
		case '2':
		{
			std::string filename;
			std::cout << "������� ��� �����:\n->";
			getline(std::cin, filename);
			fin = new std::ifstream(filename);
			//��������� ������ ����� � �������������� ����������� ����� �� ���������������� ����
			original_cin = redirectInput(fin);
			break;
		}
		case '3':
			fin = new std::ifstream("input.txt");
			//��������� ������ ����� � �������������� ����������� ����� �� ���� input.txt
			original_cin = redirectInput(fin);
			break;
		case '4': break;
		default:
			throw std::invalid_argument("��� ����������� ������ ����� ������...\n");
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
				std::cout << "������� ���������:\n-> ";

				getline(std::cin, string);
				if (string.empty())
					std::cerr << "������ ���������� ������ ������.\n";
				else expr.push_back(string);
				choice = getSymbol({ '1','2' }, "1) ����������;\n2) ��������� ���� ������\n-> ");
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
					std::cerr << "������ ���������� ������ ������.\n";
				break;
			}
			method = expr[0][0];
			std::stringstream stream(expr[2]);
			getline(stream, string, ' ');
			a = std::stoi(string);
			getline(stream, string, ' ');
			b = std::stoi(string);
			NAfterComma = getNAfterComma(std::stod(expr[3]));
			// ����� ��� ������ ������, ������ ���������� ��������� � ������ ������� � ������� �� ��������
			// ��� �����, ��� ��� ��� ���������� � ����������, expr ����� ������� ������ ���������, 
			// ������ ��������� �� ����� ������ ����
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
				"������ ���� �� ����� ���� ������, ���� �� ����������. ����������� ��� ���?\n1) ��\n2) �����\n->");
			if (choice == '1')
			{
				std::cout << "������� ��� �����:\n->";
				getline(std::cin, filename);
			}
			else return NULL;
			fin->open(filename);
		}
		//�������������� ����������� ����� ������ �� ���������� ����
		std::cin.rdbuf(fin->rdbuf()); 
		return original_cin;
	}

	~IInputDevice() 
	{
		if (original_cin) 
			std::cin.rdbuf(original_cin); // ���������� �� ������������ ����� � ����������
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