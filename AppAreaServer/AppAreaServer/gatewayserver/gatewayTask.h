#ifndef GATE_WAY_TASK_H
#define GATE_WAY_TASK_H 
#include "connect.h"
#include "messageDispatcher.h"
#include "login.pb.h"

class GatewayTask;
typedef MessageDispatcher<boost::shared_ptr<GatewayTask> > GatewayMessageDispatcher;
class GatewayTask : public Connect
{
    public:
        GatewayTask(const int fd);
        ~GatewayTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool loginGateway(boost::shared_ptr<ProtoMsgData::ReqLoginGateway> message);
        bool ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message);
    public:
        static GatewayMessageDispatcher s_gatewayMsgDispatcher;
    private:
        unsigned long m_charID;
};
#endif