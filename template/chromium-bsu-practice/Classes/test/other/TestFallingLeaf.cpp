/*
ufolr原创，转载请注明：
转载自ufolr的博客 原文连接：http://blog.csdn.net/ufolr/article/details/7624851
*/

#include "TestFallingLeaf.h"
#include <stdlib.h>


USING_NS_CC;

enum {TAG_LEAF1 = 101, TAG_LEAF2};  

CCScene* TestFallingLeaf::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestFallingLeaf *layer = TestFallingLeaf::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestFallingLeaf::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float top = origin.y + visibleSize.height;
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// -----
	// title
	// -------
	CCLabelTTF* title = CCLabelTTF::create();
	title->setString("Test Falling Leaf");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	// init
	CCSprite *spriteLeaf1 = CCSprite::create("test/testFallingLeaf1.jpg");  
	spriteLeaf1->setRotation(30);//旋转角度  
	spriteLeaf1->setAnchorPoint(ccp(0.5, 3));//设置精灵锚点  
	spriteLeaf1->setPosition(ccp(450, 500));//叶子1第一次初始位置  
	spriteLeaf1->setScale(0.5);//设置叶片大小  

	this->addChild(spriteLeaf1,100,TAG_LEAF1);  
	this->playLeafAnim(spriteLeaf1);//调用play函数播实现叶动作  

	CCSprite *spriteLeaf2 = CCSprite::create("test/testFallingLeaf1.jpg");  
	spriteLeaf2->setRotation(50);  
	spriteLeaf2->setAnchorPoint(ccp(0.5, 3));  
	spriteLeaf2->setPosition(ccp(200, 540));  
	spriteLeaf2->setScale(0.5);  

	this->addChild(spriteLeaf2,101,TAG_LEAF2);  
	this->playLeafAnim(spriteLeaf2);  

	return true;  
}

void TestFallingLeaf::playLeafAnim(CCSprite *spriteLeaf)  
{  
	int iTag = spriteLeaf->getTag();  

	CCLog("playtag%d", iTag);  
	float time, roTime;  
	float fAngle1, fAngle2;  
	if (iTag == TAG_LEAF1)  
	{  
		CCLog("tag1");  
		time = 10;//叶子下落的时间  
		roTime = 2.5;//叶子单向摆动一次时间  
		fAngle1 = -80;//叶子逆时针摆动角度  
		fAngle2 = 80;//顺时针摆动角度  
	}  
	else  
	{  
		CCLog("tag2");  
		time = 14;  
		roTime = 3.2;  
		fAngle1 = -100;  
		fAngle2 = 100;  
	}  
	CCLog("rotime%ffAngle1%ffAngle2%f",roTime, fAngle1,fAngle1);  
	//随机生成叶子横向偏移值  
	srand((UINT)GetCurrentTime());  
	int iRandPos = rand() % 250;  
	CCLog("Pianyi%d", iRandPos);  
	//叶子所运动到的位置  
	CCMoveTo *moveTo = CCMoveTo::create(time, ccp(CCDirector::sharedDirector()->getWinSize().width - iRandPos, 30));  
	CCCallFuncN *actDone = CCCallFuncN::create(this, callfuncN_selector(TestFallingLeaf::resetLeafPos));  
	CCFiniteTimeAction *putdown = CCSequence::create(moveTo, actDone, NULL);  
	//叶子旋转动作  
	CCRotateBy *rotaBy1 = CCRotateBy::create(roTime, fAngle1);  
	CCRotateBy *rotaBy2 = CCRotateBy::create(roTime, fAngle2);  

	//叶子翻转动作  
	spriteLeaf->setVertexZ(60);//设置深度抬高60，避免出现使用CCOrbitCamera实现空间翻转时产生错位和遮挡等问题  
	//CCDirector::sharedDirector()->setDepthTest(false);  
	//关闭深度测试同样可以避免上述问题，不过，推荐使用深度设置setVertexZ来正确解决，因为有时你可能需要遮挡的效果，关闭深度测试后将造成遮挡效果的缺失  
	CCOrbitCamera * orbit = CCOrbitCamera::create(8, 1, 0, 0, 360, 45, 0);  
	//让树叶精灵始终执行三维翻转的动作  
	CCRepeat *fz3d = CCRepeat::create(orbit, -1);//无限循环执行叶片翻转的动作  
	//CCRepeatForever *fz3d = CCRepeatForever::actionWithAction(orbit);  
	//由于下面使用CCSpawn同时执行动作，所以不可以使用无限次数类型的动作，而因使用有线次数循环CCRepeat将循环次数设置为-1  

	//用CCEaseInOut包装落叶摆动的动作，让树叶的进入、出现更自然（淡入淡出效果）  
	CCEaseInOut *ease1 = CCEaseInOut::create(rotaBy1, 3);  
	CCEaseInOut *ease2 = CCEaseInOut::create(rotaBy2, 3);  
	//摆动动作合成  
	CCFiniteTimeAction *seq2 = CCSequence::create(ease1, ease2, NULL);//依次执行顺时针、逆时针摆动  
	CCRepeat *baidong = CCRepeat::create(seq2, -1);//摆动合成  

	//动作执行->同时执行所有动作  
	spriteLeaf->runAction(CCSpawn::create(putdown, baidong, fz3d, NULL)); 
	// spriteLeaf->runAction(CCSpawn::create(fz3d, NULL)); 

}

void TestFallingLeaf::resetLeafPos(CCNode* sender)  
{  
	int iTag = int(sender->getTag());//获得被重置叶片的标签  
	int iZoder = int(sender->getZOrder());//获取被重置叶片的z轴值  
	sender->removeFromParentAndCleanup(true);//清除已经落到底点的叶子  

	char sImg[] = "test/testFallingLeaf1.jpg";  
	//_snprintf(sImg, sizeof(sImg), "img_yezi_%d.png", iTag % 100);  

	CCPoint pos;  
	float fAngle;  
	//随机生成叶子的起始位置  
	srand((UINT)GetCurrentTime());  
	int iRand = (rand() % 200);  
	if (iTag == TAG_LEAF1)  
	{  
		pos = ccp(iRand, 600);  
		fAngle = 30;  
	}  
	else  
	{  
		pos = ccp(iRand, 570);  
		fAngle = 50;  
	}  
	//重新生成新的叶片，在起点处释放  
	CCSprite *spriteLeaf = CCSprite::create(sImg);  
	spriteLeaf->setScale(0.5);  
	spriteLeaf->setAnchorPoint(ccp(0.5, 3));  
	spriteLeaf->setRotation(fAngle);  
	spriteLeaf->setPosition(pos);  

	this->addChild(spriteLeaf, iZoder,iTag);  
	this->playLeafAnim(spriteLeaf);//重置后的树叶再次执行飘落动作  
}

