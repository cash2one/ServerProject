#ifndef SCENE_USER_H
#define SCENE_USER_H
#include "head.h"
#include "serialize.pb.h"

class SceneUser
{
    public:
        SceneUser(const unsigned long charID,const unsigned short gatewayID);
        ~SceneUser();
    public:
        inline unsigned long getCharID() const
        {
            return m_charID;
        }
        bool parseFromBinary(const ProtoMsgData::UserBinary &binary);
        bool serializeToArray(ProtoMsgData::UserBinary &binary);
        bool sendUserMsg(const google::protobuf::Message &message);
        bool sendGatewayMsg(const google::protobuf::Message &message);
    public:
        bool onLine();
    private:
        unsigned long m_charID;
        std::string m_phone;
        unsigned short m_gatewayID;
        unsigned int m_onTime;
        unsigned int m_offTime;


};

#endif
