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
	std::string client_path = "C:\\temp\\client\\result";
	std::ofstream streamresult(client_path + "\\result");
	std::string req;
	if (getline(std::cin, req))
	{
		server << req << "\r\n";
	}
	std::string result;
	if (getline(server, result))
	{
		if (result == "Error: no such file \r")
		{
			std::cout << result << "\n";
		}
		else if (result == "Error: no permission \r")
		{
			std::cout << result << "\n";
		}
		else {
			int iterations = std::stoi(result);
			std::cout << iterations << "\n";
			std::string byte;
			char* bytes = new char[iterations];
			server.read(bytes, iterations);

			std::ofstream streamresult(client_path + fs::path(req).filename().string(), std::ofstream::binary);
			for (int i = 0; i < iterations; ++i)
			{
				std::cout << bytes[i] << "\n";
			}
		}
		streamresult.close();
	}
}
//Ask for path
//std::string req;
//if (getline(std::cin, req)) {
//	server << req << "\r\n";
//}
//std::string result;
//if (getline(server, result)) {
//	if (result == "Error: no such file \r")
//	{
//		std::cout << result << "\n";
//	}
//	else if (result == "Error: no permission \r")
//	{
//		std::cout << result << "\n";
//	}
//	else {
//		std::uintmax_t size = std::filesystem::file_size(req);
//		std::cout << "File is " + std::to_string(size) + " bytes \r\n";
//		const int iterations = std::stoi(result);
//		std::string byte;
//		std::string result_string;
//		for (int i = 0; i < iterations; ++i)
//		{
//			if (getline(server, byte))
//			{
//				byte = byte.substr(0, 1);
//				result_string += byte;
//				std::cout << byte << "\n";
//			}
//		}

//		streamresult << result_string;
//		streamresult.close();
//	}
//}

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

void sync(asio::ip::tcp::iostream& server) {
	//std::string _path_server = "C:\\temp\\server\\";
	//std::string _path_client = "C:\\temp\\client\\";

	//server << "dir" << "\r\n";
	//server << _path_server << "\r\n";
	//std::string result;
	//std::vector<std::map<std::string, std::string>> paths = {};
	//if (getline(server, result))
	//{
	//	const int iterations = std::stoi(result);
	//	for (int i = 0; i < iterations; ++i)
	//	{
	//		if (getline(server, result))
	//		{
	//			std::string seg;
	//			result.erase(result.end() - 1);
	//			std::stringstream str(result);
	//			std::map<std::string, std::string> map;
	//			int counter = 0;
	//			while (std::getline(str, seg, '|'))
	//			{
	//				switch (counter)
	//				{
	//				case 0:
	//					map["isdir"] = seg;
	//					++counter;
	//					break;
	//				case 1:
	//					map["filename"] = seg;
	//					++counter;
	//					break;
	//				case 2:
	//					map["last_modified"] = seg;
	//					++counter;
	//					break;
	//				case 3:
	//					map["filesize"] = seg;
	//					++counter;
	//					break;
	//				}
	//			}
	//			paths.push_back(map);
	//		}
	//	}
	//	int counter_client = { 0 };
	//	int counter_server = { 0 };
	//	for (const auto& entry : fs::recursive_directory_iterator(_path_client))
	//	{
	//		bool found = true;
	//		if (!paths.empty()) {
	//			counter_server = 0;
	//			for (auto& map : paths) {
	//				auto test = fs::last_write_time(entry.path());
	//				std::time_t tt = to_time_t(test);
	//				std::tm* gmt = std::localtime(&tt);
	//				std::stringstream buffer;
	//				buffer << std::put_time(gmt, "&F &T");
	//				if (buffer.str() > map["last_written"]) {
	//					sync_with_server(server, entry);
	//				}
	//				if (fs::path(entry.path()).filename().string() != map["filename"])
	//				{
	//					sync_with_server(server, entry);
	//				}
	//				++counter_server;
	//			}
	//		}
	//		else
	//		{
	//			sync_with_server(server, entry);
	//		}
	//		++counter_client;
	//	}
	//	std::vector <std::string> entry_names = {};
	//	std::vector <std::string> client_names = {};
	//	if (counter_server > counter_client)
	//	{
	//		for (const auto& entry : fs::recursive_directory_iterator(_path_client))
	//		{
	//			entry_names.push_back(fs::path(entry.path().filename().string()));
	//		}
	//		for (auto& map_entry : map)
	//		{
	//			client_names.push_back(map_entry["filename"]);
	//		}
	//		for (int i = 0; i < client_names.size(); ++i)
	//		{
	//			server << "del" << "\r\n";
	//			server << server_path + server_names.at(i) << "\r\n";
	//		}
	//	}
	//}
}

void sync_with_server(std::string req, int bytes, asio::ip::tcp::iostream& server)
{
	std::ifstream stream(req, std::ios::binary);
	char* buffer = new char[bytes];
	stream.read(buffer, bytes);
	server.write(buffer, bytes);

	//std::string _path_server = "C:\\temp\\server\\";
	//std::string _path_client = "C:\\temp\\client\\";
	//server << "put" << "\r\n";
	//server << _path_server + entry.path().filename().string() << "\r\n";
	//std::ifstream stream(_path_client + entry.path().filename().string(), std::ios::binary);
	//int file_size = fs::file_size(fs::path(_path_client + entry.path().filename().string()));

	//server << fs::file_size(fs::path(_path_client + entry.path().filename().string())) << "\r\n";
	//stream.read(buffer, file_size);
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
