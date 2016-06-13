#include "gatewayServer.h"
#include "flyer.h"
#include "superClient.h"
#include "messageHandle.h"
#include "excelBase.h"
#include "gatewayTimeTick.h"
#include "recordClient.h"
#include "sceneClient.h"
#include "recordHandle.h"
#include "sceneHandle.h"
#include "redisMemManager.h"
#include "system.pb.h"

GatewayServer::GatewayServer() : Server("网关服务器",ProtoMsgData::ST_Gateway)
{
}

GatewayServer::~GatewayServer()
{
}

bool GatewayServer::init()
{
    bool ret = false;
    do
    {
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RecordHandle>(new RecordHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<SceneHandle>(new SceneHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        boost::shared_ptr<GatewayServer> ptr(this);
        SuperClient::getInstance().s_server = ptr;
        if(!SuperClient::getInstance().init())
        {
            break;
        }
        SuperClient::getInstance().start();
        while(!getVerify())
        {
        }
        if(!listenPort())
        {
            break;
        }
        startThread();
        if(!initConnectServer<RecordClient>(ProtoMsgData::ST_Record,ProtoMsgData::ST_Gateway))
        {
            break;
        }
        if(!initConnectServer<SceneClient>(ProtoMsgData::ST_Scene,ProtoMsgData::ST_Gateway))
        {
            break;
        }
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        ProtoMsgData::GatewayInfo gateInfo;
        gateInfo.set_id(m_id);
        gateInfo.set_ip(m_ip);
        gateInfo.set_port(m_port);
        gateInfo.set_person(0);
        gateInfo.set_status(ProtoMsgData::GS_Normal);
        char temp[Flyer::msglen] = {0};
        gateInfo.SerializeToArray(temp,Flyer::msglen);
        if(!redisMem->setSet("gateway","idset",m_id))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(m_id);
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setBin("gateway",m_id,temp,gateInfo.ByteSize()))
        {
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

bool GatewayServer::loadConf()
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

bool GatewayServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool GatewayServer::end()
{
    endThread();
    return true;
}

void GatewayServer::startServerThread()
{
    GatewayTimeTick::getInstance().start();
}

void GatewayServer::endServerThread()
{
    GatewayTimeTick::getInstance().final();
    GatewayTimeTick::getInstance().end();
}

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Gateway");
    Flyer::setLogger("log/gateway.log");
    if(GatewayServer::getInstance().init())
    {
        Info(Flyer::logger,"[管理服务器] 启动成功");
        GatewayServer::getInstance().main();
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
