#include "config.h"
#include "client.h"

int main() {
    boost::asio::io_context io;
    config s{};

    for (auto t : s.getTargets()) {
        std::make_shared<client>(io, t, s)->start();
    }


    io.run();
    return 1;
}
