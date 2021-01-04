#include "OperationFactory.h"

OperationFactory::OperationFactory()
{
	_operations["INFO"] = std::make_shared<InfoOperation>();
	_operations["DIR"] = std::make_shared<DirOperation>();
	//_operations["GET"] = std::make_shared<DirOperation>();
	//_operations["PUT"] = std::make_shared<DirOperation>();
	//_operations["REN"] = std::make_shared<DirOperation>();
	//_operations["DEL"] = std::make_shared<DirOperation>();
	//_operations["MKDIR"] = std::make_shared<DirOperation>();
	//_operations["QUIT"] = std::make_shared<DirOperation>();
	//_operations["SYNC"] = std::make_shared<DirOperation>();
}

const std::shared_ptr<Operation> OperationFactory::GetOperation(const std::string& operation)
{
	if (_operations.count(operation) == 0)
	{
		return nullptr;
	}
	return _operations[operation];
}

