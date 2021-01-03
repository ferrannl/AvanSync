#pragma once
#include "Operation.h"

class InfoOperation : public Operation
{
public:
	void execute(std::string& data) override;
};
