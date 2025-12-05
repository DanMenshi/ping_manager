#include <QCoreApplication>
#include "config.h"
#include "target.h"
#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    boost::asio::io_context io;
    config s{};
    std::vector<std::shared_ptr<client>> arr;
    s.add_new_target("ebay.com.au", 443);
    for (auto& t : s.getTargets()) {
        auto ptr = std::make_shared<client>(io, t, s);
        ptr->start();
        arr.push_back(ptr);
    }




    io.run();
    return a.exec();
}
