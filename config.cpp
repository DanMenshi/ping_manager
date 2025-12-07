#include <fstream>
#include <iostream>
#include "config.h"

void config::create_json() {
    json = nlohmann::json::object();
    json["targets"] = nlohmann::json::array();
    json["targets"].push_back({
            {"host", "google.com"},
            {"addr", "0.0.0.0"},
            {"port", 443},
            {"ping_milliseconds", -1},
            {"ping_microseconds", -1},
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
            {"addr", targets[i].addr},
            {"ping_milliseconds", targets[i].ping_milliseconds.count()},
            {"ping_microseconds",targets[i].ping_microseconds.count()},
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
        targets[i].addr = arr[i]["addr"];
        targets[i].port = arr[i]["port"];
        targets[i].ping_milliseconds = std::chrono::milliseconds(arr[i]["ping_milliseconds"]);
        targets[i].ping_microseconds = std::chrono::microseconds(arr[i]["ping_microseconds"]);
    }
}

std::vector<target>& config::getTargets() {
    return targets;
}

void config::add_new_target(const std::string& host, int port) {
    auto t = target{host, "0.0.0.0", port, std::chrono::milliseconds(-1), std::chrono::microseconds(-1)};
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

void config::setPing(const std::string& host, int port, std::chrono::milliseconds ms, std::chrono::microseconds mics) {
    for (auto& t : targets) {
        if (t.host == host && t.port == port) {
            t.ping_milliseconds = ms;
            t.ping_microseconds = mics;
            break;
        }
    }
    sync();
    save();
}
void config::setPing(target& target) {
    for (auto& t : targets) {
        if (t.host == target.host && t.port == target.port) {
            t.ping_milliseconds = target.ping_milliseconds;
            t.ping_microseconds = target.ping_microseconds;
            t.addr = target.addr;
            break;
        }
    }
    sync();
    save();
}

void config::printJson() const {
    std::cout << json.dump(4) << std::endl;
}


















