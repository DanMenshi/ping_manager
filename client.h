#ifndef CLIENT_H
#define CLIENT_H
#include <boost/asio.hpp>
#include "target.h"
#include "config.h"
#include "timer.h"

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class client : public std::enable_shared_from_this<client>
{
public:
    client(asio::io_context& io, target& target, config& c);
    void start();

private:
    void do_resolve();
    void do_connect(const tcp::resolver::results_type& endpoints);

    config& c_;
    target& target_;
    asio::io_context& io_;

    tcp::resolver resolver_;
    tcp::socket socket_;
    tcp::endpoint endpoint_;
    timer time;
};

#endif // CLIENT_H
