#define _CRT_SECURE_NO_WARNINGS

#include "DirCommand.h"
#include "../Controllers/MainController.h"
#include <filesystem>
#include <time.h>
#include <ctime>

Server::Commands::DirCommand::DirCommand(std::shared_ptr<Controllers::MainController> main) : Command{ main }
{
}

void Server::Commands::DirCommand::execute(asio::ip::tcp::iostream& stream, std::string& data)
{
	const char* crlf{ "\r\n" };

	std::string p;
	getline(stream, p);
	p.erase(p.end() - 1);

	const std::filesystem::path p2(p);
	std::string type;

	if (!std::filesystem::exists(p)) {
		stream << "Error: no such directory" << "\r\n";
		return;
	}

	std::ostringstream oss;
	try {
		if (std::filesystem::is_directory(p2))
		{
			for (const auto& entry : std::filesystem::directory_iterator(p2)) {
				if (entry.is_directory()) {
					type = "D";
				}
				else if (entry.is_regular_file()) {
					type = "F";
				}
				else {
					type = "*";
				}

				std::time_t last_time = to_time_t<decltype(entry.last_write_time())>(entry.last_write_time());
				std::tm* tmObj{ std::localtime(&last_time) };

				std::string time = std::to_string(tmObj->tm_mday) + "-" + std::to_string(tmObj->tm_mon) + "-" + std::to_string(tmObj->tm_year + 1900) + +" " + std::to_string(tmObj->tm_hour) + "-" + std::to_string(tmObj->tm_min) + "-" + std::to_string(tmObj->tm_sec);

				auto size = entry.file_size();
				std::string name = entry.path().filename().string();

				oss << type << "|" << name << "|" << time << "|" << size << "\r\n";
			}
			data.append(oss.str());
			data.pop_back();
			data.pop_back();
		}
		else
		{
			data.append("Error: path not found");
		}
	}
	catch (...) {
		data.append("Error: something went wrong while reading the files");
	}
}