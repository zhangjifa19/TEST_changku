#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include <iostream>
#include "Bullet.h"
#include "Monsters.h"
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace timeline;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    ~HelloWorld();
    virtual void onEnter();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(HelloWorld);
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
private:
    PhysicsWorld* m_world;
    
    ActionTimeline* action;
    Node* mainScene;
    Bullet* bullet;
    Monsters* monster;
    
public:
    void getUiButton();
    
public:
    void getRotation(float t);
    cocos2d::Sprite * Sprite1;
    
    void addNewSpriteAtPosition(Point p);
    bool onContactBegin(const PhysicsContact& contact);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
public:
    __Array* bulletArray1;
    __Array* MonstersArray2;
};

#endif // __HELLOWORLD_SCENE_H__
