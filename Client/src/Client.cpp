#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include <filesystem>
#include <fstream>
#include <map>
namespace fs = std::filesystem;

template <typename TP>
std::time_t to_time_t(const TP& tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

void info(const std::string& req, asio::ip::tcp::iostream& server) {

	server << req << "\r\n";
}

void dir(asio::ip::tcp::iostream& server)
{
	std::string req;
	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result))
	{
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			const int iterations = std::stoi(result);
			for (int i = 0; i < iterations; ++i)
			{
				if (getline(server, result))
				{
					std::cout << result << "\n";
				}
			}
		}
	}
}

void mkdir(asio::ip::tcp::iostream& server) {
	std::string req;

	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		std::cout << result + "\n";
	}
}

void ren(asio::ip::tcp::iostream& server) {
	std::string req;

	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		std::cout << result + "\n";
	}
}

void del(asio::ip::tcp::iostream& server) {
	std::string req;
	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			std::cout << result + "\n";
		}
	}
}

void get(asio::ip::tcp::iostream& server) {
	const std::string client_path = "C:\\temp\\client\\result\\";
	std::string req;
	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			int iterations = std::stoi(result);
			std::cout << iterations << "\n";
			std::string byte;
			char* bytes = new char[iterations];
			server.read(bytes, iterations);
			for (int i = 0; i < iterations; i++) {
				std::cout << bytes[i] << "\n";
			}
			std::ofstream streamresult(client_path + fs::path(req).filename().string(), std::ofstream::binary);
			streamresult.write(bytes, iterations);
			streamresult.close();
		}
	}
}

void put(asio::ip::tcp::iostream& server) {
	std::string path;
	if (getline(std::cin, path)) {
		server << path << "\r\n";
	}
	std::string result;
	if (getline(std::cin, result))
	{
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			server << result << "\r\n";
			try {
				const int file_size = std::stoi(result);
				const std::shared_ptr<char> buffer(new char[file_size], std::default_delete<char[]>());
				std::ifstream input(path, std::ios::binary);
				input.read(buffer.get(), file_size);
				server.write(buffer.get(), file_size);
				std::string end;
				if (getline(server, end)) {
					std::cout << end << "\n";
				}
			}
			catch (std::exception e)
			{
				std::cout << "Error: " << e.what() << "\r\n";
				return;
			}
		}

	}
}

void put_server(const std::string& req, const int bytes, asio::ip::tcp::iostream& server)
{
	std::ifstream stream(req, std::ios::binary);
	const std::shared_ptr<char> buffer(new char[bytes], std::default_delete<char[]>());
	stream.read(buffer.get(), bytes);
	server.write(buffer.get(), bytes);
}

void sync_server(asio::ip::tcp::iostream& server, const std::filesystem::directory_entry& entry)
{
	const std::string _path_server = "C:\\temp\\server\\";
	const std::string _path_client = "C:\\temp\\client\\";

	server << "put" << "\r\n";
	server << entry.path().filename().string() << "\r\n";
	const int bytes = fs::file_size(fs::path(_path_client + entry.path().filename().string()));
	server << fs::file_size(fs::path(_path_client + entry.path().filename().string())) << "\r\n";

	put_server(_path_client + entry.path().filename().string(), bytes, server);
}

