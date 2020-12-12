#include "CommandoController.h"

using namespace Controllers;

CommandoController::CommandoController()
{
	_response = {};
}

std::string CommandoController::runCommand(const std::string& command)
{
	if (command.find("info") == 0) {
		return info();
	}
	if (command.find("dir") == 0) {
		return dir();
	}
	if (command.find("get") == 0) {
		return get();
	}
	if (command.find("put") == 0) {
		return put();
	}
	if (command.find("ren") == 0) {
		return ren();
	}
	if (command.find("del") == 0) {
		return del();
	}
	if (command.find("mkdir") == 0) {
		return mkdir();
	}
	if (command.find("quit") == 0) {
		return quit();
	}
	return "unknown command";
}

std::string CommandoController::info()
{
	_response = { "AvanSync server 1.0, copyright (c) 2020 Bob Polis, glashelder." };
	return _response;
}

std::string CommandoController::dir()
{
	return _response;
}

std::string CommandoController::get()
{
	return _response;
}

std::string CommandoController::put()
{
	return _response;
}

std::string CommandoController::ren()
{
	return _response;
}

std::string CommandoController::del()
{
	return _response;
}

std::string CommandoController::mkdir()
{
	return _response;
}

std::string CommandoController::quit()
{
	return _response;
}
