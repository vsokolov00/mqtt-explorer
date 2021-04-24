#ifndef CONNECTIONCONTROLLER_H
#define CONNECTIONCONTROLLER_H

#include <string>

class ConnectionController
{
public:
    ConnectionController();
    bool connect(int protocol, std::string host, std::string port, std::string user, std::string password);
private:
    std::string host;
};

#endif // CONNECTIONCONTROLLER_H
