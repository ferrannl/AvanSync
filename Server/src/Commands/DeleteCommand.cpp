#include "DeleteCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>

Server::Commands::DeleteCommand::DeleteCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DeleteCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	std::filesystem::path p(path.substr(0, path.find(" ")));
	std::string name = path.substr(path.find(" ") + 1, path.length());

	if (path.front() == '"' && path.back() == '"') {
		p = (path.substr(1, path.length() - 2));
	}
	else {
		p = (path.substr(0, path.length()));
	}

	if (!std::filesystem::exists(p)) {
		stream << "Error: no such file or directory" << "\r\n";
		return;
	}

	auto dir = std::filesystem::directory_entry(p);
	auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		stream << "Error: no permission" << "\r\n";
		return;
	}

	std::filesystem::remove(p);

	stream << "OK" << "\r\n";
}
