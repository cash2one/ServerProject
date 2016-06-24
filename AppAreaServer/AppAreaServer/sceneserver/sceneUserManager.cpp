#include "sceneUserManager.h"
#include "serialize.pb.h"

SceneUserManager::SceneUserManager()
{
}

SceneUserManager::~SceneUserManager()
{
}

bool SceneUserManager::add(boost::shared_ptr<SceneUser> user)
{
    std::pair<std::map<unsigned long,boost::shared_ptr<SceneUser> >::iterator,bool> ret = m_userMap.insert(std::pair<unsigned long,boost::shared_ptr<SceneUser> >(user->getCharID(),user));
    return ret.second;
}

void SceneUserManager::del(const unsigned long charID)
{
    m_userMap.erase(charID);
}
