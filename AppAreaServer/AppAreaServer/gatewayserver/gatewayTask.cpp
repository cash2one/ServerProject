#include "gatewayTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "common.pb.h"
#include "taskManager.h"
#include "redisMemManager.h"
#include "clientManager.h"
#include "recycleThread.h"
#include "gatewayServer.h"

GatewayMessageDispatcher GatewayTask::s_gatewayMsgDispatcher("网关服务器消息处理器");
GatewayTask::GatewayTask(const int fd) : Connect(fd),m_charID(0),m_isLogin(false)
{
}

GatewayTask::~GatewayTask()
{
}

MsgRet GatewayTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<GatewayTask> task = boost::dynamic_pointer_cast<GatewayTask>(getPtr());
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
        unsigned int serverID = GatewayServer::getInstance().getServerID();
        redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        unsigned int gatewayID = redisMem->getInt("logingate",message->phone().c_str());
        if(serverID != gatewayID)
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
            if(!TaskManager::getInstance().addGatewayTask(m_charID,m_id))
            {
                break;
            }
        }
        redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        char temp[Flyer::msglen] = {0};
        unsigned int size = redisMem->getBin("gateway",serverID,temp);
        ProtoMsgData::GatewayInfo gateInfo;
        try
        {
            gateInfo.ParseFromArray(temp,size);
        }
        catch(...)
        {
            break;
        }
        gateInfo.set_person(gateInfo.person() + 1);
        bzero(temp,sizeof(temp));
        gateInfo.SerializeToArray(temp,sizeof(temp));
        if(!redisMem->setBin("gateway",serverID,temp,gateInfo.ByteSize()))
        {
            break;
        }
        m_isLogin = true;
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
        loginScene();
    }
    if(ret)
    {
        nextStatus();
    }
    return ret;
}

bool GatewayTask::loginScene()
{
    bool ret = false;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::set<unsigned long> idSet;
        if(!redisMem->getSet("scene","idset",idSet))
        {
            break;
        }
        unsigned short sceneID = 0;
        unsigned long num = 0;
        for(auto iter = idSet.begin();iter != idSet.end();++iter)
        {
            boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(*iter);
            if(!redisMem)
            {
                break;
            }
            char temp[Flyer::msglen] = {0};
            unsigned size = redisMem->getBin("scene",*iter,temp);
            ProtoMsgData::SceneInfo sceneInfo;
            try
            {
                sceneInfo.ParseFromArray(temp,size);
            }
            catch(...)
            {
                break;
            }
            if(sceneInfo.status() == ProtoMsgData::GS_Normal)
            {
                if(!num || num > sceneInfo.person())
                {
                    num = sceneInfo.person();
                    sceneID = sceneInfo.id();
                }
            }
        }
        if(!sceneID)
        {
            break;
        }
        boost::shared_ptr<Client> client = ClientManager::getInstance().getServerClient(sceneID);
        if(!client)
        {
            break;
        }
        ProtoMsgData::ReqLoginScene reqMsg;
        reqMsg.set_charid(m_charID);
        client->sendMsg(reqMsg);
        ret = true;
    }while(false);
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
        if(!TaskManager::getInstance().addGatewayTask(m_charID,m_id))
        {
            break;
        }
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
    else
    {
        loginScene();
    }
    return ret;
}

void GatewayTask::disConnect()
{
    do
    {
        unsigned int serverID = GatewayServer::getInstance().getServerID();
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        char temp[Flyer::msglen] = {0};
        unsigned int size = redisMem->getBin("gateway",serverID,temp);
        ProtoMsgData::GatewayInfo gateInfo;
        try
        {
            gateInfo.ParseFromArray(temp,size);
        }
        catch(...)
        {
            break;
        }
        gateInfo.set_person(gateInfo.person() - 1);
        bzero(temp,sizeof(temp));
        gateInfo.SerializeToArray(temp,sizeof(temp));
        if(!redisMem->setBin("gateway",serverID,temp,gateInfo.ByteSize()))
        {
            break;
        }
        m_isLogin = false;
    }while(false);
}
