#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "src/GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    CCSize frameSize = glview->getFrameSize();
	CCSize minSize = CCSize(480,800);

	float widthFrame = frameSize.width / minSize.width;
	float heightFrame = frameSize.height / minSize.height;

	if (widthFrame > heightFrame)
	{
		glview->setDesignResolutionSize(minSize.width,minSize.height*heightFrame/widthFrame,ResolutionPolicy::NO_BORDER);
	} 
	else
	{
		glview->setDesignResolutionSize(minSize.width*widthFrame/heightFrame,minSize.height,ResolutionPolicy::NO_BORDER);
	}

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(GameScene::createScene());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
