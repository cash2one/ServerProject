#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"

class MainThread : public Thread,public TaskQueue,public Singleton<MainThread>
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::map<unsigned long,boost::shared_ptr<Connect> > m_taskSet;
    private:
        friend class Singleton<MainThread>;
        MainThread() : Thread("主线程")
        {
            m_epfd = epoll_create(atol(Flyer::globalConfMap["threadprocesstask"].c_str()));
        }
        ~MainThread()
        {
            TEMP_FAILURE_RETRY(::close(m_epfd));
        }
    public:
        bool add(boost::shared_ptr<Connect> task);
        virtual void run();
};

#endif


