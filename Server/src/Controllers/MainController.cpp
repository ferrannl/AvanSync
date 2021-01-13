#define _CRT_SECURE_NO_WARNINGS
#include "MainController.h"
#include <sstream>
#include <fstream>
#include <iostream>

#include "../Helpers/PathHelper.h"

using namespace Controllers;

template<char delimiter>
class WordDelimitedBy : public std::string
{};

void MainController::get_right_command(const std::string& command, asio::ip::tcp::iostream& client) const
{
	if (command.find("info") == 0) {
		std::string result;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
			client << info() << "\r\n";
		}
	}
	else if (command.find("dir") == 0) {
		std::string result;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
			client << dir(result) << "\r\n";
		}
	}
	else if (command.find("get") == 0) {
		std::string result;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
			client << get(result, client) << "\r\n";
		}
	}
	else if (command.find("del") == 0) {
		std::string result;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
			client << del(result) << "\r\n";
		}
	}
	else if (command.find("mkdir") == 0) {
		std::string result;
		std::string result2;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
		}
		if (getline(client, result2)) {
			result2.erase(result2.end() - 1);
		}
		client << mkdir(result, result2) << "\r\n";
	}
	else if (command.find("ren") == 0) {
		std::string result;
		std::string result2;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
		}
		if (getline(client, result2)) {
			result2.erase(result2.end() - 1);
		}
		client << ren(result, result2) << "\r\n";
	}
	else if (command.find("put") == 0) {
		std::string result;
		std::string result2;
		if (getline(client, result)) {
			result.erase(result.end() - 1);
		}
		if (getline(client, result2)) {
			try {
				client << put(result, std::stoi(result2), client) << "\r\n";
			}
			catch (const std::exception& e)
			{
				client << "Error: " << e.what() << "\r\n";
			}
		}
	}
	else if (command.find("quit") == 0)
	{
		std::cerr << "will disconnect from client" << client.socket().local_endpoint() << "\r\n";
	}
	else {
		client << "Invalid Command." << "\r\n";
	}
}

std::string MainController::info()
{
	return "AvanSync Server 1.0";
}

template <typename TP>
std::time_t to_time_t(const TP& tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

std::string MainController::dir(const std::string& path) const
{
	std::string dir_list;
	if (!fs::exists(path)) {
		return "Error: no such file \r\n";
	}
	if (fs::status(path).permissions() != fs::perms::all) {
		return "Error: no permission \r\n";
	}
	else {
		int counter = 0;
		for (const auto& entry : fs::recursive_directory_iterator(path))
		{
			++counter;
		}
		dir_list += std::to_string(counter) + "\r\n";
		for (const auto& entry : fs::recursive_directory_iterator(path)) {

			if (entry.is_directory())
			{
				dir_list += "D|";
			}
			else if (entry.is_regular_file())
			{
				dir_list += "F|";
			}
			else {
				dir_list += "|";
			}
			dir_list += fs::path(entry.path()).filename().string();
			dir_list += "|";
			auto test = fs::last_write_time(entry.path());
			std::time_t tt = to_time_t(test);
			std::tm* gmt = std::localtime(&tt);
			std::stringstream buffer;
			buffer << std::put_time(gmt, "%F %T");
			dir_list += buffer.str();
			dir_list += "|";
			dir_list += static_cast<std::stringstream>(std::stringstream() << entry.file_size()).str();
			dir_list += " ";
			dir_list += "\r\n";
		}
	}
	return dir_list;
}

std::string MainController::get(const std::string& path, asio::ip::tcp::iostream& client) const
{
	std::string return_list;
	if (fs::exists(path)) {
		if (fs::status(path).permissions() != fs::perms::all) {
			return "Error: no permission \r\n";
		}
		std::string result;
		client << std::to_string(fs::file_size(path)) + "\r\n";
		std::ifstream streamresult(path, std::ios::binary);
		streamresult.seekg(0, std::ios::end);
		const size_t length = streamresult.tellg();
		streamresult.seekg(0, std::ios::beg);

		// don't overflow the buffer!
		char buffer[100000];

		streamresult.read(buffer, length);
		for (int i = 0; i < length; ++i)
		{
			result += buffer[i];
		}
		client.write(result.c_str(), length);
	}
	else {
		return "Error: no such file \r\n";
	}
	return return_list;
}

std::string MainController::del(const std::string& path) const
{
	if (!std::filesystem::exists(path)) {
		return "Error: no such file or directory \r\n";
	}

	const auto dir = std::filesystem::directory_entry(path);
	const auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		return "Error: no permission \r\n";
	}
	std::filesystem::remove(path);
	return "OK \r\n";
}

std::string MainController::put(const std::string& path, int file_size, asio::ip::tcp::iostream& client) const
{
	if (fs::exists(path)) {
		if (fs::status(path).permissions() != fs::perms::all) {
			return "Error: no permission \r\n";
		}
		if (fs::is_directory(path))
		{
			return "Error: invalid path \r\n";
		}
		std::string result = path;
		const std::string file_name = fs::path(path).filename().string();
		if (fs::space(result.substr(0, result.length() - file_name.length())).available < file_size)
		{
			return "Error: not enough disk space \r\n";
		}
		result = result.substr(0, result.length() - file_name.length());
		const std::shared_ptr<char> byte(new char[file_size], std::default_delete<char[]>());
		client.read(byte.get(), file_size);
		std::ofstream streamresult(_path + file_name, std::ios::binary);
		streamresult.write(byte.get(), file_size);
		streamresult.close();

		return "OK! \r\n";
	}
	else
	{
		return "Error: invalid path \r\n";
	}
}


std::string MainController::ren(const std::string& path, const std::string& new_name) const
{
	if (!std::filesystem::exists(path)) {
		return "Error: no such file or directory \r\n";
	}

	const auto dir = std::filesystem::directory_entry(path);
	const auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		return "Error: no permission \r\n";
	}
	std::string path2 = path;
	if (std::filesystem::exists(path2)) {
		const std::string old_path = path2;
		std::reverse(path2.begin(), path2.end());
		const std::string end = path2.substr(0, path2.find("/"));
		path2.erase(0, end.length());
		std::reverse(path2.begin(), path2.end());
		path2 += new_name;
		std::filesystem::rename(old_path, path2);
		return "OK \r\n";
	}
	else {
		return "Error: no such file or directory \r\n";
	}

}

std::string MainController::mkdir(const std::string& parent, const std::string& name) const
{
	if (fs::exists(parent)) {
		std::string path = parent + name;
		path.erase(remove_if(path.begin(), path.end(), isspace), path.end());
		std::filesystem::create_directory(path);
		return "OK \r\n";
	}
	else {
		return "Error: no such directory \r\n";
	}
}
