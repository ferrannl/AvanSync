#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <asio.hpp>
#include "Controllers/MainController.h"

int main() {
	try {
		_CrtDumpMemoryLeaks();

		const int server_port{ 12345 };
		const char* lf{ "\n" };
		const char* crlf{ "\r\n" };
		const std::unique_ptr<Controllers::MainController> main_controller = std::make_unique<Controllers::MainController>();

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
				if (!request.empty()) {
					request.erase(request.end() - 1); // remove '\r'
				}
				std::cerr << "client says: " << request << lf;
				main_controller->get_right_command(request, client);

				if (request == "quit") {
					client << "Bye." << crlf;
					std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
					break;
				}
			}
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "server: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
