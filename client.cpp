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
            self->first = std::chrono::high_resolution_clock::now();
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
                self->endpoint_ = endpoint;
                self->second = std::chrono::high_resolution_clock::now();
                self->target_.ping_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(self->second - self->first);
                std::cout << endpoint.address().to_string() << ":" << endpoint.port() << " time to conn: " << self->target_.ping_milliseconds.count() << "ms." << std::endl;
                self->c_.sync();
                self->c_.save();
            } else {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
        });
}









