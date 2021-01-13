#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
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

void info(const std::string& request, asio::ip::tcp::iostream& server) {
	server << request << "\r\n";
}

void dir(asio::ip::tcp::iostream& server)
{
	std::string request;
	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	std::string result;
	if (getline(server, result))
	{
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			const int it = std::stoi(result);
			for (int i = 0; i < it; ++i)
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
	std::string request;

	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		std::cout << result + "\n";
	}
}

void ren(asio::ip::tcp::iostream& server) {
	std::string request;

	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		std::cout << result + "\n";
	}
}

void del(asio::ip::tcp::iostream& server) {
	std::string request;
	if (getline(std::cin, request)) {
		server << request << "\r\n";
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
	const std::string _path_client = "C:\\temp\\client\\result\\";
	std::string request;
	if (getline(std::cin, request)) {
		server << request << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		if (result.rfind("Error:", 0) == 0)
		{
			std::cout << result << "\n";
		}
		else {
			const int iterations = std::stoi(result);
			std::cout << iterations << "\n";
			std::string byte;
			const std::shared_ptr<char> bytes(new char[iterations], std::default_delete<char[]>());

			server.read(bytes.get(), iterations);
			for (int i = 0; i < iterations; i++) {
				std::cout << bytes.get()[i] << "\n";
			}
			std::ofstream streamresult(_path_client + fs::path(request).filename().string(), std::ofstream::binary);
			streamresult.write(bytes.get(), iterations);
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
			return;
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
			catch (const std::exception& e)
			{
				std::cout << "Error: " << e.what() << "\r\n";
				return;
			}
		}
	}
}

void put_server(const std::string& request, const int bytes, asio::ip::tcp::iostream& server)
{
	std::ifstream stream(request, std::ios::binary);
	const std::shared_ptr<char> buffer(new char[bytes], std::default_delete<char[]>());
	stream.read(buffer.get(), bytes);
	server.write(buffer.get(), bytes);
}

void sync_server(asio::ip::tcp::iostream& server, const std::filesystem::directory_entry& dir_entry)
{
	const std::string _path_client = "C:\\temp\\client\\";

	server << "put" << "\r\n";
	server << dir_entry.path().filename().string() << "\r\n";
	const int bytes = fs::file_size(fs::path(_path_client + dir_entry.path().filename().string()));
	server << fs::file_size(fs::path(_path_client + dir_entry.path().filename().string())) << "\r\n";

	put_server(_path_client + dir_entry.path().filename().string(), bytes, server);
}

void sync(asio::ip::tcp::iostream& server) {
	const std::string _path_server = "C:\\temp\\server\\";
	int resp_ctr = 0;
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
		return;
	}

	std::vector<std::string> _files;
	const std::string _path_client = "C:\\temp\\client\\";
	for (auto& directory_entry : fs::recursive_directory_iterator(_path_client))
	{
		auto test = fs::last_write_time(directory_entry.path());
		std::time_t tt = to_time_t(test);
		std::stringstream buffer;
		buffer << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
		bool exists_in_server = false;
		bool newer_version = false;
		for (auto& file : dirs)
		{
			if (directory_entry.path().filename() == file["filename"])
			{
				exists_in_server = true;
				if (buffer.str() > file["writetime"])
				{
					newer_version = true;
				}
			}
		}
		if (!exists_in_server || newer_version)
		{
			if (directory_entry.is_directory())
			{
				server << "mkdir" << "\r\n";
				int name = directory_entry.path().filename().string().length();
				int text = _path_client.length();
				std::string dir_path = directory_entry.path().string().substr(0, directory_entry.path().string().length() - name);
				std::string str_without_dir_path = dir_path.substr(text, dir_path.length());
				std::string parent_dir = _path_server + str_without_dir_path;
				server << parent_dir << "\r\n";
				server << directory_entry.path().filename().string() << "\r\n";
				std::string response;
				if (getline(server, response))
				{
				}
				if (resp_ctr <= 12)
				{
					if (getline(server, response))
					{
					}
					++resp_ctr;
				}
			}
			else {
				std::string path = _path_client + directory_entry.path().string().substr(_path_client.length(), directory_entry.path().string().length());
				server << "put" << "\r\n";
				server << path << "\r\n";
				server << directory_entry.file_size() << "\r\n";
				std::shared_ptr<char> buffer(new char[directory_entry.file_size()], std::default_delete<char[]>());
				std::ifstream input(directory_entry.path(), std::ios::binary);
				input.read(buffer.get(), directory_entry.file_size());
				server.write(buffer.get(), directory_entry.file_size());
				std::string response;
				if (getline(server, response))
				{
				}
				if (resp_ctr <= 12)
				{
					if (getline(server, response))
					{
					}
					++resp_ctr;
				}
			}
		}
	}
}

void quit(const std::string& request, asio::ip::tcp::iostream& server) {
	server << request << "\r\n";
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
				}
			}
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "client: " << ex.what() << '\n';
		return EXIT_FAILURE;
	}
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}