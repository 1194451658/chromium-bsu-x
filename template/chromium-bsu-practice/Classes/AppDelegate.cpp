#include "AppDelegate.h"
#include "HelloWorldScene.h"


#include "scene/TestArmatureScene.h"
#include "scene/TestEffect.h"
#include "scene/TestPhysicsManager.h"
#include "scene/TestAircraft.h"
#include "scene/TestControl.h"
#include "scene/TestShotMethod.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {

	// init resource
	CCFileUtils::sharedFileUtils()->addSearchPath("Resources");

    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pDirector->setDepthTest(true);

	// pEGLView->setViewPortInPoints(0,0, 300, 400);
	// pEGLView->setScissorInPoints(0, 0, 300, 400);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	// CCScene *pScene = HelloWorld::scene();


	// --------------------
	// test
	// -------------------

	// CCScene* pScene = TestPhysicsManager::scene();
	// CCScene *pScene = TestEffectScene::scene();
	// CCScene* pScene = TestArmatureScene::scene();
	CCScene* pScene = TestAircraft::scene();
	// CCScene* pScene = TestShotMethod::scene();

	// CCScene* pScene = TestControl::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
