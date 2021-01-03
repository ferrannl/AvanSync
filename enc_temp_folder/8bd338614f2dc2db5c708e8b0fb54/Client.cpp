#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include "Controllers/MainController.h"
#include "Factories/OperationFactory.h"

int main() {
	try {
		const char* server_address{ "localhost" };
		const char* server_port{ "12345" };
		const char* prompt{ "avansync> " };
		const char* lf{ "\n" };
		const char* crlf{ "\r\n" };
		std::unique_ptr<OperationFactory> _operationFactory{ std::make_unique<OperationFactory>() };
		_operationFactory->GetOperation("HOI");
		asio::ip::tcp::iostream server{ server_address, server_port };
		if (!server) throw std::runtime_error("could not connect to server");

		while (server) {
			std::string resp;
			std::string requestType;

			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
				std::cout << resp << lf;

				if (resp == "Bye.") break;

				if (!requestType.empty())
				{
					if (requestType == "DIR") {
						int itemCount = std::stoi(resp);
						resp.clear();

						for (int i = 0; i < itemCount; ++i) {
							std::string currentItem;
							getline(server, currentItem);
							std::cout << currentItem << lf;
						}
					}
					else if (requestType == "GET") {

					}
				}

				std::cout << prompt;
				std::string req;
				std::string data;

				if (getline(std::cin, req)) {
					if (requestType.empty()) {
						if (_operationFactory->GetOperation(req) != nullptr) {
							requestType = req;
							_operationFactory->GetOperation(req)->execute(data);
						}
					}
					server << data << crlf;
				}
			}
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "client: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
