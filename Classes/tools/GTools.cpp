//
//  GTools.cpp
//  ColorKing
//
//  Created by guang on 2016/12/6.
//
//

#include "GTools.h"

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
