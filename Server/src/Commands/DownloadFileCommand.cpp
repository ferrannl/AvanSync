#include "DownloadFileCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::DownloadFileCommand::DownloadFileCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::DownloadFileCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	const char* crlf{ "\r\n" };

	std::filesystem::path p(path.substr(0, path.length()));
	
	if (!std::filesystem::exists(p)) {
		stream << "Error: no such file" << "\r\n";
		return;
	}

	//auto bytes = std::filesystem::file_size(p);
	//stream << "File has " << bytes << " bytes" << "\r\n";

	std::ifstream input(p, std::ios::binary);
	if (input.good()) {

		std::ofstream output("C:\\myfile.gif", std::ios::binary);

		std::copy(
			std::istreambuf_iterator<char>(input),
			std::istreambuf_iterator<char>(),
			std::ostreambuf_iterator<char>(output));
	}
	else {
		stream << "Error: Cannot read file" << "\r\n";
	}

	return;
}
