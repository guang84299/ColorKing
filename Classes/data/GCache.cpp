//
//  GCache.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GCache.h"

#include "tools/GTools.h"
#include "model/GLevel.h"
#include "model/GHero.h"
#include "model/GEnemy.h"
#include "model/GBullet.h"

#include "scene/GGameScene.h"

static GCache* _instance = nullptr;

GCache* GCache::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new GCache();
        _instance->retain();
    }
    return _instance;
}

void GCache::init()
{
    GJsonArray* arr = GTools::getConfigData("levels.json");
    for(int i=0;i<arr->size();i++)
    {
        GLevel* level = GLevel::create(arr->at(i));
        level->retain();
        levels.push_back(level);
    }
    
    GJsonArray* arr_hero = GTools::getConfigData("heros.json");
    for(int i=0;i<arr_hero->size();i++)
    {
        GHero* hero = GHero::create(arr_hero->at(i));
        hero->retain();
        heros.push_back(hero);
    }

    GJsonArray* arr_enemy = GTools::getConfigData("enemys.json");
    for(int i=0;i<arr_enemy->size();i++)
    {
        GEnemy* enemy = GEnemy::create(arr_enemy->at(i));
        enemy->retain();
        enemys.push_back(enemy);
    }
    
    GJsonArray* arr_bullet = GTools::getConfigData("bullets.json");
    for(int i=0;i<arr_bullet->size();i++)
    {
        GBullet* bullet = GBullet::create(arr_bullet->at(i));
        bullet->retain();
        bullets.push_back(bullet);
    }
    
    lang = Application::getInstance()->getCurrentLanguageCode();
    initFont();
}

void GCache::destory()
{
    for(int i=0;i<levels.size();i++)
    {
        GLevel* level = levels.at(i);
        level->release();
    }
    levels.clear();
    
    for(int i=0;i<heros.size();i++)
    {
        GHero* hero = heros.at(i);
        hero->release();
    }
    heros.clear();
    
    for(int i=0;i<enemys.size();i++)
    {
        GEnemy* enemy = enemys.at(i);
        enemy->release();
    }
    enemys.clear();
    
    for(int i=0;i<bullets.size();i++)
    {
        GBullet* bullet = bullets.at(i);
        bullet->release();
    }
    bullets.clear();
}

std::string GCache::getLang()
{
    return this->lang;
}

void GCache::initFont()
{
    std::string path = "font-";
    path = path + this->lang + std::string(".plist");
    if(this->lang == "zh" || !FileUtils::getInstance()->isFileExist(path))
    {
        path = "font.plist";
    }
    v_font =  FileUtils::getInstance()->getValueMapFromFile(path);
}

std::string GCache::getFont(const std::string &key)
{
    std::string str = v_font[key.c_str()].asString();
    return str;
}


GLevel* GCache::getLevel(int lv)
{
    for(int i=0;i<levels.size();i++)
    {
        GLevel* level = levels.at(i);
        if(level->_id == lv)
        {
            return GLevel::create(level);
        }
    }
    return nullptr;
}

int GCache::getLevelNum()
{
    return levels.size();
}

GHero* GCache::getHero(int _id)
{
    for(int i=0;i<heros.size();i++)
    {
        GHero* hero = heros.at(i);
        if(hero->_id == _id)
        {
            return GHero::create(hero);
        }
    }
    return nullptr;
}

GEnemy* GCache::getEnemy(int _id)
{
    for(int i=0;i<enemys.size();i++)
    {
        GEnemy* enemy = enemys.at(i);
        if(enemy->_id == _id)
        {
            return GEnemy::create(enemy);
        }
    }
    return nullptr;
}

GBullet* GCache::getBullet(int _id)
{
    for(int i=0;i<bullets.size();i++)
    {
        GBullet* bullet = bullets.at(i);
        if(bullet->_id == _id)
        {
            return GBullet::create(bullet);
        }
    }
    return nullptr;
}

void GCache::setGameLevel(int level)
{
    this->gameLevel = level;
}

int GCache::getGameLevel()
{
    return this->gameLevel;
}

void GCache::setCurrLevel(int currLevel)
{
    UserDefault::getInstance()->setIntegerForKey("currLevel", currLevel);
    UserDefault::getInstance()->flush();
}

int GCache::getCurrLevel()
{
    return UserDefault::getInstance()->getIntegerForKey("currLevel");
}

void GCache::setLv(int lv)
{
    UserDefault::getInstance()->setIntegerForKey("lv", lv);
    UserDefault::getInstance()->flush();
}
int GCache::getLv()
{
    return UserDefault::getInstance()->getIntegerForKey("lv");
}

void GCache::setCoin(int coin)
{
    UserDefault::getInstance()->setIntegerForKey("coin", coin);
    UserDefault::getInstance()->flush();
}

int GCache::getCoin()
{
    return UserDefault::getInstance()->getIntegerForKey("coin");
}

void GCache::setMusic(bool music)
{
    UserDefault::getInstance()->setBoolForKey("music", music);
    UserDefault::getInstance()->flush();
}
bool GCache::isMusic()
{
    return UserDefault::getInstance()->getBoolForKey("music");
}

void GCache::setAd(bool ad)
{
    UserDefault::getInstance()->setBoolForKey("ad", ad);
    UserDefault::getInstance()->flush();
}
bool GCache::isAd()
{
    return UserDefault::getInstance()->getBoolForKey("ad");
}

GGameScene* GCache::getGameScene()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    GGameScene* gameScene = static_cast<GGameScene*>(scene);
    return gameScene;
}
