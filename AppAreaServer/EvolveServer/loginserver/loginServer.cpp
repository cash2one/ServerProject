#include "loginServer.h"
#include "flyer.h"
#include "serverTask.h"
#include "taskManager.h"
#include "messageHandle.h"
#include "serverHandle.h"
#include "recycleThread.h"
#include "loginTimeTick.h"
#include "mysqlPool.h"
#include "excelBase.h"
#include "redisMemManager.h"
#include "loginHandle.h"
#include "httpThread.h"
#include "threadPool.h"

static void ctrlHandler(int signal)
{
    Info(Flyer::logger,"[登陆服务器] 终止");
    LoginServer &ref = LoginServer::getInstance();
    ref.setTerminate();
}
LoginServer::LoginServer() :Server("登陆服务器",ProtoMsgData::ST_Login)
{
}

LoginServer::~LoginServer()
{
}

bool LoginServer::init()
{
    bool ret = false;
    do
    {
        struct sigaction sig;
        sig.sa_handler = ctrlHandler;
        sig.sa_flags = 0;
        sigemptyset(&sig.sa_mask);
        sigaction(SIGINT,&sig,NULL);
#if 0
        sigaction(SIGQUIT,&sig,NULL);
        sigaction(SIGABRT,&sig,NULL);
        sigaction(SIGTERM,&sig,NULL);
        sigaction(SIGHUP,&sig,NULL);
#endif

        if(!Server::init())
        {
            break;
        }
        if(!loadAccount())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<ServerHandle>(new ServerHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<LoginHandle>(new LoginHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        if(!initLoginIp())
        {
            break;
        }
        startThread();
        ret = true;
    }while(false);

    return ret;
}

bool LoginServer::acceptConnect(const int socket,const int listenPort)
{
    bool ret = false;
    do
    {
        if(listenPort == m_port)
        {
            boost::shared_ptr<ServerTask> task(new ServerTask(socket));
            if(TaskManager::getInstance().addTask(task))
            {
                task->setServerType(ProtoMsgData::ST_Super);
                ret = ThreadPool::getInstance().addVerify(task->getID());
            }
            if(!ret)
            {
                ThreadPool::getInstance().addRecycle(task->getID());
            }
        }
        else
        {
            boost::shared_ptr<LoginTask> task(new LoginTask(socket));
            if(TaskManager::getInstance().addTask(task))
            {
                task->setServerType(ProtoMsgData::ST_Client);
                ret = ThreadPool::getInstance().addVerify(task->getID());
            }
            if(!ret)
            {
                ThreadPool::getInstance().addRecycle(task->getID());
            }
        }
    }while(false);
    return ret;
}

bool LoginServer::initLoginIp()
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
        std::ostringstream oss;
        oss << "select id,ip,port,outip,outport from t_serverinfo where servertype = " << ProtoMsgData::ST_Login;
        if(!handle->select(oss.str().c_str(),oss.str().size(),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("id") == tempMap.end())
            {
                continue;
            }
            m_id = tempMap["id"];
            std::string ip = tempMap["ip"];
            m_ip = ip;
            m_port = tempMap["port"];
            std::string outIp = tempMap["outip"];
            m_outIp = outIp;
            m_outPort = tempMap["outport"];
            if(!listenPort())
            {
                break;
            }
        }
        ret = true;

    }while(false);
    handle->resetStatus();
    return ret;
}

bool LoginServer::loadConf()
{
    bool ret = false;
    do
    {
        if(!loadExcelConf())
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool LoginServer::loadExcelConf() 
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool LoginServer::end()
{
    endThread();
    return true;
}

void LoginServer::endServerThread()
{
    LoginTimeTick::getInstance().final();
    LoginTimeTick::getInstance().end();
}

void LoginServer::startServerThread()
{
    LoginTimeTick::getInstance().start();
    HttpThread::getInstance().start();
}

bool LoginServer::loadAccount()
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select phone,passwd from t_register");
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(auto iter = ipVec.begin();iter != ipVec.end();++iter)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = *iter;
            std::string phone = tempMap["phone"];
            std::string passwd = tempMap["passwd"];
            if(!redisMem->setString("register",phone.c_str(),passwd.c_str()))
            {
                Error(Flyer::logger,"[注册表] 写入redis失败(" << phone.c_str() << "," << passwd.c_str() << ")");
                continue;
            }
            std::string getPasswd = redisMem->getString("register",phone.c_str());
            Debug(Flyer::logger,"[注册表] 读取redis(" << phone.c_str() << "," << getPasswd.c_str() << ")");
        }
        ret = true;
    }while(false);
    handle->resetStatus();
    return ret;
}

int main()
{
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Login");
    Flyer::setLogger("log/login.log");
    if(LoginServer::getInstance().init())
    {
        Info(Flyer::logger,"[登陆服务器] 启动成功");
        LoginServer::getInstance().main();
    }
    Flyer::destory();
    return 0;
}

