#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <asio.hpp>
namespace fs = std::filesystem;


namespace Controllers {
	class MainController {
	private:
		std::vector<std::string> _responses;
		const std::string& _path = "C:\\temp\\server\\result\\";
	public:
		void get_right_command(const std::string& command, asio::ip::tcp::iostream& client);
		std::string info();
		std::string dir(const std::string& path);
		std::string put(const std::string& path, const std::string& file_size, asio::ip::tcp::iostream& client);
		std::string ren(const std::string& path, const std::string& new_name);
		std::string del(const std::string& path);
		std::string mkdir(const std::string& parent, const std::string& name);
		std::string get(const std::string& path, asio::ip::tcp::iostream& client);
		void sync(asio::ip::tcp::iostream& server);
	};
}
