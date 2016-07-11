#include "robotHandle.h"

RobotHandle::RobotHandle() : MessageHandle("机器人消息处理")
{
}

RobotHandle::~RobotHandle()
{
}

bool RobotHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<RobotClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<RobotClient>,ProtoMsgData::msg>(&RobotHandle::call));\
    RobotClient::s_robotMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
#undef MESSAGE_INIT
    return true;
}
