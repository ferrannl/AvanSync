#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include "Controllers/MainController.h"

int main() {
	try {
		std::unique_ptr<Server::Controllers::MainController> _main = std::make_unique<Server::Controllers::MainController>();
		_main->run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex) {
		std::cerr << "server: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
