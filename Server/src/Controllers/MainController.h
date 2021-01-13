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
		void get_commando(const std::string& commando, asio::ip::tcp::iostream& stream) const;
		static std::string info();
		std::string dir(const std::string& dirpath) const;
		std::string del(const std::string& dirpath) const;
		std::string ren(const std::string& dirpath, const std::string& dirname) const;
		std::string mkdir(const std::string& dirpath, const std::string& dirname) const;
		std::string get(const std::string& dirpath, asio::ip::tcp::iostream& stream) const;
		std::string put(const std::string& dirpath, int size, asio::ip::tcp::iostream& stream) const;
	};
}
