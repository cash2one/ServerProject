#ifndef SERVER_H
#define SERVER_H
#include "head.h"
#include "system.pb.h"
#include "flyerXmlParse.h"
#include "mysqlPool.h"
#include "clientManager.h"
#include "superClient.h"

class Server
{
    public:
        Server(const std::string &name,const ProtoMsgData::ServerType &type);
        ~Server();
    protected:
        std::string m_name;
        ProtoMsgData::ServerType m_type;
        unsigned int m_id;
        std::string m_ip;
        unsigned short m_port;
        std::map<int,int> m_socketPortMap;
        std::vector<struct epoll_event> m_epollEventVec; 
        std::map<unsigned int,ProtoMsgData::ServerInfo> m_serverInfoMap;
        int m_fd;
        int m_epfd;
        bool m_verify;
        std::string m_outIp;
        unsigned short m_outPort;
        int m_outFd;
        boost::shared_ptr<SuperClient> m_superClient;
    private:
        int accept(std::map<int,int> &socketMap);
    public:
        bool init();
        void serverCallBack();
        bool listenPort();
        void main();
        void setServerInfo(const ProtoMsgData::ServerInfo &serverInfo);
        bool getVerify() const;
        virtual bool acceptConnect(const int socket,const int listenPort) = 0;
        ProtoMsgData::ServerType getType() const;
        static void loadExcelTbx(const std::string &file,char *&buf,int &size);
        virtual bool loadConf() = 0;
        virtual bool end() = 0;
        void updateOtherServer(const ProtoMsgData::ServerInfo &serverInfo);
        bool findServer(const unsigned int id);
        void addServer(const ProtoMsgData::ServerInfo &info);
        ProtoMsgData::ServerInfo* getServer(const unsigned int id);
        unsigned int getServerID() const;
        virtual void startServerThread() = 0;
        void startThread();
        virtual void endServerThread() = 0;
        void endThread();
        template<class T>
        bool initConnectServer(const ProtoMsgData::ServerType &connectType,const ProtoMsgData::ServerType &curType)
        {
            bool ret = false;
            std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
            do
            {
                boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
                if(!handle)
                {
                    break;
                }
                char temp[100] = {0};
                snprintf(temp,sizeof(temp),"select id,ip,port from t_serverinfo where servertype = %u",connectType);
                if(!handle->select(temp,strlen(temp),ipVec))
                {
                    break;
                }
                bool breakFlg = false;
                for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
                {
                    std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
                    if(tempMap.find("id") == tempMap.end())
                    {
                        continue;
                    }
                    unsigned int id = tempMap["id"];
                    unsigned int port = tempMap["port"];
                    std::string ip = tempMap["ip"];
                    int fd = 0;
                    if(!Client::connectOwner(fd,ip,port))
                    {
                        char temp[100] = {0};
                        snprintf(temp,sizeof(temp),"[客户端连接服务器] 连接错误(%u,%u,%u,%s,%u",id,connectType,curType,ip.c_str(),port);
                        LOG4CXX_INFO(Flyer::logger,temp);
                        breakFlg = true;
                        break;
                    }
                    ProtoMsgData::ReqVerifyServer reqVerifyServer;
                    ProtoMsgData::ServerInfo *info = reqVerifyServer.mutable_serverinfo();
                    if(!info)
                    {
                        breakFlg = true;
                        break;
                    }
                    info->set_servertype(curType);
                    info->set_id(m_id);
                    info->set_ip(m_ip);
                    info->set_port(m_port);
                    boost::shared_ptr<T> client(new T("服务器客户端",ip,port,fd));
                    client->setServerID(id);
                    client->setServerType(connectType);
                    if(!ClientManager::getInstance().add(client))
                    {
                        breakFlg = true;
                        break;
                    }
                    if(!client->sendMsg(reqVerifyServer))
                    {
                        breakFlg = true;
                        break;
                    }
                }
                if(breakFlg)
                {
                    break;
                }

                //检测链接
                int checkConnect = ClientManager::getInstance().checkStatus(ipVec.size(),connectType);
                while(checkConnect == 0)
                {
                    checkConnect = ClientManager::getInstance().checkStatus(ipVec.size(),connectType);
                }
                ret = checkConnect > 0 ? true : false;

            }while(false);
            return ret;
        }


};

#endif
