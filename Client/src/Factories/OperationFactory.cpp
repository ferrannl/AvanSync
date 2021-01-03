#include "OperationFactory.h"
#include "../Operations/DirOperation.h"
#include "../Operations/InfoOperation.h"

OperationFactory::OperationFactory()
{
	_operations["INFO"] = std::make_shared<InfoOperation>();
	_operations["DIR"] = std::make_shared<DirOperation>();
}

const std::shared_ptr<Operation> OperationFactory::GetOperation(const std::string& operation)
{
	if (_operations.count(operation) == 0)
	{
		return nullptr;
	}
	return _operations[operation];
}

