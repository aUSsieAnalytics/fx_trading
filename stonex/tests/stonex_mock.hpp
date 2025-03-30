#pragma once
#include <gtest/gtest.h>
#include <httplib.h>
#include <stonex.h>

class StoneXTest : public ::testing::Test {
protected:
  static std::unique_ptr<httplib::Server> svr;
  static std::thread server_thread;
  static char *appkey;
  static char *appuser;
  static char *apppass;

  static void SetUpTestSuite() {
    svr = std::make_unique<httplib::Server>();
    appkey = std::getenv("STONEX_APPKEY");
    appuser = std::getenv("STONEX_USER");
    apppass = std::getenv("STONEX_PASS");

    setenv("STONEX_APPKEY", "TESTING", 1);
    setenv("STONEX_USER", "TESTING", 1);
    setenv("STONEX_PASS", "TESTING", 1);
    StoneX::base_url_ptr->assign("http://localhost:8080");
    StoneX::trading_url_ptr->assign("http://localhost:8080");

    svr->bind_to_port("localhost", 8080);
    server_thread = std::thread([]() { svr->listen_after_bind(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  static void TearDownTestSuite() {
    svr->stop();
    if (server_thread.joinable()) {
      server_thread.join();
    }
    svr.reset();
    if (appkey) {
      setenv("STONEX_APPKEY", appkey, 1);
    } else {
      unsetenv("STONEX_APPKEY");
    }
    if (appuser) {
      setenv("STONEX_USER", appuser, 1);
    } else {
      unsetenv("STONEX_USER");
    }
    if (apppass) {
      setenv("STONEX_PASS", apppass, 1);
    } else {
      unsetenv("STONEX_PASS");
    }
    StoneX::base_url_ptr->assign(StoneX::base_url);
    StoneX::trading_url_ptr->assign(StoneX::trading_url);
    StoneX::AccountCredentials::account_id = 0;
    StoneX::AccountCredentials::authorized = false;
  }
};

std::unique_ptr<httplib::Server> StoneXTest::svr;
std::thread StoneXTest::server_thread;
char *StoneXTest::appkey;
char *StoneXTest::appuser;
char *StoneXTest::apppass;