#include "IInputDevice.h"

char getSymbol(std::initializer_list<char> list,
	std::string notification_message,
	std::string error_message)
{
	char choice = NULL;
	std::cout << notification_message;

	bool flag = true;
	do {
		choice = _getche();
		std::cout << std::endl;
		for (auto it = list.begin(); it != list.end(); it++)
			if (it[0] == choice) { flag = false; break; }

		if (flag) std::cerr << error_message;
	} while (flag);
	return choice;
}

double getDouble(double min, double max) 
{
	std::string epsstr;
	double eps;
	do {
		std::cout << "Введите погрешность вычислений (0 < eps < 1) (с разделяющей запятой ',')\n->";
		std::cin >> epsstr;
		bool point = false, flag = false;
		for (auto it = epsstr.begin(); it != epsstr.end(); it++)
			if (!isdigit(it[0]) && (it[0] != ',' || point))
			{
				std::cout << "Введено недопустимое значение\n";
				flag = true;
				break;
			}
			else if (it[0] == ',' && !point) point = true;

		if (flag) continue;
		eps = std::stod(epsstr);
		if (eps <= min || eps >= max)
			std::cout << "Погрешность не удовлетворяет условию. Попробуйте ещё раз.\n";
		else break;
	} while (true);
	return eps;
}