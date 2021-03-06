#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "client.h"

class ClientHandle : public MessageHandle
{
    public:
        ClientHandle();
        ~ClientHandle();
        virtual bool init();
};

#endif
