#ifndef MYSQL_HANDLE_H
#define MYSQL_HANDLE_H
#include "head.h"
#include "singleton.h"
#include "mysqlUrl.h"
#include "timefun.h"
#include "flyer.h"

enum HandleStatus
{
    Handle_Invalid = 0,  //无效
    Handle_Valid = 1,    //有效
    Handle_Used = 2,     //正在使用
};

class MysqlHandle : public DisCopy
{
    private:
        const UrlInfo m_urlInfo;
        const unsigned int m_id;
        static unsigned int s_tempid;
        MYSQL *m_mysql;
        HandleStatus m_status;
        unsigned int m_usedCnt;
        TimeTv m_lifeTime;
    public:
        MysqlHandle(const UrlInfo &urlInfo);
        bool init();
        bool initMysql();
        void closeHandle();
        bool checkConnect();
        HandleStatus getStatus();
        unsigned int getID();
        bool execSql(const char *sql,const unsigned int sqlLen);
};

#endif

