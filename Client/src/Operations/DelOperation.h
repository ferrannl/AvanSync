#pragma once
#include "Operation.h"
class DelOperation :
	public Operation
{
	void execute(std::string& data) override;
};
