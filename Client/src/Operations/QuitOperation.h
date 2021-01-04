#pragma once
#include "Operation.h"
class QuitOperation :
	public Operation
{
	void execute(std::string& data) override;
};
