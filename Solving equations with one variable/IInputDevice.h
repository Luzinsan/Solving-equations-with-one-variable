#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
//#include <iomanip>

char getSymbol(std::initializer_list<char> list,
	std::string notification_message = "",
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

double getDouble(double min = -DBL_MAX,
	double max = DBL_MAX,
	std::string = "", 
	std::string error_message = "������������ ��������, ���������� ��� ���.\n->");



class IInputDevice
{
private:
	std::streambuf* _original_cin;
	std::ifstream* _fin;
	std::vector<std::string> _expr;
	char _method;
	int _NAfterComma;
	double _eps;
	double _a, _b;
public:

	IInputDevice(char choice = '1') 
		: _original_cin{ NULL },
		  _fin{ NULL }  
	{
		switch (choice)
		{
		case '1': 
			_a = getDouble(-DBL_MAX, DBL_MAX, "������� ����� ������� ���������\n-> ");
			_b = getDouble(-DBL_MAX, DBL_MAX, "������� ������ ������� ���������\n-> ");
			_NAfterComma = setNAfterComma();
			break;
		case '2':
		{
			std::string filename;
			std::cout << "������� ��� �������� �����:\n->";
			getline(std::cin, filename);
			_fin = new std::ifstream(filename);
			//��������� ������ ����� ������ � ����� � �������������� ����������� ����� �� ���������������� ����
			_original_cin = redirectInput(_fin);
			if (!_original_cin)  choice = '4';
			break;
		}
		case '3':
			_fin = new std::ifstream("input.txt");
			//��������� ������ ����� � �������������� ����������� ����� �� ���� input.txt
			_original_cin = redirectInput(_fin);
			if (!_original_cin) choice = '4';
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
				else _expr.push_back(string);
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
				if (!string.empty()) { _expr.push_back(string); continue; }
				if (_expr.empty())
					std::cerr << "������ ���������� ������ ������.\n";
				break;
			}
			_method = _expr[0][0];
			std::stringstream stream(_expr[2]);
			getline(stream, string, ' ');
			_a = std::stod(string);
			getline(stream, string, ' ');
			_b = std::stod(string);
			_eps = std::stod(_expr[3]);
			_NAfterComma = setNAfterComma(_eps);
			// ����� ��� ������ ������, ������ ���������� ��������� � ������ ������� � ������� �� ��������
			// ��� �����, ��� ��� ��� ���������� � ����������, expr ����� ������� ������ ���������, 
			// ������ ��������� �� ����� ������ ����
			_expr[0] = _expr[1];
			_expr.resize(1);
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
		//�������������� ����������� ����� ����� �� ���������� ����
		std::cin.rdbuf(fin->rdbuf()); 
		return original_cin;
	}

	

	~IInputDevice() 
	{
		if (_original_cin) 
			std::cin.rdbuf(_original_cin); // ���������� �� ������������ ����� � ����������
		if(_fin)
			_fin->close();
	}

	bool isEmptyVectorString()
	{
		return _expr.empty();
	}
	std::vector<std::string> getVectorString() 
	{ 
		return _expr; 
	}

	double getLeft() { return _a; }
	double getRight() { return _b; }
	double getEps() { return _eps; }
	int getNAfterComma() { return _NAfterComma; }
	char getMethod() { return _method; }

	void setMethod(char method)
	{
		if (method < '1' || method > '6') throw std::invalid_argument("������������ �������� ������");
		_method = method;
	}

	int setNAfterComma(double eps = 0.0)
	{
		//char choice = getSymbol({ '1', '2' },
		//	"�������� ��� �����������:\n1) ���������� �����������\n2) ������������� �����������\n-> ");
	
		if(!eps)
			_eps = getDouble(0, 1,
				"������� ����������� ���������� (0 < eps < 1) (� ����������� ������� ',')\n->",
				"����������� �� ������������� �������. ���������� ��� ���.\n");
			
		
		//if (choice == '1')
			return -std::ceil(log(_eps));
		//else
		//	return  1 - log(1 * _eps);
	}
};
#endif
