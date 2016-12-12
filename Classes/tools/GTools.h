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
};

#endif /* GTools_h */
