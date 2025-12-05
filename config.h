#ifndef CONFIG_H
#define CONFIG_H
#include <vector>
#include <nlohmann/json.hpp>
#include "target.h"

class config {
public:
    config();
    void add_new_target(const std::string& host, int port);
    void setPing(const std::string& host, int port, std::chrono::milliseconds ms);

    void printJson() const;
    std::vector<target>& getTargets();
    void sync();
    void save();
private:
    void create_json();
    void load();
    bool only_target(const target& target);

    nlohmann::json json;
    std::vector<target> targets;
};

#endif // CONFIG_H
