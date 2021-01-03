#include "PutCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::PutCommand::PutCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::PutCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
