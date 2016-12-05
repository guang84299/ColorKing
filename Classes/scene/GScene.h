//
//  GScene.h
//
//  Created by guang on 16/10/1.
//
//

#ifndef GScene_h
#define GScene_h

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class GScene : public cocos2d::Scene
{
public:
    
    virtual bool init();
    
    CREATE_FUNC(GScene);
    
protected:
    cocos2d::Layer * uiLayer;
private:
};

#endif /* GScene_h */
