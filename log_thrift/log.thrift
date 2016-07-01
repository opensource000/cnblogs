struct LogInfo {
1: required string name,
2: optional string content,
}

service LogSender {
void SendLog(1:list<LogInfo> loglist);
string GetLog(1:string logname);
}
