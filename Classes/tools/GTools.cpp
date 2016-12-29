//
//  GTools.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GTools.h"
#include "data/GCache.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

GJsonArray* GTools::getConfigData(const std::string& path)
{
    std::string data = FileUtils::getInstance()->getStringFromFile(path);
    return GJsonArray::create(data);
}


float GTools::getAngle(const cocos2d::Vec2 &dir)
{
    float angle = -180 / M_PI * dir.getAngle() + 90;
    angle = angle < 0 ? (360 + angle) : angle;
    angle = angle > 180 ? angle-360 : angle;
    return angle;
}

void GTools::playMusic(const std::string &file)
{
    stopMusic();
    if(GCache::isMusic())
        SimpleAudioEngine::getInstance()->playBackgroundMusic(file.c_str(),true);
}
void GTools::pauseMusic()
{
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void GTools::stopMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void GTools::resumeMusic(const std::string &file)
{
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
        playMusic(file);
}
void GTools::playSound(const std::string &sound)
{
    if(GCache::isMusic())
        SimpleAudioEngine::getInstance()->playEffect(sound.c_str());
}

void GTools::preload()
{
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_BUTTON);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SHOOT);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_DIE);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_BORN);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SCORE);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SPEED);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_GETBULLETS);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_HURT);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_COIN);
    SimpleAudioEngine::getInstance()->preloadEffect(SOUND_SKILL);

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FIGHT);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("she.plist");
}
