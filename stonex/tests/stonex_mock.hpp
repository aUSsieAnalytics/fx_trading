#pragma once
#include <gtest/gtest.h>
#include <httplib.h>
#include <mutex>
#include <stonex.h>

class StoneXTest : public virtual ::testing::Test {
public:
  static inline std::unique_ptr<httplib::Server> svr = std::make_unique<httplib::Server>();
  static inline std::thread server_thread;
  static inline std::unique_ptr<std::mutex> server_mutex = std::make_unique<std::mutex>();

  static void SetUpTestSuite() {
    server_mutex->lock();
    setenv("STONEX_APPKEY", "TESTING", 1);
    setenv("STONEX_USER", "TESTING", 1);
    setenv("STONEX_PASS", "TESTING", 1);

    svr->bind_to_port("localhost", 8080);
    std::cout << "listening on port 8080" << "\n";
    StoneX::base_url_ptr->assign("http://localhost:8080");
    StoneX::trading_url_ptr->assign("http://localhost:8080");

    server_thread = std::thread([]() { svr->listen_after_bind(); });
    svr->wait_until_ready();
  }

  static void TearDownTestSuite() {
    svr->stop();
    server_thread.join();
    unsetenv("STONEX_APPKEY");
    unsetenv("STONEX_USER");
    unsetenv("STONEX_PASS");
    StoneX::base_url_ptr->assign(StoneX::base_url);
    StoneX::trading_url_ptr->assign(StoneX::trading_url);
    StoneX::AccountCredentials::account_id = 0;
    StoneX::AccountCredentials::authorized = false;
    StoneX::AccountCredentials::initialized = false;
    server_mutex->unlock();
  }
  void SetUp() override {
    StoneX::AccountCredentials::authorized = false;
    StoneX::AccountCredentials::initialized = false;
    StoneX::AccountCredentials::account_id = 0;
  }

  void TearDown() override {
    StoneX::AccountCredentials::authorized = false;
    StoneX::AccountCredentials::initialized = false;
    StoneX::AccountCredentials::account_id = 0;
  }
};
