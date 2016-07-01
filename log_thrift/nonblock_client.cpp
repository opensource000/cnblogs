#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string>

#include "gen-cpp/log_constants.h"
#include "gen-cpp/log_types.h"
#include "gen-cpp/LogSender.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

void send_log(const std::string& strName, const std::string& strContent)
{
	boost::shared_ptr<TSocket> socket(new TSocket("127.0.0.1", 9090));
	//对接nonblockingServer时必须的，对普通server端时用boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket)); 
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        LogSenderClient client(protocol);
        try 
        {
                transport->open();
                vector<LogInfo> logInfos;
                LogInfo logInfo;
		logInfo.__set_name(strName);
		logInfo.__set_content(strContent);
                logInfos.push_back(logInfo);
                client.SendLog(logInfos);
                transport->close();
        } catch (TException &tx)
        {
                printf("ERROR: %s\n", tx.what());
        }
}

int main(int argc, char** argv)
{
	send_log("log1", "this is a example1");
	return 0;
}
