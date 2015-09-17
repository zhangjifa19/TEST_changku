//
//  Monsters.h
//  zixuanxiangmu
//
//  Created by student on 15/9/9.
//
//

#ifndef __zixuanxiangmu__Monsters__
#define __zixuanxiangmu__Monsters__

#include <iostream>
#include "cocos2d.h"

typedef enum
{
    Item_gebulin1 = 0,
    Item_gebulin2 ,
    Item_gebulin3
}Item_type;
//运用单例模式
class Monsters:public cocos2d::Sprite
{
public:
    int score;
    bool isflag;
    static Monsters* getInstance(Item_type spriteType);
    static void purgeInstance();
    Monsters(Item_type sprite);

    
    void setMonsterPosition(int t,cocos2d::Vec2 p1,cocos2d::Vec2 p2);
    void change();
private:
    cocos2d::Vec2 p;
    
    CC_SYNTHESIZE(int, typee, Typee);
//    CC_SYNTHESIZE(int, score, SCORE);//可以不用这个，当然也可以用这个

};

#endif /* defined(__zixuanxiangmu__Monsters__) */
