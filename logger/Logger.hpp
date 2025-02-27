#include <nlohmann/json.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger : public spdlog::logger {
  nlohmann::json _extras;
  std::shared_ptr<bool> _serialize;

  template <typename K = std::string, typename V = std::string, typename... Args>
  void add_to_extras(K key = "", V val = "", Args... args) {
    if (key == "" && val == "") {
      return;
    }
    this->_extras["extras"][key] = val;
    add_to_extras(args...);
  }

  std::string adjust_message(std::string msg) {
    if (*(this->_serialize)) {
      this->_extras["message"] = msg;
      msg = this->_extras.dump();
      msg.erase(0, 1);
      this->_extras.erase("message");
    }
  }

public:
  template <typename T>
  Logger(const std::string &name, T sinks, nlohmann::json extras = {},
         std::shared_ptr<bool> serialize = nullptr)
      : spdlog::logger(name, sinks), _extras(extras) {
    serialize ? _serialize = serialize : _serialize = std::make_shared<bool>(false);
  }

  template <typename T>
  Logger(const std::string &name, T sinks_start, T sinks_end, nlohmann::json extras = {},
         std::shared_ptr<bool> serialize = nullptr)
      : spdlog::logger(name, sinks_start, sinks_end), _extras(extras), _serialize(serialize) {
    serialize ? _serialize = serialize : _serialize = std::make_shared<bool>(false);
  }

  void serialize(bool on = true) {
    *_serialize = on;
    on ? this->set_pattern(
             "{\"timestamp\":\"%Y-%m-%d %H:%M:%S\",\"level\":\"%l\",\"logger_name\":\"%n\",%v")
       : this->set_pattern("%+");
  }

  template <typename... Args> std::shared_ptr<Logger> bind(Args... args) {
    auto new_logger = std::make_shared<Logger>(this->name_, this->sinks_.begin(),
                                               this->sinks_.end(), this->_extras, this->_serialize);
    new_logger->add_to_extras(args...);
    return new_logger;
  }

  void info(std::string msg) { return spdlog::logger::info(this->adjust_message(msg)); }
  void debug(std::string msg) { return spdlog::logger::debug(this->adjust_message(msg)); }
  void error(std::string msg) { return spdlog::logger::error(this->adjust_message(msg)); }
};