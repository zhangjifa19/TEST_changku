#include "HelloWorldScene.h"


USING_NS_CC;
#define ballMask 00100
#define gebulin1Mask 00001
#define gebulin2Mask 00010
#define gebulin3Mask 00020

HelloWorld::~HelloWorld()
{
    bullet->release();
    monster->release();
}
Scene* HelloWorld::createScene()
{
    Director::getInstance();

    //创建物理世界
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,-10));
    scene->getPhysicsWorld()->step(1/180);
    auto layer = HelloWorld::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    //设置世界边界
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(body);
    
    scene->addChild(edgeNode);
    
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    bulletArray1 = __Array::create();
    bulletArray1->retain();
    MonstersArray2 = __Array::create();
    MonstersArray2->retain();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    
    auto hero = Sprite::create("hero.png");
    hero->setPosition(Vec2(160,100));
    this->addChild(hero,1);
    Sprite1 = Sprite::create("qiangshou.png");
    Sprite1->setPosition(Vec2(200,120));
    Sprite1->setAnchorPoint(Vec2(0.5,0.8));
    Sprite1->setRotation(-90);
    this->addChild(Sprite1,1);
    this->schedule(schedule_selector(HelloWorld::getRotation),3);//开启了时间调度
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch *pTouch,Event *pEvent){
        return true;
    };
    touchListener->onTouchMoved = [&](Touch *pTouch,Event *pEvent){
        auto p = Sprite1->getPosition();
        auto start = pTouch->getLocation();
        auto Al=atan2f((start.x-p.x),(start.y-p.y));//huduzhi
        float ro= Al/3.14*180;
        Sprite1->setRotation(ro+180);
        
    };
    touchListener->onTouchEnded = [this](Touch *pTouch, Event *pEvent){
        auto p = Sprite1->getPosition();
        auto start = pTouch->getLocation();
        auto Al=atan2f((start.x-p.x),(start.y-p.y));//huduzhi
        float ro= Al/3.14*180;
        Sprite1->setRotation(ro+180);
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册监听事件
    EventListenerTouchOneByOne* one = EventListenerTouchOneByOne::create();
    one->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    one->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    one->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(one,this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin,this);
    contactListener->onContactSeperate = [this](PhysicsContact& contact){
        auto node1 = contact.getShapeA()->getBody()->getNode();
        auto node2 = contact.getShapeB()->getBody()->getNode();
        if (node1->getTag()==15) {
             node1->removeFromParent();
             node2->removeFromParent();
        }
        log("seprated");
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    //获得csb动画
    mainScene = CSLoader::createNode("LevelScene01.csb");
    mainScene->setPosition(Vec2(0,0));
    this->addChild(mainScene);
    
    action = CSLoader::createTimeline("LevelScene01.csb");
    action->gotoFrameAndPlay(0,175,true);
    mainScene->runAction(action);
    
    getUiButton();
    for (int i =0; i<3; i++) {
        int x=arc4random()*10;
        x %=900;
        x = fabsf(x);
        int y=arc4random()*10;
        y %=600;
        y = fabsf(y);
//        char temp[50];
//        sprintf(temp,"Item_gebulin%d",i+1);
//        log("x= %d ,y= %d",x,y);
//        log("%s",temp);
//        __String * temp1 = __String::create(temp);
        switch (i) {
            case 0:
                monster = new Monsters(Item_gebulin1);
                break;
            case 1:
                monster = new Monsters(Item_gebulin2);
                break;
            case 2:
                monster = new Monsters(Item_gebulin3);
                break;
            default:
                break;
        }
        monster->setPosition(Point(x,y));
        monster->setMonsterPosition(3, Vec2(visibleSize.width/2,visibleSize.height/2), Vec2(10,visibleSize.height/2));
        MonstersArray2->addObject(monster);
        addChild(monster);
    }

   
    return true;
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
    log("began");
    auto node1=contact.getShapeA()->getBody();
    auto node2=contact.getShapeB()->getBody();
    switch (node1->getContactTestBitmask()|node2->getContactTestBitmask()) {
        case ballMask|gebulin1Mask:
            log("gebuling1 && ball");
            break;
        case ballMask|gebulin2Mask:
            log("gebuling2 && ball");
            break;
        case ballMask|gebulin3Mask:
            log("gebuling3 && ball");
            break;
            
        default:
            break;
    }
    return false;
}
void HelloWorld::getUiButton()//给障碍物设置刚体
{
    for (int i = 1;i<10;i++)
    {
        if (i<10) {
        __String *str = __String::createWithFormat("LevelBeijing_01_0%d",i);
        auto item = mainScene->getChildByName<Sprite*>(str->getCString());
        auto body = PhysicsBody::createBox(item->getContentSize());
        body->setDynamic(false);//设置静止
        item->setPhysicsBody(body);
        item->getPhysicsBody()->getShape(0)->setRestitution(1);
        item->getPhysicsBody()->getShape(0)->setFriction(0);
        }
        else{
            __String * str = __String::createWithFormat("LevelBeijing_01_%d",i);
            auto item = mainScene->getChildByName<Sprite*>(str->getCString());
//            auto body = PhysicsBody::createCircle(item->getContentSize().width/4);
            Size BoxSize=Size::Size(item->getContentSize().width/4,item->getContentSize().height/5*3);
            auto body = PhysicsBody::createEdgeBox(BoxSize);
            body->setMass(0);
            char temp[50];
            for (int j=1; j<4; j++) {
                sprintf(temp,"gebulin%dMask",j);
            }
            int t=__String::createWithFormat("%s",temp)->intValue();
            body->setContactTestBitmask(t);
            body->getShape(0)->setRestitution(1);
            body->getShape(0)->setDensity(0);//密度
            body->getShape(0)->setFriction(0);
            
//            body->setResting(1);//设置睡眠模式
            item->setPhysicsBody(body);
            Vec2 s = item->getPosition();
            log("=====x %f===y %f===",s.x,s.y);
        }
        
    }

}

void HelloWorld::getRotation(float t)
{
//    int b;
//    log("2222222%ld",bulletArray1->count());
//    for (int i =0 ; i<bulletArray1->count(); i++) {
//        bullet = (Bullet*)bulletArray1->getObjectAtIndex(i);
//        bullet->removeFromParent();
//        if (bullet->hp <=0) {
//            bullet->removeFromParent();
//            log("hhhhhhhhhh");
//            b=i;
//        }else{
//            (bullet->hp)--;
//        }
//    }
//    log("%d",b);
    if (bulletArray1->count()>0) {
        bullet = (Bullet*)bulletArray1->getObjectAtIndex(0);
        bullet->removeFromParent();
        bulletArray1->removeObjectAtIndex(0);
    }
    
}

void HelloWorld::addNewSpriteAtPosition(Point p)
{
//    bullet = new Bullet();
//    auto body = PhysicsBody::createCircle(bullet->getContentSize().width/4);
//    bullet->setScale(0.5);
//    body->setCategoryBitmask(1);
//    body->setCollisionBitmask(1);
//    body->setContactTestBitmask(ballMask);
//    body->getShape(0)->setFriction(0);
//    body->getShape(0)->setRestitution(1);
//    bullet->setPhysicsBody(body);
//    bullet->getPhysicsBody()->setGravityEnable(false);
//    bullet->setPosition(Vec2(200,120));
    
    auto bullet = Bullet::create();
    
    bullet->setScale(0.3);
    bullet->setPosition(p);
    p.x -=200;p.y -=120;
    
    float tt= sqrt(p.x*p.x+p.y*p.y);
    
    auto body = bullet->getPhysicsBody();
    body->setVelocity(Vec2(p.x,p.y)*500/tt);//tianjiali
    this->addChild(bullet);
    
    bulletArray1->addObject(bullet);
}
bool HelloWorld::onTouchBegan(Touch *touch,Event *unused_event)
{
    
    return true;
}
void HelloWorld::onTouchMoved(Touch* touch,Event *unused_event)
{
//    log("yyyyyyyy");
    
}
void HelloWorld::onTouchEnded(Touch* touch ,Event * unused_event)
{
    addNewSpriteAtPosition(touch->getLocation());//添加子弹
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
