#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <asio.hpp>

namespace fs = std::filesystem;

namespace Controllers {
	class MainController {
	private:
		const std::string& _path = "C:\\temp\\server\\";
	public:
		void get_command(const std::string& command, asio::ip::tcp::iostream& client) const;
		static std::string info();
		std::string dir(const std::string& path) const;
		std::string del(const std::string& path) const;
		std::string ren(const std::string& path, const std::string& new_name) const;
		std::string mkdir(const std::string& parent, const std::string& name) const;
		std::string get(const std::string& path, asio::ip::tcp::iostream& client) const;
		std::string put(const std::string& path, int file_size, asio::ip::tcp::iostream& client) const;
	};
}
