#include "serverTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "loginServer.h"
#include "taskManager.h"

ServerMessageDispatcher ServerTask::s_serverMsgDispatcher("登陆服务器消息处理器");

ServerTask::ServerTask(const int fd) : Task(fd)
{
}

ServerTask::~ServerTask()
{
}

MsgRet ServerTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<ServerTask> task = boost::dynamic_pointer_cast<ServerTask>(getPtr());
    return s_serverMsgDispatcher.dispatch(task,message);
}

bool ServerTask::verify(const ProtoMsgData::ServerInfo &serverInfo)
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(TaskManager::getInstance().getServerTask(serverInfo.id()))
        {
            break;
        }
        std::ostringstream oss;
        oss << "select id,ip,port from t_logininfo where servertype = " << serverInfo.servertype();
        if(!handle->select(oss.str().c_str(),oss.str().size(),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            unsigned int id = tempMap["id"];
            unsigned int port = tempMap["port"];
            std::string ip = tempMap["ip"];
            if(ip != serverInfo.ip() || port != serverInfo.port())
            {
                continue;
            }
            ProtoMsgData::AckVerifyServer ackMsg;
            ackMsg.set_ret(true);
            if(!sendMsg(ackMsg))
            {
                continue;
            }
            m_serverID = id;
            m_serverType = ProtoMsgData::ST_Super;
            setVerify(true);
            ret = true;
            break;
        }
    }while(false);
    handle->resetStatus();
    return ret;
}


