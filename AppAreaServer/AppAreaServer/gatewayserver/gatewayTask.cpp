#include "gatewayTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "common.pb.h"
#include "taskManager.h"
#include "redisMemManager.h"
#include "clientManager.h"
#include "recycleThread.h"

GatewayMessageDispatcher GatewayTask::s_gatewayMsgDispatcher("网关服务器消息处理器");
GatewayTask::GatewayTask(const int fd) : Connect(fd),m_charID(0)
{
}

GatewayTask::~GatewayTask()
{
}

MsgRet GatewayTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<GatewayTask> task = boost::dynamic_pointer_cast<GatewayTask>(TaskManager::getInstance().getTask(m_id));
    return s_gatewayMsgDispatcher.dispatch(task,message);
}

bool GatewayTask::loginGateway(boost::shared_ptr<ProtoMsgData::ReqLoginGateway> message)
{
    bool ret = false;
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::string passwd = redisMem->getString("register",message->phone().c_str());
        if(passwd.empty())
        {
            code = ProtoMsgData::EC_Register_No;
            break;
        }
        if(passwd.compare(message->passwd()))
        {
            code = ProtoMsgData::EC_Passwd_Wrong;
            break;
        }
        std::set<unsigned long> idSet;
        if(!redisMem->getSet("gateway","idset",idSet))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(m_id);
        if(!redisMem)
        {
            break;
        }
        unsigned int gatewayID = redisMem->getInt("logingate",message->phone().c_str());
        if(m_id != gatewayID)
        {
            code = ProtoMsgData::EC_Gateway_Wrong;
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        unsigned long charID = redisMem->getInt("charid",message->phone().c_str());
        if(!charID)
        {
            ProtoMsgData::ReqCreateUser reqMsg;
            reqMsg.set_phone(message->phone());
            reqMsg.set_id(getID());
            boost::shared_ptr<Client> client = ClientManager::getInstance().getClientByType(ProtoMsgData::ST_Record);
            if(!client)
            {
                break;
            }
            client->sendMsg(reqMsg);
        }
        else
        {
            m_charID = charID;
        }
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    if(m_charID)
    {
        ProtoMsgData::AckLoginGateway ackMsg;
        ackMsg.set_ret(ret);
        sendMsg(ackMsg);
    }
    if(ret)
    {
        nextStatus();
    }
    return ret;
}

bool GatewayTask::ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    bool ret = false;
    do
    {
        if(m_charID)
        {
            break;
        }
        if(message->code() != ProtoMsgData::EC_Default)
        {
            ProtoMsgData::AckErrorCode ackMsg;
            ackMsg.set_code(message->code());
            sendMsg(ackMsg);
            break;
        }
        m_charID = message->charid();
        ret = true;
    }while(false);

    ProtoMsgData::AckLoginGateway ackMsg;
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);
    if(!ret)
    {
        boost::shared_ptr<Connect> connect = TaskManager::getInstance().getTask(getID());
        if(connect)
        {
            RecycleThread::getInstance().add(connect);
        }
    }
    return ret;
}
