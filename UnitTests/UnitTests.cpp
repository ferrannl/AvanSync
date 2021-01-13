#include "pch.h"

#include <asio.hpp>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ServerTest)
	{
	public:

		TEST_METHOD(Info)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}
			server << "info" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}
			std::string res = "AvanSync server 1.0, copyright (c)";
			Assert::AreEqual(res, resp);

			server << "quit" << crlf;
		}

		TEST_METHOD(Quit)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "quit" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}
			std::string res = "Bye.";
			Assert::AreEqual(res, resp);
		}

		TEST_METHOD(DirSucces)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "dir" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreNotEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(DirFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "dir wrong folder" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(GetFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "get" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(PutFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "put" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(RenFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "ren" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(DelFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "del" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}

		TEST_METHOD(MkdirFailed)
		{
			const std::string server_address{ "localhost" };
			const std::string server_port{ "12345" };
			const std::string lf{ "\n" };
			const std::string crlf{ "\r\n" };

			asio::ip::tcp::iostream server = asio::ip::tcp::iostream{ server_address, server_port };
			if (!server) throw std::runtime_error("could not connect to server");

			std::string resp;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			server << "mkdir" << crlf;
			if (getline(server, resp)) {
				resp.erase(resp.end() - 1); // remove '\r'
			}

			Assert::AreEqual('E', resp.front());

			server << "quit" << crlf;
		}
	};
}
