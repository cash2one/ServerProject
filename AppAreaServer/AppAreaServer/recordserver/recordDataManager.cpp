#include "recordDataManager.h"
#include "mysqlPool.h"
#include "flyerValue.h"
#include "redisMemManager.h"
#include "head.h"
#include "serialize.pb.h"

unsigned long RecordDataManager::s_charID = 0; 
RecordDataManager::RecordDataManager()
{
}

RecordDataManager::~RecordDataManager()
{
}

bool RecordDataManager::init()
{
    bool ret = false;
    do
    {
        if(!loadUserData())
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool RecordDataManager::loadUserData()
{
    bool ret = false;
    do
    {
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select * from t_user");
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("charid") == tempMap.end())
            {
                continue;
            }
            unsigned long charID = tempMap["charid"];
            std::string binary = tempMap["binary"];
            char buffer[Flyer::msglen] = {0};
            memmove(buffer,binary.c_str(),binary.size());
            ProtoMsgData::UserBinary userBinary;
            bool isLoad = true;
            try
            {
                userBinary.ParseFromArray(buffer,binary.size());
            }
            catch(...)
            {
                isLoad = false;
            }

            Info(Flyer::logger,"[加载角色信息] (" << charID << "," << isLoad << ")");
            if(!isLoad || userBinary.charid() != charID)
            {
                continue;
            }
            boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
            if(!redisMem)
            {
                break;
            }
            if(!redisMem->setInt("charid",userBinary.phone().c_str(),charID))
            {
                break;
            }
            redisMem = RedisMemManager::getInstance().getRedis(charID);
            if(!redisMem)
            {
                break;
            }
            if(!redisMem->setString("phone",charID,userBinary.phone().c_str()))
            {
                break;
            }
            if(!redisMem->setBin("userbinary",charID,buffer,binary.size()))
            {
                break;
            }
        }
        ipVec.clear();
        bzero(temp,sizeof(temp));
        snprintf(temp,sizeof(temp),"select max(charid) as charid from t_user");
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("charid") != tempMap.end())
            {
                s_charID = tempMap["charid"];
            }
            break;
        }
        ret = true;
    }while(false);
    Info(Flyer::logger,"[加载角色信息完毕] (" << s_charID << "," << ret << ")")
    return ret;
}

bool RecordDataManager::createUser(const std::string &phone,unsigned long &charID)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        ProtoMsgData::UserBinary binary;
        binary.set_phone(phone);
        binary.set_charid(s_charID + 1);
        binary.set_ontime(0);
        binary.set_offtime(0);
        char buffer[Flyer::msglen];
        binary.SerializeToArray(buffer,sizeof(buffer));
        std::ostringstream oss;
        oss << "insert into t_user values(" << binary.charid() << "," << binary.phone() << ",";
        handle->getRealString(buffer,binary.ByteSize(),oss);
        oss << ")";
        if(!handle->execSql(oss.str().c_str(),oss.str().size()))
        {
            break;
        }
        s_charID += 1;
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setInt("charid",binary.phone().c_str(),binary.charid()))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(binary.charid());
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setString("phone",binary.charid(),binary.phone().c_str()))
        {
            break;
        }
        if(!redisMem->setBin("userbinary",binary.charid(),buffer,binary.ByteSize()))
        {
            break;
        }
        charID = binary.charid();
        ret = true;
    }while(false);
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[新建角色] %s(%s)",ret ? "成功" : "失败", phone.c_str());
    Info(Flyer::logger,temp);
    return ret;
}

