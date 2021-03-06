#include "connect.h"
#include "cmdFunManager.h"
#include "mysqlPool.h"
#include "parseMessage.h"
#include "construct.h"
#include "system.pb.h"

unsigned long Connect::s_tempid = 0;
ConnectMessageDispatcher Connect::s_connectMsgDispatcher("链接消息处理器");
Connect::Connect(const int socket) : m_socket(socket),m_id(++s_tempid),m_status(Task_Status_Close),m_lifeTime(),m_serverID(0),m_serverType(ProtoMsgData::ST_Client),m_heartTime()
{
}

void Connect::addEpoll(const int epfd,const unsigned long events)
{
    struct epoll_event event;
    event.data.u64 = m_id;
    event.events = events;
    epoll_ctl(epfd,EPOLL_CTL_ADD,m_socket,&event);
}

void Connect::delEpoll(const int epfd,const unsigned long events)
{
    struct epoll_event event;
    event.data.u64 = m_id;
    event.events = events;
    epoll_ctl(epfd,EPOLL_CTL_DEL,m_socket,&event);
}

bool Connect::accpetMsg()
{
    bool ret = false;
    do
    {
        if(!m_messageBuffer.adjustPos())
        {
            break;
        }
        unsigned int len = recv(m_socket,m_messageBuffer.beginWrite(),m_messageBuffer.ableWriteSize(),0);
        if(len == 0)
        {
            break;
        }
        else if(len < 0)
        {
            if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
            {
                break;
            }
            ret = true;
            break;
        }
        m_messageBuffer.moveWritePos(len);
        unsigned char buffer[atol(Flyer::globalConfMap["datasize"].c_str())] = {0};

        //这里用new MessageData析构会出问题
        MessageData *messageData = (MessageData*)buffer;
        constructInBuffer(messageData);
        while(m_messageBuffer.beginRead(messageData))
        {
            boost::shared_ptr<google::protobuf::Message> message = decodeMessage(messageData);
            if(!message)
            {
                continue;
            }
            MsgRet flg = s_connectMsgDispatcher.dispatch(this,message); 
            if(flg == MR_No_Register)
            {
                flg = this->dispatcher(message);
            }
            Debug(Flyer::logger,"接受且处理消息(" << m_id << "," << message->GetTypeName() << "," << flg << ")");
        }
        ret = true;
    }while(false);

    return ret;
}

void Connect::closeFd()
{
    Info(Flyer::logger,"断开连接(" << getID() << ")");
    if(m_socket != -1)
    {
        close(m_socket);
    }
    m_socket = -1;
}

void Connect::doAcceptMessage()
{
    while(!m_messageQueue.empty())
    {
        boost::shared_ptr<MessageData> messageData = m_messageQueue.getMessage();
        std::string messageName = CmdFunManager::getInstance().getProtoName(messageData->key);
        if(messageName.empty())
        {
            Error(Flyer::logger,"接受到未知消息(" << messageData->key << ")");
            continue;
        }
        google::protobuf::Message *message = createMessage(messageName.c_str());
        if(!message)
        {
            Error(Flyer::logger,"没有生成消息实例(" << messageName << ")");
            continue;
        }
        shared_ptr<google::protobuf::Message> sharedMessage(message);
        sharedMessage->ParseFromArray(&messageData->data[0], messageData->size);
    }
}

bool Connect::randTestDB()
{
    bool ret = false;
    char temp[100] = {0};
    do
    {
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        snprintf(temp,sizeof(temp),"INSERT INTO test VALUES(0,%lu)",m_id);
        if(!handle->execSql(temp,strlen(temp)))
        {
            break;
        }
        ret = true;
    }while(false);

    char mark[100] = {0};
    snprintf(mark,sizeof(mark),"[数据库操作] 插入%s(%s)",ret ? "成功" : "失败",temp);
    Info(Flyer::logger,mark);
    return ret;
}

bool Connect::sendMsg(const google::protobuf::Message &message)
{
    std::string ret;
    encodeMessage(&message,ret);
    bool flg = send(m_socket,ret.c_str(),ret.size(),0);
    Debug(Flyer::logger,"发送消息(" << m_id << "," << message.GetTypeName() << "," << flg << ")");
    return flg;
}

bool Connect::sendMsg(int fd,const google::protobuf::Message &message)
{
    std::string ret;
    encodeMessage(&message,ret);
    bool flg = send(fd,ret.c_str(),ret.size(),0);
    Debug(Flyer::logger,"发送消息(" << 0 << "," << message.GetTypeName() << "," << flg << ")");
    return flg;
}



TaskStatus Connect::getStatus()
{
    return m_status;
}

void Connect::setStatus(const TaskStatus status)
{
    m_status = status;
}

void Connect::nextStatus()
{
    switch(m_status)
    {
        case Task_Status_Close:
            {
                m_status = Task_Status_Verify;
            }
            break;
        case Task_Status_Verify:
            {
                m_status = Task_Status_Main;
            }
            break;
        case Task_Status_Main:
            {
                m_status = Task_Status_Recycle;
            }
            break;
        default:
            {
            }
            break;
    }
}

bool Connect::isElapse()
{
    return m_lifeTime.elapse() >= (unsigned int)atol(Flyer::globalConfMap["taskwaittime"].c_str());
}

void Connect::resetLifeTime()
{
    m_lifeTime.now();
}

bool Connect::isHeartElapse()
{
    return m_heartTime.elapse() >= (unsigned int)atol(Flyer::globalConfMap["hearttime"].c_str());
}

void Connect::resetHeartTime()
{
    m_heartTime.now();
}

bool Connect::sendHeartMsg()
{
    if(!m_serverID)
    {
        return true;
    }
    if(isHeartElapse())
    {
        return false;
    }
    ProtoMsgData::ReqHeartBeat reqMsg;
    sendMsg(reqMsg);
    resetHeartTime();
    return true;
}
