#include "UploadFileCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::UploadFileCommand::UploadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::UploadFileCommand::execute(asio::ip::tcp::iostream&, const std::string&)
{
}
