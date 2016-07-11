#include "robotClient.h"
#include "clientManager.h"

RobotClientMessageDispatcher RobotClient::s_robotClientMsgDispatcher("机器人消息处理器");
RobotClient::RobotClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

RobotClient::~RobotClient()
{
}

MsgRet RobotClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_False;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<RobotClient>robotClient = boost::dynamic_pointer_cast<RobotClient>(getPtr());
            ret = s_robotClientMsgDispatcher.dispatch(robotClient,message);
        }
    }while(false);
    return ret;
}
