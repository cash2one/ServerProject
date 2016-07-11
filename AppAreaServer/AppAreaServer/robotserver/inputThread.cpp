#include "inputThread.h"
#include "flyer.h"
#include "recycleThread.h"

void InputThread::run()
{
    while(!isFinal())
    {
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}



