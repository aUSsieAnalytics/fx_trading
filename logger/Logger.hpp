#pragma once

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

template <typename K = std::string, typename V = std::string, typename... Args>
void add_to_extras(nlohmann::json &extras, K key = "", V val = "", Args... args) {
  if (key == "") {
    return;
  }
  extras[key] = val;
  add_to_extras(extras, args...);
}

class StructuredLogger {
  static inline std::string _default_pattern = "[%Y-%m-%d %H:%M:%S:%e][%^%l%$]%v";
  std::shared_ptr<bool> _serialize;
  std::vector<std::shared_ptr<nlohmann::json>> _extras_patch_list;
  std::shared_ptr<spdlog::logger> _logger;
  std::string _local_name;

  std::string adjust_message(std::string msg) {
    if (*(this->_serialize)) {
      nlohmann::json extras;
      extras["message"] = msg;
      for (const auto &extras_patch : this->_extras_patch_list) {
        for (const auto &[key, val] : extras_patch->items()) {
          extras[key] = val;
        };
      };
      extras["logger_name"] = this->_local_name;
      msg = extras.dump();
      msg.erase(0, 1);
    } else {
      msg = "[" + this->_local_name + "] " + msg;
    }
    return msg;
  }

public:
  template <typename T>
  StructuredLogger(const std::string &name, T sinks, nlohmann::json extras = {}) {
    extras.size() > 0 ? _extras_patch_list = {std::make_shared<nlohmann::json>(extras)}
                      : _extras_patch_list = {};
    _logger = std::make_shared<spdlog::logger>(name, sinks);
    _logger->set_pattern(StructuredLogger::_default_pattern);
    _serialize = std::make_shared<bool>(false);
    _local_name = name;
  }

  template <typename T>
  StructuredLogger(const std::string &name, T sinks_start, T sinks_end,
                   nlohmann::json extras = {}) {
    extras.size() > 0 ? _extras_patch_list = {std::make_shared<nlohmann::json>(extras)}
                      : _extras_patch_list = {};
    _logger = std::make_shared<spdlog::logger>(name, sinks_start, sinks_end);
    _logger->set_pattern(StructuredLogger::_default_pattern);
    _serialize = std::make_shared<bool>(false);
    _local_name = name;
  }

  StructuredLogger(const StructuredLogger &logger) {
    _logger = logger._logger;
    _serialize = logger._serialize;
    _extras_patch_list = logger._extras_patch_list;
    _local_name = logger._local_name;
  }

  void set_name(std::string name) { this->_local_name = name; }

  std::shared_ptr<spdlog::logger> get_spdlogger() { return _logger; }

  void serialize(bool on = true) {
    *_serialize = on;
    on ? this->_logger->set_pattern("{\"timestamp\":\"%Y-%m-%d %H:%M:%S:%e\",\"level\":\"%l\",%v")
       : this->_logger->set_pattern(StructuredLogger::_default_pattern);
  }

  template <typename... Args> std::shared_ptr<StructuredLogger> bind(Args... args) {
    auto new_logger = std::make_shared<StructuredLogger>(*this);
    std::shared_ptr<nlohmann::json> new_extras = std::make_shared<nlohmann::json>();
    add_to_extras(*new_extras, args...);
    new_logger->_extras_patch_list.push_back(new_extras);
    return new_logger;
  }
  void info(std::string msg) { return this->_logger->info(this->adjust_message(msg)); }
  void debug(std::string msg) { return this->_logger->debug(this->adjust_message(msg)); }
  void error(std::string msg) { return this->_logger->error(this->adjust_message(msg)); }
  void warn(std::string msg) { return this->_logger->warn(this->adjust_message(msg)); }
};