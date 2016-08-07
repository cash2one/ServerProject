#include "clientManager.h"
#include "recycleThread.h"
#include "clientThread.h"

ClientThread::ClientThread() : Thread("客户端管理器")
{
    init();
}

ClientThread::~ClientThread()
{
    TEMP_FAILURE_RETRY(::close(m_epfd));
}

bool ClientThread::init()
{
    m_epfd = epoll_create(atol(Flyer::globalConfMap["addepollsize"].c_str()));
    return m_epfd != -1;
}

bool ClientThread::add(const unsigned long id)
{
    bool flag = false;
    do
    {
        boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(id);
        if(!client)
        {
            break;
        }
        client->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
        std::pair<std::set<unsigned long>::iterator,bool>ret = m_clientSet.insert(id);
        flag = ret.second;
        if(!flag)
        {
            break;
        }
        if(m_clientSet.size() > m_eventVec.size())
        {
            m_eventVec.resize(m_clientSet.size() + atol(Flyer::globalConfMap["addepollsize"].c_str()));
        }
    }while(false);
    return flag;
}

void ClientThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_clientSet.empty())
        {
            std::vector<unsigned long> delVec;
            int ret = epoll_wait(m_epfd,&m_eventVec[0],m_clientSet.size(),0);
            for(int cnt = 0;cnt < ret;++cnt)
            {
                struct epoll_event &event = m_eventVec[cnt];
                bool delFlg = true;
                do
                {
                    boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(event.data.u64);
                    if(!client)
                    {
                        break;
                    }
                    if(event.events & EPOLLPRI)
                    {
                        break;
                    }
                    if(event.events & EPOLLERR)
                    {
                        break;
                    }
                    if(event.events & EPOLLIN)
                    {
                        client->accpetMsg();
                    }
                    if(event.events & EPOLLOUT)
                    {
                    }
                    delFlg = false;
                }while(false);
                if(delFlg)
                {
                    delVec.push_back(event.data.u64);
                }
                event.events = 0;
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                addRecycle(*iter);
            }
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_clientSet.begin();iter != m_clientSet.end();++iter)
    {
        addRecycle(*iter);
    }
    m_clientSet.clear();
}

void ClientThread::addRecycle(const unsigned long id)
{
    boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(id);
    if(client)
    {
        client->delEpoll(m_epfd,EPOLLIN);
        RecycleThread::getInstance().add(id);
    }
    m_clientSet.erase(id);
}
