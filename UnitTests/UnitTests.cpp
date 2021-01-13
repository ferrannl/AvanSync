#include "pch.h"
#include <asio.hpp>
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(Info_Succesfully_Returned_General_Info)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			server << "info" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			std::string res = "AvanSync server 1.0, copyright (c)";
			Assert::AreEqual(res, response);

			server << "quit" << crlf;
		}

		TEST_METHOD(Dir_Succesful_Listing)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			server << "dir" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			Assert::AreNotEqual('E', response.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(Dir_Unsuccesful_Listing)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			server << "dir wrong folder" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', response.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(Ren_Unsuccesful_Rename)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			server << "ren" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', response.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(Del_Unsuccesful_Delete)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			server << "del" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', response.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(Mkdir_Unsuccesful_NewDirectory)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string response;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			server << "mkdir" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', response.front());

			server << "quit" << crlf;
		}
	};
}