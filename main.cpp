#include <QCoreApplication>
#include "config.h"
#include "target.h"
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    boost::asio::io_context io;
    config s{};





    io.run();
    return a.exec();
}
