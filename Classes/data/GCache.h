//
//  GCache.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GCache_h
#define GCache_h

#define _T(str) GCache::getInstance()->getFont(str)

#define MUSIC_MIAN "mainBGM.mp3"
#define MUSIC_FIGHT "fightBGM.mp3"
#define SOUND_BUTTON "button.mp3"
#define SOUND_SHOOT "shoot.mp3"
#define SOUND_DIE "dead.mp3"
#define SOUND_BORN "born.mp3"
#define SOUND_SCORE "kill.wav"
#define SOUND_SPEED "speed.mp3"
#define SOUND_GETBULLETS "getBullets.mp3"
#define SOUND_HURT "hurt.wav"
#define SOUND_COIN "coin.wav"
#define SOUND_SKILL "skill.wav"

#include "cocos2d.h"

USING_NS_CC;

class GLevel;
class GHero;
class GEnemy;
class GBullet;
class GGameScene;

class GCache : public Ref
{
private:
    GCache(){};
public:
    static GCache* getInstance();
    
    void init();
    void destory();
    
    void initFont();
    std::string getFont(const std::string &key);
    std::string getLang();
    
    GLevel* getLevel(int level);
    int getLevelNum();
    GHero* getHero(int _id);
    GEnemy* getEnemy(int _id);
    GBullet* getBullet(int _id);
    
    void setGameLevel(int level);
    int getGameLevel();
    
    static void setCurrLevel(int currLevel);
    static int getCurrLevel();
    
    static void setLv(int lv);
    static int getLv();
    
    static void setCoin(int coin);
    static int getCoin();
    
    static void setMusic(bool music);
    static bool isMusic();
    
    static void setAd(bool ad);
    static bool isAd();
    
    GGameScene* getGameScene();
private:
    std::vector<GLevel*> levels;
    std::vector<GHero*> heros;
    std::vector<GEnemy*> enemys;
    std::vector<GBullet*> bullets;
    
    int gameLevel;
    cocos2d::ValueMap v_font;
    std::string lang;
};

#endif /* GCache_h */
