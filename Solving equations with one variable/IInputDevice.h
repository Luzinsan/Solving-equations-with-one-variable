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
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

double getDouble(double min = 0, 
	double max = 1, 
	std::string = "", 
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

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

		std::string string;
		switch (method) 
		{
		case '1':
			
			while (true)
			{
				std::cout << "������� ���������:\n-> ";
				
				getline(std::cin, string);
				if (string.empty())
					std::cerr << "������ ���������� ������ ������.\n";		
				else expr.push_back(string);
				method = getSymbol({ '1','2' }, "1) ����������;\n2) ��������� ���� ������\n-> ");
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
					std::cerr << "������ ���������� ������ ������.\n";
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