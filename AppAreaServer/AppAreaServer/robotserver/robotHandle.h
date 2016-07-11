#ifndef ROBOT_HANDLE_H
#define ROBOT_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "recordClient.h"

class RobotHandle : public MessageHandle
{
    public:
        RobotHandle();
        ~RobotHandle();
        virtual bool init();
};

#endif
