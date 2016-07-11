#ifndef ROBOT_CLIENT_H
#define ROBOT_CLIENT_H 
#include "client.h"
#include "messageDispatcher.h"

class RobotClient;
typedef MessageDispatcher<boost::shared_ptr<RobotClient> > RobotClientMessageDispatcher;
class RobotClient : public Client
{
    public:
        RobotClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~RobotClient();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    public:
        static RobotClientMessageDispatcher s_robotClientMsgDispatcher;
};

#endif
