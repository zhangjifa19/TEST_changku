
//
//  GameLayer.h
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#ifndef __zixuanxiangmu__GameLayer__
#define __zixuanxiangmu__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
//#include "Box2D/Box2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Gun.h"
#include "Bullet.h"
#include "Monsters.h"
#include "Ben_file.h"
#include "PauseLayer.h"

USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace timeline;
using namespace std;

class GameLayer:public LayerColor,public PauseDelegate
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    void sureClicked();
    
    void setPhyWorld(PhysicsWorld* world){
        m_world = world;
        }
    
public:
    void addMenu(Ref * f );
    void addWorldEdges();
    void addBullet(Point p);
    void addGangti();
    void loadLayer();
    void touchStart();
    void firstAddMonsters();
    void addMonsters(Item_type t);
    
    void checkCollision(float f);
    bool isCollision(Bullet* bullet,Monsters* monster);
    
    
public:
    virtual void onEnter();
    
    virtual void onExit();
public:
    //解决穿透
    void updateStart(float dt);
    void update(float dt);
    void test();
    
public:
    //biaoqian
    Label * current_score;
    
private:
    PhysicsWorld* m_world;//刚体物理世界
    Node* mainScene;//导入的场景
    ActionTimeline* action;//cocos的时间线
    Gun* gun;
    Monsters* Gebulin;
    float dis_x;//枪的坐标
    float dis_y;
    int  monster_type;//怪物的类型
    int monster_num;//怪物的数量
    int bullets_num;//子弹的数量
    
    
    int fenshu_monster;//当前打怪得分
//    int monsterMask;
    Size visibleSize;
    
    Vector<Monsters*> gebulinVector;
    Vector<Bullet*> bulletVector;
    
    //存取数据
    vector<Data1* > vec;
};


#endif /* defined(__zixuanxiangmu__GameLayer__) */
