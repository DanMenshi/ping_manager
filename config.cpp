#include <fstream>
#include <iostream>
#include "config.h"

void config::create_json() {
    json = nlohmann::json::object();
    json["targets"] = nlohmann::json::array();
    json["targets"].push_back({
            {"host", "google.com"},
            {"port", 431},
            {"last_ping", -1}
        });
}

void config::load() {
    std::ifstream file("config.json");
    file >> json;

}

void config::save() {
    std::ofstream file("config.json");
    try {
        file << json.dump(4);
    } catch (...) {
        std::cerr << "Fatal error" << std::endl;
        create_json();
        save();
    }
}

void config::sync() {
    auto& fileT = json["targets"];
    fileT.clear();
    for (int i = 0; i < targets.size(); ++i) {
        fileT.push_back({
            {"host", targets[i].host},
            {"port", targets[i].port},
            {"last_ping", targets[i].last_ping.count()},
        });
    }
}

config::config() {
    std::ifstream file("config.json");
    if (file.is_open()) {
        load();
        std::cout << "File open 'config.json'" << std::endl;
    } else {
        create_json();
        save();
        std::cout << "File created 'config.json'" << std::endl;
    }

    auto& arr = json["targets"];
    targets.resize(arr.size());
    for (int i = 0; i < json["targets"].size(); ++i) {
        targets[i].host = arr[i]["host"];
        targets[i].port = arr[i]["port"];
        targets[i].last_ping = std::chrono::milliseconds(arr[i]["last_ping"]);
    }
}

std::vector<target>& config::getTargets() {
    return targets;
}

void config::add_new_target(const std::string& host, int port) {
    auto t = target{host, port, std::chrono::milliseconds(-1)};
    if (only_target(t)) {
        targets.push_back(t);
    }
    sync();
    save();
}

bool config::only_target(const target& target) {
    for (auto& t : targets) {
        if (t.host == target.host && t.port == target.port) {
            return false;
        }
    }
    return true;
}

void config::setPing(const std::string& host, int port, std::chrono::milliseconds ms) {
    for (auto& t : targets) {
        if (t.host == host && t.port == port) {
            t.last_ping = ms;
        }
    }
    sync();
    save();
}

void config::printJson() const {
    std::cout << json.dump(4) << std::endl;
}


















