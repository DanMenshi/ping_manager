#ifndef APP_H
#define APP_H
#include <boost/asio.hpp>
#include "config.h"
#include "client.h"

#define MAX_COUNT_CONNECTION 100000

namespace asio = boost::asio;

class App
{
public:
    App(asio::io_context& io_, config& config_);
    void choice();
private:
    void start();
    void add_new_connect();
    void connection();
    bool targetExist(std::string& host, int port);
    asio::io_context& io_;
    config& config_;
    std::vector<std::shared_ptr<client>> clients;
};

#endif // APP_H
