//
//  GTools.h
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#ifndef GTools_h
#define GTools_h

#include "cocos2d.h"
#include "data/GJson.h"

USING_NS_CC;

class GTools
{
public:
    static GJsonArray* getConfigData(const std::string& path);
    static float getAngle(const Vec2& dir);
    
    //sound
    static void playMusic(const std::string &file);
    static void pauseMusic();
    static void stopMusic();
    static void resumeMusic(const std::string &file);
    static void playSound(const std::string &sound);
    
    static void preload();

};

#endif /* GTools_h */
