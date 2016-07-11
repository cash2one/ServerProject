#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H 
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"

class InputThread : public Thread,public TaskQueue,public Singleton<InputThread>
{
    private:
        friend class Singleton<InputThread>;
        InputThread() : Thread("机器人输入线程")
        {
        }
        ~InputThread()
        {
        }
    public:
        virtual void run();
};

#endif


