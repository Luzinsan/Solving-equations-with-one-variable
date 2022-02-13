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