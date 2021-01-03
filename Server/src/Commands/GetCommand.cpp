#include "GetCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <fstream>

Server::Commands::GetCommand::GetCommand(std::shared_ptr<Controllers::MainController> main) : BaseCommand{ main }
{
}

void Server::Commands::GetCommand::execute(asio::ip::tcp::iostream& stream, const std::string& path)
{
	const char* crlf{ "\r\n" };

	std::filesystem::path p(path.substr(0, path.length()));

	if (!std::filesystem::exists(p)) {
		stream << "Error: no such file" << "\r\n";
		return;
	}

	std::uintmax_t size = std::filesystem::file_size(p);
	stream << "File is " << size << " bytes" << "\r\n";
	stream << "File is " << size << " bytes " << "\r\n";

	std::ifstream input(p, std::ios::binary);
	if (input.good()) {

		//"C:\temp\test.txt"
		//C:\temp\test.txt
		std::ofstream output("C:\\temp\\test.txt", std::ios::binary);
		auto bytes = { "Size of the file is" };
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

unsigned char* return_byte(unsigned char source)
{
	static unsigned char byte[CHAR_BIT];
	unsigned char* p = byte, i;

	for (i = 0; i < CHAR_BIT; i++)
		p[i] = '0' + ((source & (1 << i)) > 0);

	return p;
}
