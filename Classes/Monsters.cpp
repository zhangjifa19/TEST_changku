//
//  Monsters.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/9.
//
//

#include "Monsters.h"
#include "cocos2d.h"

using namespace cocos2d;

//#define  name_monsters1   "gebulin1.png"
//#define  name_monsters2   "gebulin2.png"
//#define  name_monsters3   "gebulin3.png"

static Monsters * instance = nullptr;

 Monsters* Monsters::getInstance(Item_type sprite)
{
//    if (instance == nullptr) {//这就是单例模式的意思，有就返回之前创建的
        instance= new Monsters(sprite);
        log("初始化");
//        return instance;
//    }
    return instance;
}
Monsters::Monsters(Item_type sprite)
{
    this->isflag = false;
    p=Director::getInstance()->getVisibleSize();
    
    switch (sprite)
    {
        case Item_gebulin1:
        {
            {
//            this->initWithFile("gebulin1.png");
//            this->score = 10;
//            this->stopAllActions();
//            Vector<SpriteFrame* >vector;
//            typee=1;
//            
//            auto tempDic = __Dictionary::createWithContentsOfFile("gebulin1.plist");
//            auto dic = (__Dictionary*)tempDic->objectForKey("frames");
//            int num = (int)dic->allKeys()->count();
//            log("gebulin  %d张图",num);
//            
//            for (int i=12;i<18; ++i)
//            {
//                SpriteFrame *frame = NULL;
//                frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("gebulin1_%d.png",i)->getCString());
//                
//                vector.pushBack(frame);//??????weishenem 
//            }
//            auto animation = Animation::createWithSpriteFrames(vector,0.2,1);
//            auto plitAnimate = Animate::create(animation);
//            this->runAction(RepeatForever::create(plitAnimate));
            }
            this->initWithFile("gebulin1.png");
            this->score = 10;
            this->stopAllActions();
            Vector<SpriteFrame* >vector;
            typee=1;
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gebulin1.plist");
            for (int i=12;i<18; ++i)
            {
                SpriteFrame *frame = NULL;
                frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("gebulin1_%d.png",i)->getCString());
                vector.pushBack(frame);
            }
            auto animation = Animation::createWithSpriteFrames(vector,0.2,1);
            auto plitAnimate = Animate::create(animation);
            this->runAction(RepeatForever::create(plitAnimate));
            
            break;
        }
        case Item_gebulin2:
        {
            this->initWithFile("gebulin2.png");
            this->score = 15;
            this->stopAllActions();
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gebulin2.plist");
            Vector<SpriteFrame* >vector;
            typee=2;
            
            for (int i=12;i<18; ++i)
            {
                SpriteFrame *frame = NULL;
                frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("gebulin2_%d.png",i)->getCString());
                log("%s",__String::createWithFormat("gebulin2_%d.png",i)->getCString());
                vector.pushBack(frame);
            }
            auto animation = Animation::createWithSpriteFrames(vector,0.2,1);
            auto plitAnimate = Animate::create(animation);
            this->runAction(RepeatForever::create(plitAnimate));
            break;
        }
        case Item_gebulin3:
        {
            this->initWithFile("gebulin3.png");
            this->score = 20;
            this->stopAllActions();
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gebulin3.plist");//导入图片
            Vector<SpriteFrame* >vector;
            typee=3;
            
            for (int i=12;i<18; ++i)
            {
                SpriteFrame *frame = NULL;
                frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat("gebulin3_%d.png",i)->getCString());
                vector.pushBack(frame);
            }
            auto animation = Animation::createWithSpriteFrames(vector,0.2,1);
            auto plitAnimate = Animate::create(animation);
            this->runAction(RepeatForever::create(plitAnimate));
            
            break;
        }
        default:
            break;
    }

}
void Monsters::setMonsterPosition(int t,cocos2d::Vec2 p1, cocos2d::Vec2 p2)
{
   
    this->setPosition(p1);
    auto moveToright = MoveTo::create(t,p2);
    auto moveToleft = MoveTo::create(t,p1);
    auto func = CallFunc::create(CC_CALLBACK_0(Monsters::change,this));
    
    auto seq = Sequence::create(moveToright,DelayTime::create(1),func,moveToleft,func,NULL);
    this->runAction(RepeatForever::create(seq));
}
void Monsters::change(){
    isflag = !isflag;
    if (isflag) {
        this->setFlippedX(true);
    }else{
        this->setFlippedX(false);
    }
    
}

void Monsters::purgeInstance(){//删除
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}