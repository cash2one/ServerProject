#ifndef TASK_HANDLE_H
#define TASK_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "task.h"

class TaskHandle : public MessageHandle
{
    public:
        TaskHandle();
        ~TaskHandle();
        virtual bool init();
};

#endif
