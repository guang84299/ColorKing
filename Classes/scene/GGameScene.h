//
//  GGameScene.h
//
//
//  Created by guang on 16/10/2.
//
//

#ifndef GGameScene_h
#define GGameScene_h

#include "GScene.h"
#include "ui/GRockView.h"
#include "ui/GUIGameOver.h"
#include "sprite/GHeroSprite.h"
#include "sprite/GEnemySprite.h"
#include "sprite/GBulletSprite.h"
#include "sprite/GDropSprite.h"
#include "tools/GTools.h"
#include "data/GCache.h"
#include "model/GLevel.h"
#include "model/GHero.h"
#include "model/GEnemy.h"

class GGameScene : public GScene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
   
    void initUI();
   
    CREATE_FUNC(GGameScene);
    
    void rockHandler(cocos2d::Vec2 &dir,float power,const char *data);
    void touchEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void update(float dt);
    
    
    //更新关卡数据
    void updateLevel(float dt);
    //更新英雄
    void updateHero(float dt);
    //更新敌人
    void updateEnemy(float dt);
    //更新子弹
    void updateBullet(float dt);
    //更新掉落
    void updateDrop(float dt);
    
    void updateUI();
    
    void end(bool isSuccess);
public:
    GHeroSprite* hero;
    std::vector<GEnemySprite*> enemys;
    std::vector<GBulletSprite*> bullets;
    std::vector<GBulletSprite*> enemy_bullets;
    std::vector<GDropSprite*> drops;
    std::vector<GDropSprite*> dropBullets;
    GLevel* level;
private:
    Text* t_coin;
    Text* t_time;
    int coin;
    float time;
    float timeDt;
};


#endif /* GGameScene_h */
