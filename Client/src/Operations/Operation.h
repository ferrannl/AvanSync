#pragma once
#include <string>
#include <memory>

class Operation {
public:
	virtual void execute(std::string& data) = 0;
};
