/**
 * @file    testlib.cpp
 * @brief   Types converter test suite.
 * @author garciay.yann@gmail.com
 * @copyright Copyright (c) 2015 ygarcia. All rights reserved
 * @license This project is released under the MIT License
 * @version 0.1
 */
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

#include <cpptest.h>

#include "socket_address.h"
#include "channel_manager.h"

#include "runnable.h"

#define LOCAL_IPv4_ADDRESS "192.168.1.21"
//#define LOCAL_IPv4_ADDRESS "172.28.2.240"
//#define LOCAL_IPv4_ADDRESS "172.28.0.55"
//#define LOCAL_IPv4_ADDRESS "0.0.0.0"
#define PEER_IPv4_ADDRESS "192.168.1.45"
//#define PEER_IPv4_ADDRESS "172.28.2.240"

#define LOCAL_IPv6_ADDRESS "::1"
#define PEER_IPv6_ADDRESS "::1"

using namespace std;

static int g_index = 0;
std::vector<int8_t> g_wait_cursor { '|', '/', '-', '\\', '|', '/', '-', '\\' };

/**
 * @class Socket address test suite implementation
 */
class socket_address_test_suite : public Test::Suite {
public:
  /**
   * @brief Default ctor
   */
  socket_address_test_suite() {
    TEST_ADD(socket_address_test_suite::test_ipv4_address_1);
    TEST_ADD(socket_address_test_suite::test_ipv4_address_2);
    TEST_ADD(socket_address_test_suite::test_ipv4_address_3);
    TEST_ADD(socket_address_test_suite::test_ipv4_address_4);
    
    TEST_ADD(socket_address_test_suite::test_ipv6_address_1);
    TEST_ADD(socket_address_test_suite::test_ipv6_address_2);
  }
	
private:
  /**
   * @brief Test case for @see ipv4_address
   */
  void test_ipv4_address_1() {
    socket_address addr(std::string("localhost"), static_cast<const uint16_t>(12345));
    TEST_ASSERT(addr.is_ipv4());
    TEST_ASSERT(!addr.is_ipv6());
    std::vector<uint8_t> to_bytes = addr.to_numeric();
    TEST_ASSERT(to_bytes.size() == 4);
    uint8_t expected_result[] = { 0x7f, 0x00, 0x00, 0x01 };
    TEST_ASSERT(std::equal(to_bytes.begin(), to_bytes.end(), expected_result));
    TEST_ASSERT(addr.port() == 12345);
    TEST_ASSERT(addr.to_string() == "127.0.0.1");
    TEST_ASSERT(addr.addr() != NULL);
  } // End of method test_ipv4_address_1
  
  /**
   * @brief Test case for @see ipv4_address
   */
  void test_ipv4_address_2() {
    socket_address addr(std::string("127.0.0.1"), static_cast<const uint16_t>(12347));
    TEST_ASSERT(addr.is_ipv4());
    TEST_ASSERT(!addr.is_ipv6());
    TEST_ASSERT(addr.port() == 12347);
    TEST_ASSERT(addr.to_string() == "127.0.0.1");
    TEST_ASSERT(addr.addr() != NULL);
    TEST_ASSERT(addr.is_localhost());
    TEST_ASSERT(!addr.is_multicast());
    TEST_ASSERT(!addr.is_broadcast());
  } // End of method test_ipv4_address_2
  
  /**
   * @brief Test case for @see ipv4_address
   */
  void test_ipv4_address_3() {
    socket_address addr(std::string("www.etsi.org"), static_cast<const uint16_t>(443));
    TEST_ASSERT(addr.is_ipv4());
    TEST_ASSERT(!addr.is_ipv6());
    std::vector<uint8_t> to_bytes = addr.to_numeric();
    TEST_ASSERT(to_bytes.size() == 4);
    uint8_t expected_result[] = { 195, 238, 226, 27 };
    TEST_ASSERT(std::equal(to_bytes.begin(), to_bytes.end(), expected_result));
    TEST_ASSERT(addr.port() == 443);
    TEST_ASSERT(addr.to_string() == "195.238.226.27");
    TEST_ASSERT(addr.addr() != NULL);
    TEST_ASSERT(!addr.is_localhost());
    TEST_ASSERT(!addr.is_multicast());
    TEST_ASSERT(!addr.is_broadcast());
  } // End of method test_ipv4_address_3
  
