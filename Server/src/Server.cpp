//
// server.cpp
//
// Created by Bob Polis at 2020-12-02
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include "Controllers/MainController.h"

int main() {
    try {
        std::shared_ptr<Server::Controllers::MainController> _main = std::make_shared<Server::Controllers::MainController>();
        _main->run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
    }
    catch (...) {
        std::cerr << "Unknown Error" << '\n';
    }
    return EXIT_FAILURE;
}
