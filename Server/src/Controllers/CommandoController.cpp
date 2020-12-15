#include "CommandoController.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace Controllers;

CommandoController::CommandoController()
{
	_response = {};
}

void CommandoController::runCommand(const std::string& command)
{
	_response.clear();
	if (command.find("info") == 0) {
		info();
	}
	else if (command.find("dir") == 0) {
		dir(command.substr(3, command.length() - 3));
	}
	else if (command.find("get") == 0) {
		get();
	}
	else if (command.find("put") == 0) {
		put();
	}
	else if (command.find("ren") == 0) {
		ren();
	}
	else if (command.find("del") == 0) {
		del();
	}
	else if (command.find("mkdir") == 0) {
		mkdir();
	}
	else if (command.find("quit") == 0) {
		quit();
	}
	else {
		_response.push_back("Error.");
	}
}

void CommandoController::info()
{
	_response.push_back("AvanSync server 1.0, copyright (c) 2020 Bob Polis, glashelder.");
}

void CommandoController::dir(const std::string& path)
{
	//std::string path1 = "C:/Users/Ferran/Documents/Git_repos/CPP2-Eindopdracht/AvanSync";
	for (const auto& entry : fs::directory_iterator(path))
		_response.push_back(entry.path().string() + "");
}

void CommandoController::get()
{
	_response.push_back("kanker GET");
}

void CommandoController::put()
{
}

void CommandoController::ren()
{
}

void CommandoController::del()
{
}

void CommandoController::mkdir()
{
}

void CommandoController::quit()
{
}

std::vector<std::string> Controllers::CommandoController::get_response()
{
	return _response;
}
