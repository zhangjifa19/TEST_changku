//
//  Bullet.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/8.
//
//

#include "Bullet.h"
//Bullet::Bullet()
//{
//    Sprite::initWithFile("CloseNormal.png");
//    hp = 3;
//}
//void Bullet::createBullet(Point p)
//{
//    this->setPosition(p);
//}
//void Bullet::setPhysicBody(b2Body * body)
//{
//    m_pBody = body;
//}
bool Bullet::init()
{
    this->initWithFile("ball.png");
    this->setScale(0.5);
    auto body= PhysicsBody::createCircle(this->getContentSize().width/4);
    body->setDynamic(true);
    body->setMass(0);
    body->getShape(0)->setFriction(0);
    body->getShape(0)->setRestitution(1);
    body->setGravityEnable(false);
    this->setPhysicsBody(body);
    this->getPhysicsBody()->setGroup(-1);
    hp=3;
    return true;
}