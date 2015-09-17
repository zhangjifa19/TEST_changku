//
//  GameLayer.cpp
//  zixuanxiangmu
//
//  Created by student on 15/9/10.
//
//

#include "GameLayer.h"
#include "MainGameData.h"
#include "MainLayer.h"


#define BULL_MASK   0x0001
#define WALL_MASK   0x0002
#define OBSTRUCTION_MASK 0x0004

int Level =0;//关卡

Scene * GameLayer::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameLayer::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    layer->test();//调用函数，帧频
    scene->getPhysicsWorld()->setAutoStep(false);
    return scene;
}

void GameLayer::test()
{
    schedule(schedule_selector(GameLayer::updateStart),0.005f);
}

bool GameLayer::init(){
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    
    gun = Gun::create();
    gun->setPosition(Vec2(150,visibleSize.height/2-100));
    addChild(gun,1);
    
    fenshu_monster=0;
    loadLayer();
    addWorldEdges();
    touchStart();
    firstAddMonsters();
    
    this->schedule(schedule_selector(GameLayer::checkCollision),0.1);//启动检测碰撞的函数
    return true;
}
void GameLayer::loadLayer(){
    //读取数据
    bendi = new Ben_file<Data1>();//模版
    vec.clear();
    vec = bendi->createwithxmlfile("data_gameLayer.xml");
    Level = vec[0]->_number;
    
    
    
    //获得csb动画
    char temp[50];
    sprintf(temp,"LevelScene0%d.csb",Level+1);
    mainScene = CSLoader::createNode(temp);
    mainScene->setPosition(Vec2(0,0));
    this->addChild(mainScene);
    
    action = CSLoader::createTimeline(temp);
    action->gotoFrameAndPlay(0,175,true);
    mainScene->runAction(action);
    monster_num= MONSTERS_NUM[Level];//初始化怪物和子弹的数量
    bullets_num = BULLETS_NUM[Level];
    
    //显示标签，得分
    auto label = Label::createWithSystemFont("Score:", "arial.ttf", 24);
    label->setPosition(Vec2(50,visibleSize.height-30));
    __String * fenshu = __String::createWithFormat("%d",vec[Level]->_score);
    auto score= Label::createWithSystemFont(fenshu->getCString(), "arial.ttf", 24);
    score->setPosition(Vec2(100,visibleSize.height-30));
    addChild(label,1);
    addChild(score,1);
    //显示标签，得分
    auto label1 = Label::createWithSystemFont("Level:", "Marker Felt.ttf", 24);
    label1->setPosition(Vec2(50,visibleSize.height-60));
    __String * guanshu = __String::createWithFormat("%d",vec[Level]->_number+1);
    auto level1= Label::createWithSystemFont(guanshu->getCString(), "Marker Felt.ttf", 24);
    level1->setPosition(Vec2(100,visibleSize.height-60));
    addChild(label1,1);
    addChild(level1,1);
    //显示标签，得分
    auto label2 = Label::createWithSystemFont("Level:", "Marker Felt.ttf", 24);
    label2->setPosition(Vec2(50,visibleSize.height-100));
    __String * cu= __String::createWithFormat("%d",0);//start直接为 0
    current_score = Label::createWithSystemFont(cu->getCString(), "Marker Felt.ttf", 24);
    current_score->setPosition(Vec2(100,visibleSize.height-100));
    addChild(label2,1);
    addChild(current_score,1);
    
    //暂停按钮
    auto menu = MenuItemImage::create("newPause_Normal.png","newPause_Normal.png");
    auto menu1 = MenuItemImage::create("newPause_Select.png","newPause_Select.png");
    auto toggle = MenuItemToggle::create();
    toggle->addSubItem(menu);
    toggle->addSubItem(menu1);
    toggle->setSelectedIndex(0);
    toggle->setPosition(Vec2(visibleSize.width-40,40));
    toggle->setCallback(CC_CALLBACK_1(GameLayer::addMenu,this));
    auto menu2 = Menu::create(toggle,nullptr);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2);
    
    
    addGangti();
    
}

