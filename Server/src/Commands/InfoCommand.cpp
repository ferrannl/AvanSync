#include "InfoCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::InfoCommand::InfoCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::InfoCommand::execute(asio::ip::tcp::iostream& client, const std::string&)
{
	client << "AvanSync server 1.0, copyright (c) 2020 Bob Polis." << "\r\n";
}
