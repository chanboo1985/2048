#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
	auto director = Director::getInstance();
	auto eglView = director->getOpenGLView();
	if (!eglView)
	{
		eglView = GLView::create("2048");
		director->setOpenGLView(eglView);
	}
	eglView->setViewName("resolution");
	eglView->setFrameSize(480,800);
    return Application::getInstance()->run();
}
