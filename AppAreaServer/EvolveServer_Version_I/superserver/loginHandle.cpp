#include "loginHandle.h"

LoginHandle::LoginHandle() : MessageHandle("登录服客户端消息处理")
{
}

LoginHandle::~LoginHandle()
{
}

bool LoginHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<LoginClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<LoginClient>,ProtoMsgData::msg>(&LoginHandle::call));\
    }
#undef MESSAGE_INIT
    return true;
}
