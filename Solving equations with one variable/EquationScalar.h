#pragma once
#include <iomanip>
#include <iostream>
#include "PolStr.h"

class EquationScalar
{
private:
	double _a, _b, _eps;
	const char* _pstr;
	char _method;
	double _res;
	std::string _expr;
public:
	EquationScalar(const char* pstr, double a, double b, double eps, std::string expr, char method = '1'):
		_pstr{ pstr }, _a(a), _b(b), _eps(eps), _expr{expr}, _method(method)
	{
		setResult(_method);
	}
	~EquationScalar() 
	{
		delete[] _pstr;
	}


	std::string getType() const 
	{
		switch (_method)
		{
		case '1':
			return "Метод Дихотомии";
		case '2':
			return "Метод Хорд";
		case '3':
			return "Метод Золотого Сечения";
		case '4':
			return "Метод Ньютона";
		case '5':
			return "Метод Итераций";
		case '6':
			return "Комбинированный Метод";
		default:
			return "Не Обнаружен";
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const EquationScalar& expr)
	{
		int precision = std::cout.precision();
		out << expr.getType() << ": " << expr._expr << " = " << std::setprecision(precision) << expr._res << std::endl;
		return out;
	}

	double setResult(char choice)
	{
		_method = choice;
		switch (_method)
		{
		case '1':
			setDichotomyMethod();
			break;
		case '2':
			setChordMethod();
			break;
		case '3':
			setGoldenSectionMethod();
			break;
		case '4':
			setNewtonMethod();
			break;
		case '5':
			setIterationMethod();
			break;
		case '6':
			setCombinedMethod();
			break;
		default:
			throw std::invalid_argument("Не найден подходящий метод решения");
		}
	}

	//метод дихотомии
	double setDichotomyMethod()
	{
		double a = _a, b = _b, eps = _eps, c;
		while ((b - a) / 2 > eps)
		{
			c = (a + b) / 2;
			if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, c, 0) <= 0)
				b = c;
			else a = c;
		}
		_res = (a + b) / 2;
		return _res;
	}
	
	//метод хорд
	double setChordMethod() 
	{
		double a = _a, b = _b, eps = _eps;
		double c;
		double x; // начальное приближение
		if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, a, 2) > 0)
			x = a;
		else x = b;
		do {
			c = a - EvalPolStr(_pstr, a, 0) * (b - a)
				/ (EvalPolStr(_pstr, b, 0) - EvalPolStr(_pstr, a, 0));
			if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, c, 0) <= 0)
				b = c;
			else a = c;
			x = x - EvalPolStr(_pstr, x, 0) / EvalPolStr(_pstr, x, 1);
		} while (abs(c - x) > eps);
		_res = c;
		return c;
	}

	//метод золотого сечения
	double setGoldenSectionMethod() 
	{
		double a = _a, b = _b, eps = _eps;
		double c, d, h = (sqrt(5) + 1) / 2;
		while ((b - a) / 2 > eps)
		{
			d = a + (b - a) / h; // новая правая граница
			c = a + b - d; // c - a = b - d / или новая левая граница
			if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, d, 0) <= 0)
				b = d;
			else a = c;
		}
		_res = (a + b) / 2;
		return _res;
	}
	
	//метод Ньютона
	double setNewtonMethod() 
	{
		double a = _a, b = _b, eps = _eps;
		double x1;
		double x0; // начальное приближение
		if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, a, 2) > 0)
			x0 = a;
		else x0 = b;
		x1 = x0;
		do {
			x0 = x1;
			x1 = x1 - EvalPolStr(_pstr, x1, 0) / EvalPolStr(_pstr, x1, 1);
		} while (abs(x1 - x0) > eps);
		_res = x1;
		return x1;
	}

	//метод итераций
	double setIterationMethod() 
	{
		double a = _a, b = _b, eps = _eps;
		double x0 = (a + b) / 2; // начальное приближение
		a = EvalPolStr(_pstr, a, 1);
		b = EvalPolStr(_pstr, b, 1);
		double x1 = x0;
		do {
			x0 = x1;
			x1 = x1 - EvalPolStr(_pstr, x1, 0) / a > b ? a : b;
		} while (abs(x1 - x0) > eps);
		_res = x1;
		return _res;
	}

	//комбинированный метод
	double setCombinedMethod()
	{
		double a = _a, b = _b, eps = _eps;
		double c;
		do {
			c = a -				EvalPolStr(_pstr, a, 0)						* (b - a)
					/ (EvalPolStr(_pstr, b, 0) - EvalPolStr(_pstr, a, 0));
			if (EvalPolStr(_pstr, a, 0) * EvalPolStr(_pstr, a, 2) > 0)
			{
				a = a - EvalPolStr(_pstr, a, 0) / EvalPolStr(_pstr, a, 1);
				b = c;
			}
			else
			{
				a = c;
				b = b - EvalPolStr(_pstr, b, 0) / EvalPolStr(_pstr, b, 1);
			}

		} while ((b - a) / 2 > eps);
		_res = (a + b) / 2;
		return _res;
	}
};

