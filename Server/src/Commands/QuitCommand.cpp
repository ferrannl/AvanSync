#include "QuitCommand.h"
#include "../Controllers/MainController.h"

Server::Commands::QuitCommand::QuitCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::QuitCommand::execute(asio::ip::tcp::iostream& stream, const std::string&)
{
	stream << "Bye." << "\r\n";
	std::cerr << "will disconnect from client " << stream.socket().local_endpoint() << "\n";
}
