//
//  Bullet.h
//  zixuanxiangmu
//
//  Created by student on 15/9/8.
//
//

#ifndef __zixuanxiangmu__Bullet__
#define __zixuanxiangmu__Bullet__

#include <iostream>
#include "cocos2d.h"
//#include "Box2D/Box2D.h"
USING_NS_CC;
class Bullet:public Sprite
{
//public:
//    Bullet();
//    void createBullet(Point p);
//    void setPhysicBody(b2Body *body);
//    int hp;
//private:
//    b2Body * m_pBody;//刚体
public:
    virtual bool init();
    CREATE_FUNC(Bullet);
protected:
    //血量
    CC_SYNTHESIZE(int,hp,Hp);
};


#endif /* defined(__zixuanxiangmu__Bullet__) */
