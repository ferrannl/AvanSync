#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

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
		int iterations = std::stoi(result);
		for (int i = 0; i < iterations; ++i)
		{
			if (getline(server, result))
			{
				std::cout << result << "\n";
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
		std::cout << result + "\n";
	}
}

void get(asio::ip::tcp::iostream& server) {
	//Ask for path
	std::string req;

	if (getline(std::cin, req)) {
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result)) {
		if (result == "Error: no such file \r")
		{
			std::cout << result << "\n";
		}
		else if (result == "Error: no permission \r")
		{
			std::cout << result << "\n";
		}
		else {
			std::uintmax_t size = std::filesystem::file_size(req);
			std::cout << "File is " + std::to_string(size) + " bytes \r\n";
			int iterations = std::stoi(result);
			std::string byte;
			std::string result_string;
			for (int i = 0; i < iterations; ++i)
			{
				if (getline(server, byte))
				{
					byte = byte.substr(0, 1);
					result_string += byte;
					std::cout << byte << "\n";
				}
			}
			std::string client_path = "C:\\temp\\client\\result";
			std::ofstream streamresult(client_path + "\\result.txt");

			streamresult << result_string;
			streamresult.close();
		}
	}
}

void put(asio::ip::tcp::iostream& server) {
	std::string req;
	if (getline(std::cin, req)) {
		server << req << "\r\n";
		server << fs::file_size(req) << "\r\n";
		std::string result;
		std::ifstream streamresult(req);
		//get length of file
		streamresult.seekg(0, std::ios::end);
		size_t length = streamresult.tellg();
		streamresult.seekg(0, std::ios::beg);

		char buffer[1000];
		// don't overflow the buffer!

		//read file
		streamresult.read(buffer, length);
		for (int i = 0; i < length; ++i)
		{
			server << buffer[i] << "\r\n";
		}
	}
	std::string end;
	if (getline(server, end)) {
		std::cout << end << "\n";
	}
}

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
