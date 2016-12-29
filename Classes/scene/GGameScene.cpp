//
//  GGameScene.cpp
//
//  Created by guang on 16/10/2.
//
//

#include "GGameScene.h"
#include "scene/GHomeScene.h"

USING_NS_CC;

Scene* GGameScene::createScene()
{
    auto layer = GGameScene::create();
    layer->setName("scene");
    
    return layer;
}

bool GGameScene::init()
{
    if ( !GScene::init() )
    {
        return false;
    }

    this->level = GCache::getInstance()->getLevel(GCache::getInstance()->getGameLevel());
    this->level->retain();
    
    initUI();
    
    Size s = Director::getInstance()->getWinSize();
    
    hero = GHeroSprite::create(1);
    hero->setPosition(s.width/2, s.height/2);
    gameLayer->addChild(hero,2);
    hero->born();
    
    coin = 0;
    time = this->level->time+1;
    
    this->schedule(SEL_SCHEDULE(&GGameScene::update));
    GTools::playSound(SOUND_BORN);
    return true;
}

void GGameScene::initUI()
{
    Size s = Director::getInstance()->getWinSize();
    
    GRockView* view = GRockView::create(GROCK_CALLBACK(GGameScene::rockHandler, this));
    uiLayer->addChild(view);
    
    char c[7];
    sprintf(c, "%d",this->level->time);
    t_time = Text::create(_T("game_2")+c, "", 24);
    t_time->setPosition(Vec2(s.width/2,s.height-30));
    uiLayer->addChild(t_time);
    
    t_coin = Text::create(_T("game_1")+"0", "", 22);
    t_coin->setPosition(Vec2(s.width/2,s.height-70));
    uiLayer->addChild(t_coin);
    
    auto btn = Button::create("sound.png","sound.png");
    btn->setName("sound");
    btn->setAnchorPoint(Vec2(0.5,1));
    btn->setPosition(Vec2(60,s.height-20));
    btn->addTouchEventListener(CC_CALLBACK_2(GGameScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    if(!GCache::isMusic())
    {
        btn->loadTextures("sound_close.png", "sound_close.png");
    }
    
    btn = Button::create("pause.png","pause.png");
    btn->setName("pause");
    btn->setAnchorPoint(Vec2(0.5,1));
    btn->setPosition(Vec2(s.width-60 - 120,s.height-20));
    btn->addTouchEventListener(CC_CALLBACK_2(GGameScene::touchEvent, this));
    uiLayer->addChild(btn);
    
    btn = Button::create("home.png","home.png");
    btn->setName("home");
    btn->setAnchorPoint(Vec2(0.5,1));
    btn->setPosition(Vec2(s.width-60,s.height-20));
    btn->addTouchEventListener(CC_CALLBACK_2(GGameScene::touchEvent, this));
    uiLayer->addChild(btn);
}

void GGameScene::update(float dt)
{
    updateLevel(dt);
    updateHero(dt);
    updateEnemy(dt);
    updateBullet(dt);
    updateDrop(dt);
}

void GGameScene::updateLevel(float dt)
{
    level->updateTimeDt+=dt;
    level->updateBulletTimeDt += dt;
    
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
    
    if(level->updateBulletTimeDt >= level->updateBulletTime && dropBullets.size() < level->maxBulletNum)
    {
        level->updateBulletTimeDt = 0;
        
        Size s = Director::getInstance()->getWinSize();
        GDropSprite* dropBullet = GDropSprite::create(level->getRandBulletId(), 1);
        dropBullet->setPosition(random(50, (int)s.width-50), random(50, (int)s.height-150));
        gameLayer->addChild(dropBullet);
        
        dropBullets.push_back(dropBullet);
    }
    
    if(timeDt >= 1)
    {
        timeDt = 0;
        updateUI();
    }
    timeDt += dt;
    time -= dt;
}

void GGameScene::updateHero(float dt)
{
    if(hero->state == GSprite::State::REMOVE)
    {
        this->unschedule(SEL_SCHEDULE(&GGameScene::update));
        this->runAction(Sequence::create(DelayTime::create(1),
                                         CallFunc::create(CC_CALLBACK_0(GGameScene::end, this,false)),
                                         NULL));
        return;
    }
    hero->hero->attackSpeedDt += dt;
    if(hero->hero->attackSpeedDt >= hero->hero->attackSpeed)
    {
        hero->hero->attackSpeedDt = 0;
        //寻找最近目标
        if(!hero->isSkill)
        {
            hero->attack();
        }
    }
    //判断英雄和掉落子弹碰撞
    for(int i=0;i<dropBullets.size();i++)
    {
        GDropSprite* drop = dropBullets.at(i);
        if(drop->getPosition().getDistance(hero->getPos())
           < drop->getContentSize().width + hero->getContentSize().width)
        {
            hero->changeSkill(drop->_id);
            drop->die2(hero->getPos());
            dropBullets.erase(dropBullets.begin() + i);
            break;
        }
    }
}

void GGameScene::updateEnemy(float dt)
{
    for(int i=0;i<enemys.size();i++)
    {
        GEnemySprite* enemy = enemys.at(i);
        if(enemy->state == GSprite::State::REMOVE)
        {
            enemys.erase(enemys.begin()+i);
            break;
        }
        else
        {
            //如果敌人能攻击，随机一个状态
            GSprite::State state = enemy->randState();
            if(state == GSprite::State::IDLE && enemy->changeState(GSprite::State::IDLE))
            {
                enemy->idle();
            }
            else if(state == GSprite::State::RUN && enemy->changeState(GSprite::State::RUN))
            {
                float dis = hero->getPos().getDistance(enemy->getPos());
                if(dis > enemy->getAttackRange())
                {
                    enemy->run();
                }
                else
                {
                    enemy->changeState(GSprite::State::RUNEND);
                }
            }
            else if(state == GSprite::State::ATTACK && enemy->changeState(GSprite::State::ATTACK))
            {
                float dis = hero->getPos().getDistance(enemy->getPos());
                if(dis < enemy->getAttackRange())
                {
                    enemy->attack();
                }
                else
                {
                    enemy->changeState(GSprite::State::ATTACKEND);
                }
            }
        }
    }
}

void GGameScene::updateBullet(float dt)
{
    for(int i=0;i<bullets.size();i++)
    {
        GBulletSprite* bullet = bullets.at(i);
        if(bullet->state == GBulletSprite::State::DIE)
        {
            bullet->die();
            bullets.erase(bullets.begin() + i);
            break;
        }
    }

    for(int i=0;i<enemy_bullets.size();i++)
    {
        GBulletSprite* bullet = enemy_bullets.at(i);
        if(bullet->state == GBulletSprite::State::DIE)
        {
            bullet->die();
            enemy_bullets.erase(enemy_bullets.begin() + i);
            break;
        }
    }
    for(int i=0;i<bullets.size();i++)
    {
        GBulletSprite* bullet = bullets.at(i);
        //判断碰撞
        if(bullet->state == GBulletSprite::State::RUN)
        {
            for(int j=0;j<enemys.size();j++)
            {
                GEnemySprite* enemy = enemys.at(j);
                float dis = bullet->getPos().getDistance(enemy->getPos());
                if(enemy->canAttack() && dis < enemy->getContentSize().width/2)
                {
                    bullet->changeState(GBulletSprite::State::DIE);
                    enemy->hurt(bullet);
                }
            }
        }
    }
    
    for(int i=0;i<enemy_bullets.size();i++)
    {
        GBulletSprite* bullet = enemy_bullets.at(i);
        //判断碰撞
        if(bullet->state == GBulletSprite::State::RUN)
        {
            float dis = bullet->getPos().getDistance(hero->getPos());
            if(hero->canAttack() && dis < hero->getContentSize().width/2)
            {
                bullet->changeState(GBulletSprite::State::DIE);
                hero->hurt(bullet);
            }
        }
        
    }
}

void GGameScene::updateDrop(float dt)
{
    for(int i=0;i<drops.size();i++)
    {
        GDropSprite* drop = drops.at(i);
        if(!drop->isDie)
        {
            float dis = drop->getPosition().getDistance(hero->getPos());
            if(dis < drop->getContentSize().width + hero->getContentSize().width)
            {
                drop->isDie = true;
                drop->die(hero->getPos());
                drops.erase(drops.begin()+i);
                coin++;
                updateUI();
                break;
            }
        }
    }
}

void GGameScene::updateUI()
{
    char c[7];
    sprintf(c, "%d",coin);
    t_coin->setString(_T("game_1")+c);
    
    sprintf(c, "%d",(int)time);
    t_time->setString(_T("game_2")+c);
    if((int)time == 0)
    {
        this->unschedule(SEL_SCHEDULE(&GGameScene::update));
        this->runAction(Sequence::create(DelayTime::create(1),
                                         CallFunc::create(CC_CALLBACK_0(GGameScene::end, this,true)),
                                         NULL));
    }
}

void GGameScene::end(bool isSuccess)
{
    hero->clearAllAction();
    for(int i=0;i<enemys.size();i++)
    {
        GEnemySprite* enemy = enemys.at(i);
        enemy->clearAllAction();
    }
    GCache::setCoin(GCache::getCoin() + coin);
    GUIGameOver* over = GUIGameOver::create();
    if(isSuccess)
    {
        over->success();
        GCache::setCurrLevel(GCache::getInstance()->getGameLevel()+1);
    }
    else
    {
        over->fail();
    }
    uiLayer->addChild(over);
}

void GGameScene::rockHandler(cocos2d::Vec2 &dir,float dt,const char *data)
{
    //更新自己方向
    if(data == std::string("move"))
    {
        hero->run(dir);
    }
    else
    {
//        hero->stopRun();
    }
}



void GGameScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    Button* btn = (Button*)pSender;
    std::string name = btn->getName();
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            GTools::playSound(SOUND_BUTTON);
          break;
        case Widget::TouchEventType::MOVED:
            break;
        case Widget::TouchEventType::ENDED:
            if(name == "pause")
            {
                btn->loadTextures("play.png", "play.png");
                btn->setName("play");
                Director::getInstance()->pause();
            }
            else if(name == "play")
            {
                btn->loadTextures("pause.png", "pause.png");
                btn->setName("pause");
                Director::getInstance()->resume();
            }
            else if(name == "home")
            {
                if(Director::getInstance()->isPaused())
                    Director::getInstance()->resume();
                hero->clearAllAction();
                for(int i=0;i<enemys.size();i++)
                {
                    GEnemySprite* enemy = enemys.at(i);
                    enemy->clearAllAction();
                }
                
                this->unschedule(SEL_SCHEDULE(&GGameScene::update));
                auto t = TransitionFade::create(1, GHomeScene::create(), Color3B::BLACK);
                Director::getInstance()->replaceScene(t);
            }
            else if(name == "sound")
            {
                GCache::setMusic(!GCache::isMusic());
                if(GCache::isMusic())
                {
                    btn->loadTextures("sound.png", "sound.png");
                }
                else
                {
                    btn->loadTextures("sound_close.png", "sound_close.png");
                }
            }
           
            break;
            
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
}
