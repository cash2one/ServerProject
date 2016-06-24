#include "sceneUser.h"
#include "clientManager.h"
#include "parseMessage.h"

SceneUser::SceneUser(const unsigned long charID,const unsigned short gatewayID) : m_charID(charID),m_phone(),m_gatewayID(gatewayID),m_onTime(0),m_offTime(0)
{
}

SceneUser::~SceneUser()
{
}

bool SceneUser::parseFromBinary(const ProtoMsgData::UserBinary &binary)
{
    bool ret = false;
    do
    {
        if(binary.charid() != m_charID)
        {
            break;
        }
        m_phone = binary.phone();
        m_onTime = binary.ontime();
        m_offTime = binary.offtime();
        ret = true;
    }while(false);
    return ret;
}

bool SceneUser::serializeToArray(ProtoMsgData::UserBinary &binary)
{
    bool ret = false;
    do
    {
        binary.set_charid(m_charID);
        binary.set_phone(m_phone);
    }while(false);
    return ret;
}

bool SceneUser::sendUserMsg(const google::protobuf::Message &message)
{
    bool ret = false;
    do
    {
        std::string msg;
        encodeMessage(&message,msg);
        ProtoMsgData::AckUserMsg ackMsg;
        ackMsg.set_charid(m_charID);
        ackMsg.set_data(msg);
        boost::shared_ptr<Client> client = ClientManager::getInstance().getServerClient(m_gatewayID);
        if(!client)
        {
            break;
        }
        ret = client->sendMsg(ackMsg);
    }while(false);
    return ret;
}

bool SceneUser::sendGatewayMsg(const google::protobuf::Message &message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Client> client = ClientManager::getInstance().getServerClient(m_gatewayID);
        if(!client)
        {
            break;
        }
        ret = client->sendMsg(message);
    }while(false);
    return ret;
}

bool SceneUser::onLine()
{
    bool ret = false;
    do
    {
    }while(false);
    return ret;
}
