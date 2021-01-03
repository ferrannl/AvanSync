#include "GetServerInfoCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::GetServerInfoCommand::GetServerInfoCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::GetServerInfoCommand::execute(asio::ip::tcp::iostream& client, const std::string&)
{
	client << "AvanSync server 1.0, copyright (c) 2020 Bob Polis." << "\r\n";
}
