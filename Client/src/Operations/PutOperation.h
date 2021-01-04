#pragma once
#include "Operation.h"
class PutOperation :
	public Operation
{
	void execute(std::string& data) override;
};

