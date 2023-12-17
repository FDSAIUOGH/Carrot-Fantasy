#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__
#include "cocos2d.h"
USING_NS_CC;
class CGameMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//¼Ì³Ð´´½¨³¡¾°

    virtual bool init();

    void close_game(Ref* pSender);

    void goto_options(Ref* pSender);

    void goto_helper(Ref* pSender);

    void goto_adventure(Ref* psender);

    void goto_boss(Ref* psender);

    void goto_nest(Ref* psender);

    CREATE_FUNC(CGameMenu);
};

//#define WINSIZE Director::getInstance()->getVisibleSize()
//#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif