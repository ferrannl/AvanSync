#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void mkdir(std::string req, asio::ip::tcp::iostream& server) {
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

void ren(std::string req, asio::ip::tcp::iostream& server) {
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

void del(std::string req, asio::ip::tcp::iostream& server) {
    if (getline(std::cin, req)) {
        server << req << "\r\n";
    }
    std::string result;
    if (getline(server, result)) {
        std::cout << result + "\n";
    }
}

void quit(std::string req, asio::ip::tcp::iostream& server) {
    server << req << "\r\n";
    std::cerr << "will disconnect from client " << server.socket().local_endpoint() << "\n";

}

void info(std::string req, asio::ip::tcp::iostream& server) {
        server << req << "\r\n";
}

void dir(std::string req, asio::ip::tcp::iostream& server)
{
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

void get(std::string req, asio::ip::tcp::iostream& server) {
    if (getline(std::cin, req)) {
        server << req << "\r\n";
    }
    std::string result;
    if (getline(server, result)) {
        int iterations = std::stoi(result);
        std::string byte;
        std::string result_string;
        for (int i = 0; i < iterations; ++i)
        {
            if (getline(server, byte))
            {
                result_string += byte;
                std::cout << byte << "\n";
            }
        }
        std::string client_path = "D:\\CPP\\test\client";
        std::ofstream streamresult(client_path + "\test.txt");
        streamresult << result_string;
        streamresult.close();
    }
}

void put(std::string req, asio::ip::tcp::iostream& server) {
    if (getline(std::cin, req)) {
        std::string result = req.substr(4, req.length());
        if (fs::exists(result)) {
            float size = fs::file_size(result);
            req += " ";
            req += std::to_string(size);
        }
    }
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
                        dir(req, server);
                    }
                    else if (req.find("del") == 0) {
                        del(req, server);
                    }
                    else if (req.find("info") == 0) {
                        info(req, server);
                    }
                    else if (req.find("mkdir") == 0) {
                        mkdir(req, server);
                    }
                    else if (req.find("ren") == 0) {
                        ren(req, server);
                    }
                    else if (req.find("quit") == 0) {
                        quit(req, server);
                    }
                    else if (req.find("put") == 0) {
                        put(req, server);
                    }
                    else if (req.find("get") == 0) {
                        get(req, server);
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
