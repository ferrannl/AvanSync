#pragma once
#include <string>
#include <memory>
#include "../Operations/Operation.h"
#include <map>

class OperationFactory {
private:
	std::map< std::string, std::shared_ptr<Operation>> _operations;

public:
	OperationFactory();
	const std::shared_ptr<Operation> GetOperation(const std::string& operation);
};
