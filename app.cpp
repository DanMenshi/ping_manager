#include "app.h"
#include <iostream>
#include <thread>

namespace asio = boost::asio;

App::App(asio::io_context& io, config& config) :
    io_(io),
    config_(config)
{ }

void App::choice() {
    std::cout << "Do you want add new target? (1. yes/2. no) \n~ ";
    int value = 0;
    std::cin >> value;
    std::cout << std::endl;

    if (value == 1) {
        add_new_connect();
    } else {
        start();
    }

}

void App::add_new_connect() {
    std::string host;
    std::cout << "Write new host: ";
    std::cin >> host;
    std::cout << std::endl;

    int port;
    std::cout << "Write and port: ";
    std::cin >> port;
    std::cout << std::endl;

    config_.add_new_target(host, port);
    choice();
}

void App::start() {
    for (auto& target : config_.getTargets()) {
        clients.push_back(std::make_shared<client>(io_, target, config_));
    }
    std::cout << "Target found: " << clients.size() << std::endl;
    connection();
}

void App::connection() {
    std::cout << "\033[2J\033[1;1H";
    int count = 0;
    while (count != MAX_COUNT_CONNECTION) {
        for (auto& ptr : clients) {
            ptr->start();
        }
        io_.run();
        std::cout << "====" << std::endl;
        for (auto& target : config_.getTargets()) {
            std::cout << target.host << ":" << target.port << " : " << target.ping_milliseconds.count() << "ms." << std::endl;
        }
        std::cout << "====" << "         ~" << count << std::endl;
        ++count;
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        std::cout << "\033[2J\033[1;1H";
        io_.restart();
    }


}
