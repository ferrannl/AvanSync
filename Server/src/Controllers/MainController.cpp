#include <string>
#include <stdexcept>
#include <asio.hpp>
#include <iostream>
#include <cstdlib>
#include "MainController.h"

using namespace Server;

Controllers::MainController::MainController() {};

void Server::Controllers::MainController::run() {

	_factory = { shared_from_this() };
	const int server_port{ 12345 };
	const char* lf{ "\n" };
	const char* crlf{ "\r\n" };

	asio::io_context io_context;
	asio::ip::tcp::acceptor server{ io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), server_port) };

	for (;;) {
		std::cerr << "waiting for client to connect\n";
		asio::ip::tcp::iostream client;
		server.accept(client.socket());
		std::cerr << "client connected from " << client.socket().local_endpoint() << lf;
		client << "Welcome to AvanSync server 1.0" << crlf;
		for (;;) {
			std::string request;
			getline(client, request);
			request.erase(request.end() - 1); // remove '\r'
			std::cerr << "client says: " << request << lf;

			std::string cmd = "";
			std::string rest = "";

			try {
				cmd = request.substr(0, request.find(" "));
				rest = request.substr(request.find(" ") + 1, request.length());
			}
			catch (const std::exception& e) {
			}

			if (cmd == "") {
				cmd = request;
			}

			runCommand(cmd, rest);

			if (request == "disconnect") {
				break;
			}
		}
	}
}

void Controllers::MainController::runCommand(const std::string& command, const std::string& path) {
	if (command == "info") {
		_factory.get_command(Enums::CommandEnum::GET_SERVER_INFO)->execute(_client);
	}
	else if (command == "dir") {
		_factory.get_command(Enums::CommandEnum::GET_DIRECTORY_LISTING)->execute(_client, path);
	}
	else if (command == "disconnect") {
		_factory.get_command(Enums::CommandEnum::DISCONNECT)->execute(_client);
	}
	else if (command == "download") {
		_factory.get_command(Enums::CommandEnum::DOWNLOAD_FILE)->execute(_client, path);
	}
	else if (command == "rename") {
		_factory.get_command(Enums::CommandEnum::RENAME)->execute(_client, path);
	}
	else if (command == "remove") {
		_factory.get_command(Enums::CommandEnum::DELETE_ITEM)->execute(_client, path);
	}
	else if (command == "create") {
		_factory.get_command(Enums::CommandEnum::CREATE_DIR)->execute(_client, path);
	}
	else {
		_client << "Invalid Command" << "\r\n";
	}
}

//if (request == "quit") {
//	client << "Bye." << crlf;
//	std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
//	break;
//}
//else {
//	//fills response list
//	commandoController->runCommand(request);
//	//gets response list
//	std::vector<std::string> responseList = commandoController->get_response();
//	//loops through response list
//	std::string reponse = {};
//	for (std::string line : responseList)
//	{
//		reponse += line;
//	}
//	client << reponse << crlf;
//}