void sync(asio::ip::tcp::iostream& server) {
	const std::string _path_server = "C:\\temp\\server\\";
	const std::string _path_client = "C:\\temp\\client\\";
	server << "dir" << "\r\n";
	server << _path_server << "\r\n";
	std::string result;
	std::vector<std::map<std::string, std::string>> dirs = {};
	if (getline(server, result))
	{
		int iterations = std::stoi(result);
		for (int i = 0; i < iterations; ++i)
		{
			if (getline(server, result))
			{
				std::string segment;
				result.erase(result.end() - 1);
				std::stringstream test(result);
				std::map<std::string, std::string> total;
				int counter = 0;
				while (std::getline(test, segment, '|'))
				{
					switch (counter)
					{
					case 0:
						total["isdir"] = segment;
						counter++;
						break;
					case 1:
						total["filename"] = segment;
						counter++;
						break;
					case 2:
						total["writetime"] = segment;
						counter++;
						break;
					case 3:
						total["filesize"] = segment;
						counter++;
						break;
					}
				}
				dirs.push_back(total);
			}
		}
	}

	std::vector<std::string> _files;
	for (auto& p : fs::directory_iterator(_path_client))
	{
		auto test = fs::last_write_time(p.path());
		std::time_t tt = to_time_t(test);
		std::tm* gmt = std::localtime(&tt);
		std::stringstream buffer;
		buffer << std::put_time(gmt, "%F %T");
		bool exists_in_server = false;
		bool newer_version = false;
		for (auto& file : dirs)
		{
			if (p.path().filename() == file["filename"])
			{
				exists_in_server = true;
				file["exists"] = "true";
				if (buffer.str() > file["writetime"])
				{
					newer_version = true;
				}
			}

		}
		if (!exists_in_server || newer_version)
		{
			std::string path = _path_server + p.path().string().substr(_path_client.length(), p.path().string().length());
			server << "put" << "\r\n";
			server << path << "\r\n";
			server << p.file_size() << "\r\n";
			const std::shared_ptr<char> buffer(new char[p.file_size()], std::default_delete<char[]>());
			std::ifstream input(p.path(), std::ios::binary);
			input.read(buffer.get(), p.file_size());
			server.write(buffer.get(), p.file_size());
		}
	}
	for (auto& file : dirs)
	{
		if (file["exists"] != "true")
		{
			std::string path = _path_server + file["filename"];
			server << "del" << "\r\n";
			server << path << "\r\n";
		}
	}
}
/*server << "dir" << "\r\n";
server << _path_server << "\r\n";
std::string result;
std::vector<std::map<std::string, std::string>> paths = {};
if (getline(server, result))
{
	const int iterations = std::stoi(result);
	for (int i = 0; i < iterations; ++i)
	{
		if (getline(server, result))
		{
			std::string seg;
			result.erase(result.end() - 1);
			std::stringstream str(result);
			std::map<std::string, std::string> map;
			int counter = 0;
			while (std::getline(str, seg, '|'))
			{
				switch (counter)
				{
				case 0:
					map["isdir"] = seg;
					++counter;
					break;
				case 1:
					map["filename"] = seg;
					++counter;
					break;
				case 2:
					map["last_modified"] = seg;
					++counter;
					break;
				case 3:
					map["filesize"] = seg;
					++counter;
					break;
				}
			}
			paths.push_back(map);
		}
	}
	std::vector<std::string> _files;
	for (const auto& p : fs::recursive_directory_iterator(_path_client))
	{
		auto test = fs::last_write_time(p.path());
		std::time_t tt = to_time_t(test);
		std::tm* gmt = std::localtime(&tt);
		std::stringstream buffer;
		buffer << std::put_time(gmt, "%F %T");
		bool exists_in_server = false;
		bool newer_version = false;
		for (auto& file : paths)
		{
			if (fs::path(p).filename() == file["filename"])
			{
				exists_in_server = true;
				file["exists"] = "true";
				if (buffer.str() > file["last_modified"])
				{
					newer_version = true;
				}
			}
		}
		if (!exists_in_server || newer_version)
		{
			if (p.is_directory())
			{
				server << "mkdir" << "\r\n";
				server << p.path() << "\r\n";
				server << p.path().filename().string() << "\r\n";
			}
			else
			{
				sync_server(server, p);
			}
		}
	}
	for (auto& file : paths)
	{
		if (file["exists"] != "true")
		{
			std::string path = _path_server + file["filename"];
			server << "del" << "\r\n";
			server << path << "\r\n";
		}
	}*/

void quit(const std::string& req, asio::ip::tcp::iostream& server) {
	server << req << "\r\n";
}

int main() {
	try {
		const char* server_address{ "localhost" };
		const char* server_port{ "12345" };
		const char* prompt{ "avansync> " };
		const char* lf{ "\n" };
		const char* crlf{ "\r\n" };

		asio::ip::tcp::iostream server{ server_address, server_port };
		if (!server) throw std::runtime_error("could not connect to server");

		while (server) {
			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
				std::cout << resp << lf;
				if (resp == "Bye.") break;

				std::cout << prompt;
				std::string req;
				if (getline(std::cin, req)) {
					if (req.find("sync") == 0)
					{
						sync(server);
					}
					server << req << crlf;
					if (req.find("dir") == 0)
					{
						dir(server);
					}
					else if (req.find("del") == 0) {
						del(server);
					}
					else if (req.find("info") == 0) {
						info(req, server);
					}
					else if (req.find("mkdir") == 0) {
						mkdir(server);
					}
					else if (req.find("ren") == 0) {
						ren(server);
					}
					else if (req.find("quit") == 0) {
						quit(req, server);
					}
					else if (req.find("put") == 0) {
						put(server);
					}
					else if (req.find("get") == 0) {
						get(server);
					}
					else
					{

					}
				}
			}
		}

	}
	catch (const std::exception& ex) {
		std::cerr << "client: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
