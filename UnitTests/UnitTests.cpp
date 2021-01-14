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
			const std::string res = "AvanSync Server 1.0 Ferran Hendriks";
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
			server << "C:/temp/client/test" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "F|rentestgood.txt|2021-01-14 00:51:01|0 ";
			Assert::AreEqual(expected, response);

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

			server << "dir" << crlf;
			server << "failedtest" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "Error: no such file ";
			Assert::AreEqual(expected, response);

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
			server << "failedtest" << crlf;
			server << "anotherfailedtest" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "Error: no such file ";

			Assert::AreEqual(expected, response);

			server << "quit" << crlf;
		}

		TEST_METHOD(Ren_Succesful_Rename)
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
			server << "C:/temp/client/test/rentest.txt" << crlf;
			server << "renamedfiletest.txt" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "OK ";

			Assert::AreEqual(expected, response);

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
			server << "failedtest" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "Error: no such file or directory ";

			Assert::AreEqual(expected, response);

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
			server << "failedtest" << crlf;
			server << "anotherfailedtest" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "Error: no such directory ";

			Assert::AreEqual(expected, response);

			server << "quit" << crlf;
		}

		TEST_METHOD(Mkdir_Succesful_NewDirectory)
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
			server << "C:/temp/server/" << crlf;
			server << "newdir" << crlf;
			if (getline(server, response)) {
				response.erase(response.end() - 1); // remove '\r'
			}
			const std::string expected = "OK ";

			Assert::AreEqual(expected, response);

			server << "quit" << crlf;
		}
	};
}