#include <boost/asio.hpp>
#include "config.h"
#include "app.h"

int main() {
    boost::asio::io_context io;
    config s{};
    App app{io, s};
    app.choice();
    return 1;
}
