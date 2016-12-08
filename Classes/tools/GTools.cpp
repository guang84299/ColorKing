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
