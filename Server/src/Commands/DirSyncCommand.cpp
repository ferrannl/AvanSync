#include "DirSyncCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::DirSyncCommand::DirSyncCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::DirSyncCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
