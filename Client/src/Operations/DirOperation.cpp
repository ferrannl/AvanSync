#include "../Operations/DirOperation.h"
#include <iostream>

void DirOperation::execute(std::string& data) {
	std::string path;

	data.append("DIR\r\n");
	std::cout << "Enter path:";
	getline(std::cin, path);
	data.append(path);
}