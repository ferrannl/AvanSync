#include "RenameCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::RenameCommand::RenameCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::RenameCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	std::filesystem::path p = "";

	if (path.front() == '"') {
		p = (path.substr(1, nthOccurrence(path, '"', 1) - 1));
	}
	else {
		p = (path.substr(0, path.length()));
	}

	std::string rest = path.substr(nthOccurrence(path, '"', 2), path.length() - 1);
	std::string name = "";
	if (path.front() == '"' && path.back() == '"') {
		name = rest.substr(nthOccurrence(rest, '"', 0), nthOccurrence(rest, '"', 1) - 1);
	}
	else {
		name = path.substr(p.string().length() + 1, path.length());
	}

	if (!std::filesystem::exists(p)) {
		stream << "Error: no such file or directory" << "\r\n";
		return;
	}

	auto dir = std::filesystem::directory_entry(p);
	auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		stream << "Error: Error: no permission" << "\r\n";
		return;
	}

	std::filesystem::rename(p, p.parent_path().append(name));
	std::ifstream input(p);

	stream << "OK" << "\r\n";
}
