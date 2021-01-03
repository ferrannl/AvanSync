#include "NewDirCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::NewDirCommand::NewDirCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::NewDirCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	std::filesystem::path p(path.substr(0, path.find(" ")));
	std::string existing = path.substr(path.find(" ") + 1, path.length());

	if (!std::filesystem::exists(existing)) {
		stream << "Error: no such file or directory" << "\r\n";
		return;
	}

	auto dir = std::filesystem::directory_entry(existing);
	auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		stream << "Error: Error: no permission" << "\r\n";
		return;
	}

	std::filesystem::create_directory(p, existing);

	stream << "OK" << "\r\n";
}
