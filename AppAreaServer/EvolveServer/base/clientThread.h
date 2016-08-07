#ifndef CLIENT_THREAD_H
#define CLIENT_THREAD_H
#include "head.h"
#include "thread.h"
#include "taskQueue.h"
#include "client.h"

class ClientThread : public Thread,public TaskQueue,public Singleton<ClientThread>
{
    private:
        std::set<unsigned long> m_clientSet;
        int m_epfd;
        std::vector<struct epoll_event> m_eventVec;
    private:
        friend class Singleton<ClientThread>;
        ClientThread();
        ~ClientThread();
    public:
        virtual bool add(const unsigned long id);
        virtual void run();
        bool init();
        void addRecycle(const unsigned long id);

};

#endif

