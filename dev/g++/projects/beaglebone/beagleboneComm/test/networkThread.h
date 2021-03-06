#if !defined(__NETWORKTHREAD_H__)
#define __NETWORKTHREAD_H__

#include "runnable.h"

#include "abstractChannel.h"

class networkThread : public beagleboneUtils::thread::runnable {
  beagleboneComm::network::socketAddress _host;
  beagleboneComm::network::socketAddress _remote;
  int _udp;

 public:
  networkThread(const std::string & p_hostAddr, const int p_hostLocalPort, const int p_hostRemotePort);
  virtual ~networkThread() { };

  void stop();
  void run();
}; // End of class networkThread

#endif // __NETWORKTHREAD_H__

