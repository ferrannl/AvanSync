#include "DelOperation.h"

#include <iostream>

void DelOperation::execute(std::string& data)
{
	std::string path;
	data.append("DEL\r\n");
	std::cout << "Enter path: ";
	getline(std::cin, path);
	data.append(path);
}