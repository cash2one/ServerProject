#include "sceneClient.h"
#include "clientManager.h"
#include "taskManager.h"
#include "gatewayTask.h"

SceneClientMessageDispatcher SceneClient::s_sceneClientMsgDispatcher("场景服客户端消息处理器");
SceneClient::SceneClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

SceneClient::~SceneClient()
{
}

MsgRet SceneClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_False;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<SceneClient> sceneClient = boost::dynamic_pointer_cast<SceneClient>(getPtr());
            ret = s_sceneClientMsgDispatcher.dispatch(sceneClient,message);
        }
    }while(false);
    return ret;
}

bool SceneClient::ackUserMsg(boost::shared_ptr<ProtoMsgData::AckLoginScene> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Connect> connect = TaskManager::getInstance().getGatewayTask(message->charid());
        boost::shared_ptr<GatewayTask> gatewayTask = boost::dynamic_pointer_cast<GatewayTask>(connect);
        if(!gatewayTask)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

