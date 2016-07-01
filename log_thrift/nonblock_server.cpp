#include "gen-cpp/LogSender.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

#define THREAD_NUM 5

std::map<std::string, std::string> logMap;

class LogSenderHandler : virtual public LogSenderIf {
 public:
  LogSenderHandler() {
    // Your initialization goes here
  }

  void SendLog(const std::vector<LogInfo> & loglist) {
    // Your implementation goes here
    sleep(5);
    time_t now = time(NULL);
    printf("SendLog, now = %s\n", ctime(&now));
    for (size_t i = 0; i < loglist.size(); ++i)
    {
      if (logMap.find(loglist[i].name) == logMap.end())
      {
        logMap.insert(std::make_pair(loglist[i].name, loglist[i].content));
      }
    }
  }

  void GetLog(std::string& _return, const std::string& logname) {
    // Your implementation goes here
    std::map<std::string,std::string>::iterator iter = logMap.find(logname);
    if (iter != logMap.end())
    {
      _return = iter->second;
    }
    else
    {
      _return = "Not Found!";
    }
  }

};

int main(int argc, char **argv) 
{
  int port = 9090;
  shared_ptr<LogSenderHandler> handler(new LogSenderHandler());
  shared_ptr<TProcessor> processor(new LogSenderProcessor(handler));
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(THREAD_NUM);
  shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory> (new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  TNonblockingServer server(processor, protocolFactory, port, threadManager);

  server.serve();
  return 0;
}

