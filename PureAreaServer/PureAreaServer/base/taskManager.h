#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include "head.h"
#include "connect.h"

class TaskManager : public Singleton<TaskManager>
{
    private:
        std::map<unsigned long,boost::shared_ptr<Connect> > m_taskMap;
    private:
        friend class Singleton<TaskManager>;
        TaskManager()
        {
        }
        ~TaskManager()
        {
        }
    public:
        bool addTask(boost::shared_ptr<Connect> task);
        boost::shared_ptr<Connect> getTask(const unsigned long id);
        inline size_t size() const
        {
            return m_taskMap.size();
        }
        void eraseTask(const unsigned long taskID);
        void randCloseFd(const unsigned long cnt);
        void randOpDB(const unsigned long cnt);
        bool sendServerMsg(const unsigned int serverID,const google::protobuf::Message &message);
        boost::shared_ptr<Connect> getServerTask(const unsigned int serverID);
        void sendHeartMsg();
};

#endif