void GameLayer::addMenu(Ref * f){
    PauseLayer * pause = PauseLayer::create();//初始化层
    this->addChild(pause,1);
    pause->setDelegate(this);//设置代理
    //暂停游戏
    Director::getInstance()->pause();
    
    //触摸吞噬，创建一个监听器
    auto l = EventListenerTouchOneByOne::create();
    l->setSwallowTouches(true);
    l->onTouchBegan=[&](Touch*,Event*){
//        pause->setSwallowsTouches(true);//这是错误的写法，监听器进行吞噬触摸
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(l, pause);
    
}

void GameLayer::addGangti(){
    int Level_Obstructs_num =0;
    switch (Level) {
        case 0:
        {
            Level_Obstructs_num =10;
            for (int i = 1;i<Level_Obstructs_num;i++)
            {
                if (i<10) {
                    __String *str = __String::createWithFormat("LevelBeijing_01_0%d",i);
                    auto item = mainScene->getChildByName<Sprite*>(str->getCString());
                    auto body = PhysicsBody::createBox(item->getContentSize());
                    body->setDynamic(false);//设置静止
                    item->setPhysicsBody(body);
                    item->getPhysicsBody()->getShape(0)->setContactTestBitmask(OBSTRUCTION_MASK);
                    item->getPhysicsBody()->getShape(0)->setRestitution(1.2);
                    item->getPhysicsBody()->getShape(0)->setFriction(0);
                }
                else{
                    __String * str = __String::createWithFormat("LevelBeijing_01_%d",i);
                    auto item = mainScene->getChildByName<Sprite*>(str->getCString());
                    //            char temp[50];
                    //            for (int j=1; j<4; j++) {
                    //                sprintf(temp,"gebulin%dMask",j);
                    //            }
                    //            int t=__String::createWithFormat("%s",temp)->intValue();
                    //            body->setContactTestBitmask(t);
                  
                    Vec2 s = item->getPosition();
                    log("=====x %f===y %f===",s.x,s.y);
                    item->removeFromParent();
                }
                
            }
        }
            break;
            
        case 1:
        {
            Level_Obstructs_num =10;
            ///////////
            for (int i =1 ; i<Level_Obstructs_num; i++) {
                __String *str = __String::createWithFormat("LevelBeijing_02_0%d",i);
                auto item = mainScene->getChildByName<Sprite*>(str->getCString());
                PhysicsBody *body;
                if ((i==1)|(i<6&&i>3)) {
                    
                    body = PhysicsBody::createBox(item->getContentSize());
                }
                else if(i==2){
                    body = PhysicsBody::createBox(Size(item->getContentSize().width*1.5,item->getContentSize().height));
                }
                else if(i==3){
                    body = PhysicsBody::createBox(Size(item->getContentSize().width*2,item->getContentSize().height));
                }
                else{
                    body = PhysicsBody::createCircle(item->getContentSize().width/2);
                }
                body->setDynamic(false);//设置静止
                item->setPhysicsBody(body);
                item->getPhysicsBody()->getShape(0)->setContactTestBitmask(OBSTRUCTION_MASK);
                item->getPhysicsBody()->getShape(0)->setRestitution(1.2);
                item->getPhysicsBody()->getShape(0)->setFriction(0);
            }
            /////////////
        }
            break;
            
        case 2:
        {
//            break;
            Level_Obstructs_num =15;
            for (int i =1 ; i<Level_Obstructs_num; i++) {
                ///////////////////
                Sprite* item;
                PhysicsBody *body;
                if (i<10) {
                    __String *str = __String::createWithFormat("LevelBeijing_03_0%d",i);
                    item = mainScene->getChildByName<Sprite*>(str->getCString());
                    body = PhysicsBody::createBox(item->getContentSize());
                }
                else if(i==10)
                {
                    __String *str = __String::createWithFormat("LevelBeijing_03_%d",i);
                    item = mainScene->getChildByName<Sprite*>(str->getCString());
                    body = PhysicsBody::createBox(Size(item->getContentSize().width/2,item->getContentSize().height));
                }
                else if(i==11|i==12)
                {
                    __String *str = __String::createWithFormat("LevelBeijing_03_%d",i);
                    item = mainScene->getChildByName<Sprite*>(str->getCString());
//                    item->setRotation(23);//设置旋转角度,添加了刚体，就没有旋转的角度了?????
                    body = PhysicsBody::createBox(item->getContentSize());
                }
                else{
                    __String *str = __String::createWithFormat("LevelBeijing_03_%d",i);
                    item = mainScene->getChildByName<Sprite*>(str->getCString());
                    body = PhysicsBody::createBox(item->getContentSize());

                }
                item->setRotation(23);
                
                body->setDynamic(false);//设置静止
                item->setPhysicsBody(body);
                item->getPhysicsBody()->getShape(0)->setContactTestBitmask(OBSTRUCTION_MASK);
                item->getPhysicsBody()->getShape(0)->setRestitution(1.2);
                item->getPhysicsBody()->getShape(0)->setFriction(0);
               
            }
            ////////////
            break;
        }
        default:
            break;
    }
   
}
void GameLayer::addWorldEdges(){
    //添加世界边框
//    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
//    body->getShape(0)->setFriction(0);
//    body->getShape(0)->setRestitution(1);
//    body->getShape(0)->setContactTestBitmask(WALL_MASK);
//    auto node = Node::create();
//    node->setPhysicsBody(body);
//    node->setPosition(visibleSize/2);
//    addChild(node);
    
    for (int i=0 ; i<4; i++) {
        PhysicsBody *body;
        Node * node=Node::create();
    switch (i) {
        case 0:
            node->setContentSize(Size(20,visibleSize.height));
            node->setPosition(Vec2(0,visibleSize.height/2));
            break;
        case 1:
            node->setContentSize(Size(visibleSize.width,20));
            node->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
            break;
        case 2:
            node->setContentSize(Size(20,visibleSize.height));
            node->setPosition(Vec2(visibleSize.width,visibleSize.height/2));
            break;
        case 3:
            node->setContentSize(Size(visibleSize.width,20));
            node->setPosition(Vec2(visibleSize.width/2,0));
            break;
            
        default:
            break;
    }
        body=PhysicsBody::createBox(node->getContentSize());
        body->setDynamic(false);
        node->setPhysicsBody(body);
        body->getShape(0)->setFriction(0);
        body->getShape(0)->setRestitution(1);
        body->getShape(0)->setContactTestBitmask(WALL_MASK);
        
        addChild(node);
    }
    
}

void GameLayer::touchStart(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan =[&](Touch* t,Event* e){
        Vec2 lo = t->getLocation();
        int GunX= gun->getPositionX();
        int GunY= gun->getPositionY();
        dis_x = lo.x-GunX;
        dis_y = lo.y-GunY;
        float atan = atan2f(dis_x,dis_y)*180/3.14;
        if (atan>=-10 && atan<=250) {
            gun->setRotation(atan);
        }
        return true;
    };
    listener->onTouchMoved = [&](Touch* t,Event* e){
        Vec2 lo= t->getLocation();
        int GunX= gun->getPositionX();
        int GunY= gun->getPositionY();
        dis_x = lo.x-GunX;
        dis_y = lo.y-GunY;
        float atan = atan2f(dis_x,dis_y)*180/3.14;
        if (atan>=-10 && atan<=250) {
            gun->setRotation(atan);
        }
    };
    listener->onTouchEnded = [&](Touch* t,Event * e){
        this->addBullet(Vec2(gun->getPositionX(),gun->getPositionY()));
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void GameLayer::addBullet(Point p){
    log("还有几发子弹＝ %d",bullets_num);
    if (bullets_num>0&&bulletVector.size()==0)
    {//子弹的剩余数量,//一次，只能一发指弹
        auto bullet = Bullet::create();
        bullet->setTag(100);//子弹的Tag值为100
        bullet->setScale(0.3);
        bullet->setPosition(p);
        this->addChild(bullet);
        float tt = sqrtf(dis_x*dis_x+dis_y*dis_y);
        auto body = bullet->getPhysicsBody();
        body->setVelocity(Vec2(dis_x, dis_y)/tt*2500);
//    body->applyForce(Vec2(dis_x, dis_y)/tt*100);//瞬间力
//    body->applyImpulse(Vec2(dis_x, dis_y)/tt*100);
        bullet->getPhysicsBody()->setContactTestBitmask(BULL_MASK);//设置检测碰撞类型
        bulletVector.pushBack(bullet);
    }
    else if(bulletVector.size())
    {
        log("bullet");
    }
    else
    {
        MessageBox("游戏结束",  "标题");
        auto menulayer= MainLayer::createScene();
        Director::getInstance()->replaceScene(menulayer);
    }
    bullets_num--;
    log("子弹 ＝ %zd",bulletVector.size());
}

void GameLayer::firstAddMonsters(){
    //    MONSTERS_NUM[1];
    monster_num -=MONSTERS_num[Level];//
    for (int i =0 ; i<MONSTERS_num[Level]; i++) {
        switch (i) {
            case 0:
                log("添加怪物了1");
                Gebulin=Monsters::getInstance(Item_gebulin1);
                Gebulin->setPosition(Vec2(520,555));
                Gebulin->setMonsterPosition(3, Vec2(520, 555), Vec2(800,555));
                break;
            case 1:
                log("添加怪物了2");
                Gebulin=Monsters::getInstance(Item_gebulin2);
                Gebulin->setPosition(Vec2(405.08, 335));
                Gebulin->setMonsterPosition(3, Vec2(405.08, 335), Vec2(650,335));
                break;
            case 2:
                log("添加怪物了3");
                Gebulin=Monsters::getInstance(Item_gebulin3);
                Gebulin->setPosition(Vec2(800, 193));
                Gebulin->setMonsterPosition(1, Vec2(800, 193), Vec2(945,193));
                break;
            case 3:
                log("添加怪物了4");
                Gebulin=Monsters::getInstance(Item_gebulin3);
                Gebulin->setPosition(Vec2(800, 230));
                Gebulin->setMonsterPosition(1, Vec2(800, 230), Vec2(945,230));
                break;
            case 4:
                log("添加怪物了5");
                Gebulin=Monsters::getInstance(Item_gebulin3);
                Gebulin->setPosition(Vec2(50, 900));
                Gebulin->setMonsterPosition(1, Vec2(50, 900), Vec2(300,900));
                break;
            case 5:
                log("添加怪物了6");
                Gebulin=Monsters::getInstance(Item_gebulin3);
                Gebulin->setPosition(Vec2(600, 600));
                Gebulin->setMonsterPosition(1, Vec2(600, 600), Vec2(900,600));
                break;
                
            default:
                break;
        }
        this->addChild(Gebulin,1);
        gebulinVector.pushBack(Gebulin);
        
    }
}
void GameLayer::addMonsters(Item_type t)
{
    if (MONSTERS_NUM[Level] && (gebulinVector.size()<MONSTERS_num[Level])) {
        switch (monster_type) {
            case 1:
                log("添加怪物了1");
                Gebulin=Monsters::getInstance(Item_gebulin1);
                Gebulin->setPosition(Vec2(520,555));
                Gebulin->setMonsterPosition(3, Vec2(520, 555), Vec2(800,555));
                break;
            case 2:
                log("添加怪物了2");
                Gebulin=Monsters::getInstance(Item_gebulin2);
                Gebulin->setPosition(Vec2(405.08, 335));
                Gebulin->setMonsterPosition(3, Vec2(405.08, 335), Vec2(650,335));
                break;
            case 3:
                log("添加怪物了3");
                //                Gebulin = new Monsters(Item_gebulin3);
                Gebulin=Monsters::getInstance(Item_gebulin3);
                Gebulin->setPosition(Vec2(800, 193));
                Gebulin->setMonsterPosition(1, Vec2(800, 193), Vec2(945,193));
                break;
                
            default:
                break;
        }
        this->addChild(Gebulin,1);
        gebulinVector.pushBack(Gebulin);
    }
    
    //判断游戏是否结束
    if ((gebulinVector.size() == 0)&& (monster_num == 0)){
        PauseLayer * pause = PauseLayer::create();//初始化层
        this->addChild(pause);
        pause->setDelegate(this);//设置代理
        //暂停游戏
        Director::getInstance()->pause();
        auto l = EventListenerTouchOneByOne::create();
        l->setSwallowTouches(true);
        l->onTouchBegan = [&](Touch*,Event* ){
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(l, pause);
    }
}

void GameLayer::update(float dt)
{
        for (int i=0;i<3;i++){///????????
    m_world->step(1/200.0f);
        }
    if (bulletVector.size()>0){
        Vector<Bullet*>::iterator it;
        
        for (it =bulletVector.begin();it!=bulletVector.end();it++)
        {
            int x= (*it)->getPosition().x;
            int y= (*it)->getPosition().y;
            if (x<0|x>visibleSize.width|y<0|y>visibleSize.height) {
                log("移除子弹 剩余数＝ %zd",bulletVector.size());
                (*it)->removeFromParent();
                bulletVector.erase(it);
                break;
            }
        }
    }
    
}
void GameLayer::updateStart(float dt){
    scheduleUpdate();//设置优先级为0
}
//这个是的碰撞的检测，然后实现的操作
void GameLayer::checkCollision(float f){
    Vector<Monsters*>::iterator it;
    Vector<Bullet*>::iterator it1;
    for (it1 = bulletVector.begin(); it1!= bulletVector.end(); it1++) {
        auto  bullet=*it1;
        for (it = gebulinVector.begin() ; it!=gebulinVector.end(); it++) {
            ////////碰到怪物后移除它，并且加上相应的得分
            if (isCollision(bullet, (*it))) {
                (*it)->removeFromParent();
                //添加特效
                auto p = ParticleFlower::create();
                addChild(p);
                p->setPosition((*it)->getPosition());
                p->setDuration(1.0);
                p->setAutoRemoveOnFinish(true);
                monster_type=(*it)->getTypee();
                //修改当前得分
                fenshu_monster= (*it)->score+fenshu_monster;
                current_score->setString(__String::createWithFormat("%d",fenshu_monster)->getCString());
                //判断是否超纪录
                if (fenshu_monster>vec[Level]->_score) {
                    bendi->SaveXmlFile(Level, fenshu_monster);
                }
                gebulinVector.eraseObject(*it);
                log("怪物数==%zd",gebulinVector.size());
                
                if (monster_num>0) {
                    monster_num--;
                    log("monster_type==%d",monster_type);
                    switch (monster_type) {
                        case 1:
                        {auto func=CallFunc::create(CC_CALLBACK_0( GameLayer::addMonsters,this,Item_gebulin1));
                            auto seq = Sequence::create(DelayTime::create(3),func, NULL);
                            this->runAction(seq);}
                            
                            break;
                            
                        case 2:
                        {auto func=CallFunc::create(CC_CALLBACK_0( GameLayer::addMonsters,this,Item_gebulin2));
                            auto seq = Sequence::create(DelayTime::create(3),func, NULL);
                            this->runAction(seq);}
                            break;
                            
                        case 3:
                        {auto func=CallFunc::create(CC_CALLBACK_0( GameLayer::addMonsters,this,Item_gebulin3));
                            auto seq = Sequence::create(DelayTime::create(3),func, NULL);
                            this->runAction(seq);}
                            break;
                            
                        default:
                            break;
                    }
                    ////////////
                }
                break;
            }
            /////////
        }
    }
}
//子弹跟精灵的碰撞，但是这歌没有刚体，是用矩形边框检测的,检测的方法
bool GameLayer::isCollision(Bullet* bullet,Monsters* monster){
    auto rect1 = bullet->getBoundingBox();
    auto rect2 = monster->getBoundingBox();
    
    return !(rect1.getMaxX() < rect2.getMinX()+35 ||
            rect2.getMaxX()-35 <  rect1.getMinX() ||
            rect1.getMaxY() < rect2.getMinY()+30 ||
            rect2.getMaxY()-30 <rect1.getMinY());
    
}
//注册碰撞的监听事件，监听刚体的碰撞的事件
void GameLayer::onEnter(){
    Layer::onEnter();
    auto contlistener = EventListenerPhysicsContact::create();
    contlistener->onContactBegin = [&](PhysicsContact& contact){
        switch (contact.getShapeA()->getBody()->getContactTestBitmask()|contact.getShapeB()->getContactTestBitmask())
        {
            case BULL_MASK|WALL_MASK:
            {
                auto A = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
                auto B = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
                if ( A==nullptr &&B==nullptr ) {
                    return false;
                }
                if (A==nullptr) {
                    A=B;
                }
                else{}
                int a = A->getHp();
                A->setHp(--a);
                if (A->getHp()==0) {
                    log("子弹的数量 %zd",bulletVector.size());
                    A->removeFromParent();
                    bulletVector.eraseObject(A);
                }
//                log("子弹碰到墙壁 ");
            }
                break;
                
                
            case BULL_MASK|OBSTRUCTION_MASK:
            {
                auto A = dynamic_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
                auto B = dynamic_cast<Bullet*>(contact.getShapeB()->getBody()->getNode());
                if ( A==nullptr &&B==nullptr ) {
                    return false;
                }
                if (A==nullptr) {
                    A=B;
                }
                else{}
                int a = A->getHp();
                A->setHp(--a);
                if (A->getHp()==0) {
                    log("子弹的数量 %zd",bulletVector.size());
                    A->removeFromParent();
                    bulletVector.eraseObject(A);
                }
//                log("子弹碰到障碍物 ");
            }
                break;
                
            default:
                break;
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contlistener, this);
}
void GameLayer::sureClicked()
{
    log("Clicked!!!代理方法");
    //恢复游戏
    Director::getInstance()->resume();
    auto scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(scene);
    
}

void GameLayer::onExit(){
    Layer::onExit();
    
    _eventDispatcher->removeEventListenersForTarget(this);
}