#include <QCoreApplication>
#include "config.h"
#include "target.h"
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    boost::asio::io_context io;
    config s{};


    for (auto t : s.getTargets()) {
        std::make_shared<client>(io, t, s)->start();
    }


    io.run();
    return a.exec();
}
