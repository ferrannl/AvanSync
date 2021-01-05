#define _CRT_SECURE_NO_WARNINGS
#include "MainController.h"
#include <sstream>
#include <fstream>
#include "../Helpers/PathHelper.h"

using namespace Controllers;

template<char delimiter>
class WordDelimitedBy : public std::string
{};

void MainController::get_right_command(const std::string& command, asio::ip::tcp::iostream& client)
{
	_responses.clear();
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
			client << get(result) << "\r\n";
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
		//Ask for parent dir
		if (getline(client, result)) {
			result.erase(result.end() - 1);
		}
		//Ask for name for new dir
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
		if (getline(client, result)) {
			result2.erase(result2.end() - 1);
		}
		client << put(result, result2) << "\r\n";

		/*std::istringstream iss(command);
		std::vector<std::string> results((std::istream_iterator<WordDelimitedBy<' '>>(iss)),
			std::istream_iterator<WordDelimitedBy<' '>>());
		put(results[1]);*/
	}

	else {
		wrong_command();
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

std::string MainController::dir(const std::string& path)
{

	std::string dir_list;
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
	return dir_list;
}

std::string Controllers::MainController::get(const std::string& path)
{
	std::string return_list;
	if (fs::exists(path)) {
		return_list += std::to_string(fs::file_size(path)) + "\r\n";
		std::string result;
		std::ifstream streamresult(path);
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
			return_list += buffer[i];
			return_list += "\r\n";
		}
	}
	return return_list;
}

std::string MainController::put(const std::string& path, const std::string& file_size)
{
	if (fs::exists(path)) {
		fs::copy(path, path);
		return "OK";
	}
	else {
		return "Error: Invalid path";
	}
}

std::string MainController::ren(std::string& path, const std::string& new_name)
{
	if (std::filesystem::exists(path)) {
		std::string old_path = path;
		std::reverse(path.begin(), path.end());
		std::string end = path.substr(0, path.find("/"));
		path.erase(0, end.length());
		std::reverse(path.begin(), path.end());
		path += new_name;
		std::filesystem::rename(old_path, path);
		return "OK \r\n";
	}
	else {
		return "Error: invalid path \r\n";
	}

}

std::string MainController::del(const std::string& path)
{
	if (!std::filesystem::exists(path)) {
		return "Error: no such file or directory \r\n";
	}

	auto dir = std::filesystem::directory_entry(path);
	auto per = dir.status().permissions();

	if (per != std::filesystem::perms::all) {
		return "Error: no permission \r\n";
	}
	std::filesystem::remove(path);
	return "OK \r\n";
}

std::string MainController::mkdir(const std::string& parent, const std::string& name)
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

void MainController::wrong_command()
{
	_responses.push_back("Invalid Command.");
}

std::vector<std::string> Controllers::MainController::get_responses()
{
	return _responses;
}


