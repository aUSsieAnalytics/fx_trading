#include <gtest/gtest.h>
#include <httplib.h>
#include <stonex.h>

class StoneXRespTest : public ::testing::Test {
protected:
  static std::unique_ptr<httplib::Server> svr;
  static std::thread server_thread;

  static void SetUpTestSuite() {
    svr = std::make_unique<httplib::Server>();
    setenv("STONEX_APPKEY", "TESTING", 1);
    setenv("STONEX_USER", "TESTING", 1);
    setenv("STONEX_PASS", "TESTING", 1);
    StoneX::base_url_ptr->assign("http://localhost:8080");
    StoneX::trading_url_ptr->assign("http://localhost:8080");

    svr->bind_to_port("localhost", 8080);
    server_thread = std::thread([]() { svr->listen_after_bind(); });

    // Give the server time to start
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  static void TearDownTestSuite() {
    // Stop the server and join the thread (only once after last test)
    svr->stop();
    if (server_thread.joinable()) {
      server_thread.join();
    }

    // Clean up the server instance
    svr.reset();
  }
};

// Define static members
std::unique_ptr<httplib::Server> StoneXRespTest::svr;
std::thread StoneXRespTest::server_thread;