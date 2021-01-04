#include "MainController.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>

using namespace Server;

Controllers::MainController::MainController() {}

void Server::Controllers::MainController::run()
{
	_factory = { shared_from_this() };
	const int server_port{ 12345 };
	const char* lf{ "\n" };
	const char* crlf{ "\r\n" };

	asio::io_context io_context;
	asio::ip::tcp::acceptor server{ io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), server_port) };

	for (;;) {
		std::cerr << "waiting for client to connect\n";
		server.accept(_client.socket());
		std::cerr << "client connected from " << _client.socket().local_endpoint() << lf;
		_client << "Welcome to AvanSync server 1.0" << crlf;

		for (;;) {
			std::string request;

			getline(_client, request);

			request.erase(request.end() - 1); // remove '\r'

			std::cerr << "client says: " << request << lf;

			std::string command = "";
			std::string rest = "";

			try {
				command = request.substr(0, request.find(" "));
			}
			catch (const std::exception& e) {
			}

			if (command == "") {
				command = request;
			}

			processCommand(command, rest);
			_client << rest << crlf;
			if (request == "disconnect") {
				break;
			}
		}
	}
}

void Controllers::MainController::processCommand(const std::string& command, std::string& rest)
{
	if (command == "INFO") {
		_factory.get_command(Enums::CommandEnum::GET_SERVER_INFO)->execute(_client);
	}
	else if (command == "DIR") {
		_factory.get_command(Enums::CommandEnum::GET_DIRECTORY_LISTING)->execute(_client, rest);
	}
	else if (command == "GET") {
		_factory.get_command(Enums::CommandEnum::DOWNLOAD_FILE)->execute(_client, rest);
	}
	else if (command == "PUT") {
		_factory.get_command(Enums::CommandEnum::UPLOAD_FILE)->execute(_client, rest);
	}
	else if (command == "REN") {
		_factory.get_command(Enums::CommandEnum::RENAME)->execute(_client, rest);
	}
	else if (command == "DEL") {
		_factory.get_command(Enums::CommandEnum::DELETE_ITEM)->execute(_client, rest);
	}
	else if (command == "MKDIR") {
		_factory.get_command(Enums::CommandEnum::CREATE_DIRECTORY)->execute(_client, rest);
	}
	else if (command == "QUIT") {
		_factory.get_command(Enums::CommandEnum::DISCONNECT)->execute(_client);
	}
	else {
		_client << "Invalid Command" << "\r\n";
	}
}