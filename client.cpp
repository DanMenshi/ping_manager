#include "client.h"
#include <iostream>
#include <chrono>

client::client(boost::asio::io_context& io, target& target, config& c)
    : io_(io),
      resolver_(io_),
      socket_(io_),
      target_(target),
      c_(c)
{ }

void client::start() {
    do_resolve();
}

void client::do_resolve() {

    auto self = shared_from_this();

    resolver_.async_resolve(target_.host, std::to_string(target_.port),
    [self] (const boost::system::error_code ec, tcp::resolver::results_type endpoints){
        if (!ec) {
            self->time.start_time();
            self->do_connect(endpoints);
        }
        else {
            std::cerr << "Error: " << ec.message() << std::endl;
        }
    });
}

void client::do_connect(const tcp::resolver::results_type& endpoints) {

    auto self = shared_from_this();

    asio::async_connect(socket_, endpoints,
        [self] (const boost::system::error_code& ec, const tcp::endpoint& endpoint) {
            if (!ec) {
                self->time.end_time();
                self->endpoint_ = endpoint;
                self->target_.ping_milliseconds = self->time.get_ms();
                self->target_.ping_microseconds = self->time.get_mcs();
                self->target_.addr = self->endpoint_.address().to_string();
                self->c_.setPing(self->target_);
            } else {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
            self->socket_.close();
        });
}