  /**
   * @brief Test case for @see ipv4_address
   */
  void test_ipv4_address_4() {
    socket_address addr(std::string("195.238.226.27"), static_cast<const uint16_t>(443));
    std::vector<uint8_t> to_bytes = addr.to_numeric();
    TEST_ASSERT(to_bytes.size() == 4);
    uint8_t expected_result[] = { 195, 238, 226, 27 };
    TEST_ASSERT(std::equal(to_bytes.begin(), to_bytes.end(), expected_result));
    TEST_ASSERT(addr.to_string() == "195.238.226.27");
  } // End of method test_ipv4_address_4
  
  /**
   * @brief Test case for @see ipv6_address::ctor
   */
  void test_ipv6_address_1() {
    socket_address addr(std::string("::1"), static_cast<const uint16_t>(12345));
    TEST_ASSERT(!addr.is_ipv4());
    TEST_ASSERT(addr.is_ipv6());
    TEST_ASSERT(addr.is_localhost());
    TEST_ASSERT(!addr.is_multicast());
    TEST_ASSERT(!addr.is_broadcast());
    std::vector<uint8_t> to_bytes = addr.to_numeric();
    TEST_ASSERT(to_bytes.size() == 16);
    uint8_t expected_result[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    TEST_ASSERT(std::equal(to_bytes.begin(), to_bytes.end(), expected_result));
    TEST_ASSERT(addr.to_string() == "::1");
  } // End of method test_ipv6_address_1
  
  /**
   * @brief Test case for @see ipv6_address::ctor
   */
  void test_ipv6_address_2() {
    socket_address addr(std::string("par03s13-in-x10.1e100.net"), static_cast<const uint16_t>(12345));
    TEST_ASSERT(!addr.is_ipv4());
    TEST_ASSERT(addr.is_ipv6());
    TEST_ASSERT(!addr.is_localhost());
    TEST_ASSERT(!addr.is_multicast());
    TEST_ASSERT(!addr.is_broadcast());
    std::vector<uint8_t> to_bytes = addr.to_numeric();
    TEST_ASSERT(to_bytes.size() == 16);
    uint8_t expected_result[] = { 0x2a, 0x00, 0x14, 0x50, 0x40, 0x07, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10 };
    TEST_ASSERT(std::equal(to_bytes.begin(), to_bytes.end(), expected_result));
    TEST_ASSERT(addr.to_string() == "2a00:1450:4007:806::1010");
  } // End of method test_ipv6_address_2
  
};

/**
 * @class Channel manager/UDP test suite implementation
 */
class channel_manager_udp_test_suite : public Test::Suite {
public:
  /**
   * @brief Default ctor
   */
  channel_manager_udp_test_suite() {
    // TEST_ADD(channel_manager_udp_test_suite::test_create_channel_udp_1);
    // TEST_ADD(channel_manager_udp_test_suite::test_create_channel_udp_2);
    // TEST_ADD(channel_manager_udp_test_suite::test_create_channel_udp_3);
    
    TEST_ADD(channel_manager_udp_test_suite::test_create_channel_udp_4);
    TEST_ADD(channel_manager_udp_test_suite::test_create_channel_udp_5);
  }
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * @see channel_manager::get_channel
   * @see channel_manager::remove_channel
   */
  void test_create_channel_udp_1() {
    // Create UDP channel
    socket_address addr(std::string("localhost"), static_cast<const uint16_t>(12345));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::udp, addr);
    TEST_ASSERT(channel != -1);
    
