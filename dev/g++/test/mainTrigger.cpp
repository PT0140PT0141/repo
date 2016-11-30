#include <iostream>
#include <iomanip>

#include "mainTrigger.h"

mainTrigger::mainTrigger(std::string & p_hostAddr, const int p_hostLocalPort, const int p_hostRemotePort) : 
  _host(p_hostAddr, p_hostLocalPort),
  _remote(p_hostAddr, p_hostRemotePort) {
  std::clog << ">>> mainTrigger::ctor" << std::endl;

  std::clog << "socket: " << _host.toString() << std::endl;
  std::clog << "socket: " << _remote.toString() << std::endl;
  _udp = raspberryComm::channelManager::getInstance().createChannel(raspberryComm::abstractChannel::udp, _host, _remote);
  std::clog << "Channel id: " << std::dec << _udp << std::endl;
}

void mainTrigger::stop() {
  std::clog << ">>> mainTrigger::operator" << std::endl;

  raspberryComm::channelManager::getInstance().getChannel(_udp).disconnect();

  raspberryComm::channelManager::getInstance().removeChannel(_udp);
}

void mainTrigger::run() {
  std::clog << ">>> mainTrigger::operator" << std::endl;

  _running = true;
  while (_running == true) {
    std::vector<unsigned char> vdatas { (unsigned char)0xff, (unsigned char)0x01, (unsigned char)0x41 };
    raspberryComm::channelManager::getInstance().getChannel(_udp).write(vdatas);

    usleep(25);
    
    std::vector<unsigned char> result(3);
    raspberryComm::channelManager::getInstance().getChannel(_udp).read(result);
    std::clog << "Receive data: " << std::endl;
    int idx = 0;
    for (std::vector<unsigned char>::iterator it = result.begin(); it != result.end(); ++it, idx++) {
      std::clog << "result[" << idx << "] = 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)*it << std::endl;
    } // End of 'for' statement

    std::cout << ".";
    usleep(50);
  } // End of 'while' statement

  std::clog << "<<< mainTrigger::operator" << std::endl;
}

