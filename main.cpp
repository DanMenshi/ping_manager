#include "config.h"
#include "client.h"
#include "app.h"
int main() {
    boost::asio::io_context io;
    config s{};
    App a(io, s);
    a.choice();

    return 1;
}