    // Get channel
    TEST_THROWS_NOTHING(channel_manager::get_instance().get_channel(channel));
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
    TEST_THROWS(channel_manager::get_instance().get_channel(channel), std::out_of_range);
  } // End of method test_create_channel_udp_1
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use command netcat -vv -u -l -p12345 LOCAL_IPv4_ADDRESS to start an UDP listener on port 12345
   * @see channel_manager::connect
   * @see channel_manager::write
   * @see channel_manager::disconnect
   */
  void test_create_channel_udp_2() {
    // Create UDP channel
    socket_address addr(std::string(LOCAL_IPv4_ADDRESS), static_cast<const uint16_t>(12345));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::udp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0d, 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
     TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_udp_2
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use command echo "Hi man" | netcat -vv -u -l -p12346 LOCAL_IPv4_ADDRESS to start an UDP listener on port 12346
   * @see channel_manager::connect
   * @see channel_manager::send
   * @see channel_manager::disconnect
   */
  void test_create_channel_udp_3() {
    // Create UDP channel
    socket_address addr(std::string(LOCAL_IPv4_ADDRESS), static_cast<const uint16_t>(12346));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::udp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0d, 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
    TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Read data
    buffer.clear();
    buffer.assign(6, 0x00);
    result = channel_manager::get_instance().get_channel(channel).read(buffer);
    TEST_ASSERT(result != -1);
    cout << "Buffer size: " << (int)buffer.size() << endl;
    TEST_ASSERT(buffer.size() == 6);
    uint8_t expected_result[] = { 'H', 'i', ' ', 'm', 'a', 'n' };
    TEST_ASSERT(std::equal(buffer.begin(), buffer.end(), expected_result));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_udp_3
  
  /**
   * @brief Test case for @see channel_manager::create_channel - IPv6
   * @see channel_manager::get_channel
   * @see channel_manager::remove_channel
   */
  void test_create_channel_udp_4() {
    // Create UDP channel
    socket_address addr(std::string("::1"), static_cast<const uint16_t>(12345));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::udp, addr);
    TEST_ASSERT(channel != -1);
    
    // Get channel channel
    TEST_THROWS_NOTHING(channel_manager::get_instance().get_channel(channel));
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
    TEST_THROWS(channel_manager::get_instance().get_channel(channel), std::out_of_range);
  } // End of method test_create_channel_udp_4
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use command netcat -6 -vv -u -l -p12345 LOCAL_IPv6_ADDRESS to start an UDP listener on port 12345
   * @see channel_manager::connect
   * @see channel_manager::write
   * @see channel_manager::disconnect
   */
  void test_create_channel_udp_5() {
    // Create UDP channel
    socket_address addr(std::string(LOCAL_IPv6_ADDRESS), static_cast<const uint16_t>(12345));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::udp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0d, 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
     TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_udp_5
  
}; // End of class channel_manager_udp_test_suite

/**
 * @class Channel manager/UDP/Thread test suite implementation
 */
class channel_manager_t_udp_test_suite : public Test::Suite {
  
  class thread_ : public runnable {
    socket_address _host_address;
    socket_address _peer_address;
    uint32_t _udp;
    bool _result;
    
  public:
    thread_(const socket_address & p_host_address, const socket_address p_peer_address) : _host_address(p_host_address), _peer_address(p_peer_address), _udp(-1), _result(false) {
      _udp = channel_manager::get_instance().create_channel(channel_type::udp, _host_address, _peer_address);
      // channel_manager::get_instance().get_channel(_udp).connect();
    }; // End of ctor
    virtual ~thread_() { };

    void stop() {
      runnable::stop();
      channel_manager::get_instance().get_channel(_udp).disconnect();
      channel_manager::get_instance().remove_channel(_udp);
      _udp = -1;
    };
    
    void run() {
      uint8_t expected_result[] = { 'H', 'i', ' ', 'm', 'a', 'n', 0x0a };
      std::vector<uint32_t> fds;
      _running = true;
      while(_running) {
	channel_manager::get_instance().poll_channels(1000, fds); // 1000 ms
	std::vector<uint32_t>::iterator it = std::find(fds.begin(), fds.end(), _udp);
	if (it != fds.end()) { // Some data are available for _udp channel
	  // Read data
	  std::vector<uint8_t> buffer(16, 0xff);
	  channel_manager::get_instance().get_channel(*it).read(buffer);
	  
	  _result = std::equal(buffer.begin(), buffer.end(), expected_result);
	  fds.clear();

	  // Echo
	  channel_manager::get_instance().get_channel(_udp).write(buffer);
	}
      } // End of 'while' statement
    }; // End of method run
    
    const bool get_result() const { return _result; };
  }; // End of class thread_
  
  unique_ptr<thread_> _udp_manager;
  bool _stop;
  
public:
  
  /**
   * @brief Default ctor
   */
  channel_manager_t_udp_test_suite() {
    TEST_ADD(channel_manager_t_udp_test_suite::test_udp_thread_channel_1);
  }
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use commands:
   * -  netcat -vv -u LOCAL_IPv4_ADDRESS 12347
   * -  netcat -vv -u -l -p 12348 PEER_IPv4_ADDRESS
   * @see channel_manager::accept_connection
   * @see channel_manager::write
   * @see channel_manager::disconnect
   */
  void test_udp_thread_channel_1() {
    socket_address host_address(std::string(LOCAL_IPv4_ADDRESS), static_cast<const uint16_t>(12347));
    socket_address peer_address(std::string(PEER_IPv4_ADDRESS), static_cast<const uint16_t>(12348));
    
    // Start server
    _stop = false;
    _udp_manager.reset(new thread_(host_address, peer_address));
    _udp_manager->start();
    
    // Wait for stop keyword
    while (!_udp_manager->get_result()) {
      std::clog << g_wait_cursor[g_index] << '\b';
      g_index = (g_index + 1) % g_wait_cursor.size();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    };
    
    // Stop server
    _udp_manager->stop();
    _udp_manager.reset();

  } // End of method test_udp_thread_channel_1
  
}; // End of class channel_manager_t_udp_test_suite

/**
 * @class Channel manager test suite implementation
 */
class channel_manager_tcp_test_suite : public Test::Suite {
public:
  /**
   * @brief Default ctor
   */
  channel_manager_tcp_test_suite() {
    // TEST_ADD(channel_manager_tcp_test_suite::test_create_channel_tcp_1);
    // TEST_ADD(channel_manager_tcp_test_suite::test_create_channel_tcp_2);
    // TEST_ADD(channel_manager_tcp_test_suite::test_create_channel_tcp_3);

    TEST_ADD(channel_manager_tcp_test_suite::test_create_channel_tcp_4);
    TEST_ADD(channel_manager_tcp_test_suite::test_create_channel_tcp_5);
  }
    
  /**
   * @brief Test case for @see channel_manager::create_channel
   * @see channel_manager::get_channel
   * @see channel_manager::remove_channel
   */
  void test_create_channel_tcp_1() {
    // Create TCP channel
    socket_address addr(std::string("localhost"), static_cast<const uint16_t>(12348));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::tcp, addr);
    TEST_ASSERT(channel != -1);
    
    // Get channel channel
    TEST_THROWS_NOTHING(channel_manager::get_instance().get_channel(channel));
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
    TEST_THROWS(channel_manager::get_instance().get_channel(channel), std::out_of_range);
  } // End of method test_create_channel_tcp_1
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use command netcat -vv -l -p12348 LOCAL_IPv4_ADDRESS to start an TCP listener on port 12348
   * @see channel_manager::connect
   * @see channel_manager::write
   * @see channel_manager::disconnect
   */
  void test_create_channel_tcp_2() {
    // Create TCP channel
    socket_address addr(std::string(LOCAL_IPv4_ADDRESS), static_cast<const uint16_t>(12348));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::tcp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
    TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_tcp_2
  
  /**
   * @brief Test case for @see channel_manager::create_channel
   * Use command ech "Hi man" | netcat -vv -l -p12348 LOCAL_IPv4_ADDRESS to start an TCP listener on port 12348
   * @see channel_manager::connect
   * @see channel_manager::write
   * @see channel_manager::read
   * @see channel_manager::disconnect
   */
  void test_create_channel_tcp_3() {
    // Create UDP channel
    socket_address addr(std::string(LOCAL_IPv4_ADDRESS), static_cast<const uint16_t>(12348));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::tcp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
    TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Read data
    buffer.assign(16, 0xff);
    result = channel_manager::get_instance().get_channel(channel).read(buffer);
    TEST_ASSERT(result != -1);
    cout << "Buffer size: " << (int)buffer.size() << endl;
    TEST_ASSERT(buffer.size() == 7);
    uint8_t expected_result[] = { 'H', 'i', ' ', 'm', 'a', 'n', 0x0a };
    TEST_ASSERT(std::equal(buffer.begin(), buffer.end(), expected_result));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_tcp_3
  
  /**
   * @brief Test case for @see channel_manager::create_channel - IPv6
   * @see channel_manager::get_channel
   * @see channel_manager::remove_channel
   */
  void test_create_channel_tcp_4() {
    // Create TCP channel
    socket_address addr(std::string("::1"), static_cast<const uint16_t>(12348));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::tcp, addr);
    TEST_ASSERT(channel != -1);
    
    // Get channel channel
    TEST_THROWS_NOTHING(channel_manager::get_instance().get_channel(channel));
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
    TEST_THROWS(channel_manager::get_instance().get_channel(channel), std::out_of_range);
  } // End of method test_create_channel_tcp_4
  
  /**
   * @brief Test case for @see channel_manager::create_channel - IPv6
   * Use command netcat -vv -l -p12348 LOCAL_IPv6_ADDRESS to start an TCP listener on port 12348
   * @see channel_manager::connect
   * @see channel_manager::write
   * @see channel_manager::disconnect
   */
  void test_create_channel_tcp_5() {
    // Create TCP channel
    socket_address addr(std::string(LOCAL_IPv6_ADDRESS), static_cast<const uint16_t>(12348));
    int32_t channel = channel_manager::get_instance().create_channel(channel_type::tcp, addr);
    
    // Connect it to host
    int32_t result = channel_manager::get_instance().get_channel(channel).connect();
    TEST_ASSERT(result != -1);
    
    // Send data
    std::vector<uint8_t> buffer = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', 0x0a };
    result = channel_manager::get_instance().get_channel(channel).write(buffer);
    TEST_ASSERT(result != -1);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Close connection
    result = channel_manager::get_instance().get_channel(channel).disconnect();
    TEST_ASSERT(result != -1);
    
    // Remove channel
    TEST_ASSERT(channel_manager::get_instance().remove_channel(channel) != -1);
  } // End of method test_create_channel_tcp_5
  
}; // End of class channel_manager_tcp_test_suite

/**
 * @brief Display User help
 */
static void usage() {
  cout << "usage: testlib [MODE]\n"
       << "where MODE may be one of:\n"
       << "  --compiler\n"
       << "  --html\n"
       << "  --text-terse (default)\n"
       << "  --text-verbose\n";
  exit(0);
}

/**
 * @brief Process command line options
 * @param[in] p_argc Number of argumrnt
 * @param[in] p_argv List of the arguments
 */
static unique_ptr<Test::Output> cmdline(int p_argc, char* p_argv[]) {
  if (p_argc > 2) {
    usage(); // will not return
  }
  
  Test::Output* output = NULL;
	
  if (p_argc == 1) {
    output = new Test::TextOutput(Test::TextOutput::Verbose);
  } else {
    const char* arg = p_argv[1];
    if (strcmp(arg, "--compiler") == 0) {
      output = new Test::CompilerOutput;
    } else if (strcmp(arg, "--html") == 0) {
      output =  new Test::HtmlOutput;
    } else if (strcmp(arg, "--text-terse") == 0) {
      output = new Test::TextOutput(Test::TextOutput::Terse);
    } else if (strcmp(arg, "--text-verbose") == 0) {
      output = new Test::TextOutput(Test::TextOutput::Verbose);
    } else {
      cout << "invalid commandline argument: " << arg << endl;
      usage(); // will not return
    }
  }
  
  return unique_ptr<Test::Output>(output);
}

/**
 * @brief Main test program
 * @param[in] p_argc Number of argumrnt
 * @param[in] p_argv List of the arguments
 */
int main(int p_argc, char* p_argv[]) {
  cout << "Warning, some test required the launch in another session some netcast UDP and TCP listener" << endl;
  try {
    Test::Suite ts;
    ts.add(unique_ptr<Test::Suite>(new socket_address_test_suite));
    //ts.add(unique_ptr<Test::Suite>(new channel_manager_udp_test_suite));
    // ts.add(unique_ptr<Test::Suite>(new channel_manager_t_udp_test_suite));
    // ts.add(unique_ptr<Test::Suite>(new channel_manager_tcp_test_suite));

    // Run the tests
    unique_ptr<Test::Output> output(cmdline(p_argc, p_argv));
    ts.run(*output, true);

    Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
    if (html) {
      html->generate(cout, true, "Converter test suite");
    }
  } catch (...) {
    cout << "unexpected exception encountered\n";
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
