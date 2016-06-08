#include "loginTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "common.pb.h"
#include "taskManager.h"
#include "redisMemManager.h"

LoginMessageDispatcher LoginTask::s_loginMsgDispatcher("登陆服务器消息处理器");
LoginTask::LoginTask(const int fd) : Connect(fd)
{
}

LoginTask::~LoginTask()
{
}

MsgRet LoginTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<LoginTask> task = boost::dynamic_pointer_cast<LoginTask>(TaskManager::getInstance().getTask(m_id));
    return s_loginMsgDispatcher.dispatch(task,message);
}

bool LoginTask::registerAccount(boost::shared_ptr<ProtoMsgData::ReqRegister> message)
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
        if(!passwd.empty())
        {
            code = ProtoMsgData::EC_Register_Again;
            break;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"insert into t_register values(%s,%s)",message->phone().c_str(),message->passwd().c_str());
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle->execSql(temp,strlen(temp)))
        {
            break;
        }
        if(!redisMem->setString("register",message->phone().c_str(),message->passwd().c_str()))
        {
            break;
        }
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    ProtoMsgData::AckRegister ackMsg;
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);
    if(ret)
    {
        nextStatus();
    }
    return ret;
}

bool LoginTask::getGatewayInfo(boost::shared_ptr<ProtoMsgData::ReqGateway> message)
{
    bool ret = false;
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
    ProtoMsgData::AckGateway ackMsg;
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
        unsigned long lessID = 0,lessNum = 0,port = 0;
        std::string ip;
        for(auto iter = idSet.begin();iter != idSet.end();++iter)
        {
            redisMem = RedisMemManager::getInstance().getRedis(*iter);
            if(!redisMem)
            {
                break;
            }
            char temp[Flyer::msglen] = {0};
            unsigned int len = redisMem->getBin("gatewayinfo",*iter,temp);
            ProtoMsgData::GatewayInfo gateInfo;
            gateInfo.ParseFromArray(temp,len);
            if(gateInfo.status() == ProtoMsgData::GS_Normal && gateInfo.person() <= lessNum)
            {
                lessID = *iter;
                lessNum = gateInfo.person();
                port = gateInfo.port();
                ip = gateInfo.ip();
            }
        }
        if(!lessID)
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(lessID);
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setInt("logingate",message->phone().c_str(),lessID))
        {
            break;
        }
        ackMsg.set_ip(ip);
        ackMsg.set_port(port);
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);
    if(ret)
    {
        nextStatus();
    }
    return ret;
}
