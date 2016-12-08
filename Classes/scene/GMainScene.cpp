#include "GMainScene.h"
#include "sprite/GHeroSprite.h"
#include "sprite/GEnemySprite.h"
#include "tools/GTools.h"
#include "data/GCache.h"
#include "model/GLevel.h"
#include "model/GHero.h"

USING_NS_CC;

Scene* GMainScene::createScene()
{
    auto layer = GMainScene::create();
    layer->setName("scene");

    return layer;
}

bool GMainScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }
    GCache::getInstance()->init();
    this->level = GCache::getInstance()->getLevel(1);
    this->level->retain();
    
    Size s = Director::getInstance()->getWinSize();
    
    hero = GHeroSprite::create(1);
    hero->setPosition(s.width/2, s.height/2);
    gameLayer->addChild(hero);
    hero->born();
    
    this->schedule(SEL_SCHEDULE(&GMainScene::update));
    
    return true;
}

void GMainScene::update(float dt)
{
    level->updateTimeDt+=dt;
    
    if(level->updateTimeDt >= level->updateTime && enemys.size() < level->maxEnemyNum)
    {
        level->updateTimeDt = 0;
        
        Size s = Director::getInstance()->getWinSize();
        auto enemy = GEnemySprite::create(1);
        enemy->setPosition(random(50, (int)s.width-50), random(50, (int)s.height-50));
        gameLayer->addChild(enemy);
        enemy->born();
        
        enemys.push_back(enemy);
    }
    
    updateHero(dt);
}

void GMainScene::updateHero(float dt)
{
    hero->hero->attackSpeedDt += dt;
    if(hero->hero->attackSpeedDt >= hero->hero->attackSpeed)
    {
        hero->hero->attackSpeedDt = 0;
        //寻找最近目标
        GEnemySprite* target = nullptr;
        for(int i=0;i<enemys.size();i++)
        {
            GEnemySprite* enemy = enemys.at(i);
            float dis = hero->getPos().getDistance(enemy->getPos());
            if(dis < hero->hero->attackRange)
            {
                if(target == nullptr)
                {
                    target = enemy;
                }
                else
                {
                    float dis2 = hero->getPos().getDistance(target->getPos());
                    if(dis < dis2)
                    {
                        target = enemy;
                    }
                }
            }
        }
        hero->changeTarget(target);
        hero->attack();
    }
    
}
