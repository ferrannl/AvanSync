#pragma once
#include "Operation.h"

class DirOperation : public Operation
{
public:
	void execute(std::string& data) override;
};
