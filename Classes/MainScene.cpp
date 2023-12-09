#include "MainScene.h"
#include "audio/include/AudioEngine.h"
#include "ChooseLevel.h"

USING_NS_CC;
using namespace cocos2d::experimental;
using namespace cocos2d::ui;

float MainScene::actionDuration = 1.0f;


cocos2d::Scene* MainScene::createScene()
{
	AudioEngine::play2d("Sound/MainMenu/BGMusic.mp3", true);
	return MainScene::create();
}



static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}


void MainScene::InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder)
{
	if (fileName == "MainMenu/front_front.png" || fileName == "MainMenu/front_smoke_3.png" || fileName == "MainMenu/front_smoke_1.png")
		outSprite = Sprite::create(fileName);
	else
	{
		auto pinfo = AutoPolygon::generatePolygon(fileName);
		outSprite = Sprite::create(pinfo);
	}
	if (nullptr == outSprite)
	{
		outSprite = nullptr;
		problemLoading(fileName.c_str());
		return;
	}
	outSprite->setPosition(Vec2(x, y));
	parentNode->addChild(outSprite, localZOrder);
}

bool MainScene::InitUI()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//����

	Sprite* rootNode = nullptr;
	InitSprite(rootNode, this, "MainMenu/zh/front_bg_final.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, -1);
	if (nullptr == rootNode)
		return 0;

	//ǰ�ñ���
	Sprite* frontNode = nullptr;
	InitSprite(frontNode, this, "MainMenu/front_front.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 3);
	if (nullptr == frontNode)
		return false;

	//��ʼð�հ�ť
	auto startGameBtn = Button::create("MainMenu/zh/front_btn_start_normal.png", "MainMenu/zh/front_btn_start_pressed.png", "null.png");
	if (nullptr == startGameBtn)
		problemLoading("MainMenu/zh/front_btn_start_normal.png||MainMenu/zh/front_btn_start_pressed.png");
	else
	{
		startGameBtn->setPosition(Vec2(origin.x + 482, origin.y + 384));
		this->addChild(startGameBtn, 1);
		startGameBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
			{
				// ���ŵ����Ч
				AudioEngine::play2d("Sound/MainMenu/Select.mp3", false, 1.0f, nullptr);
				break;
			}
			case ui::Widget::TouchEventType::ENDED:
			{
				//log("_startGameBtn ENDERD");
				 //��ת����
				auto chooseLevel = ChooseLevel::createScene();
				Director::getInstance()->replaceScene(chooseLevel);
				break;
			}
			default:
				break;
			}
			});
	
	}

	


	//�������ϰ�ť
	auto everyDayBtn = Button::create("MainMenu/zh/front_btn_floor_normal.png", "MainMenu/zh/front_btn_floor_pressed.png", "null.png");
	if (nullptr == everyDayBtn)
		problemLoading("MainMenu/zh/front_btn_floor_normal.png||MainMenu/zh/front_btn_floor_pressed.png");
	else
	{
		everyDayBtn->setPosition(Vec2(origin.x + 483, origin.y + 261));
		this->addChild(everyDayBtn, 1);
	}

	//��
	Sprite* everyDayBtnLocked = nullptr;
	InitSprite(everyDayBtnLocked, everyDayBtn, "MainMenu/front_btn_floor_locked.png", everyDayBtn->getSize().width, everyDayBtn->getSize().height / 2, 1);
	if (nullptr == everyDayBtnLocked)
		return false;

	//Monster4
	_monster4 = nullptr;
	InitSprite(_monster4, this, "MainMenu/front_monster_4.png", origin.x + 227, origin.y + 475, 1);
	if (nullptr == _monster4)
		return false;
	_monster4->setScale(0.75);

	//���ð�ť
	auto setUpBtn = Button::create("MainMenu/front_btn_setting_normal.png", "MainMenu/front_btn_setting_pressed.png", "null.png");
	if (nullptr == setUpBtn)
		problemLoading("MainMenu/front_btn_setting_normal.png||MainMenu/front_btn_setting_pressed.png");
	else
	{
		_monster4->addChild(setUpBtn, 1);
		setUpBtn->setPosition(Vec2(176, 89));
	}

	//�������ܲ�
	_carrot = nullptr;
	InitSprite(_carrot, this, "MainMenu/front_carrot.png", origin.x + 920, origin.y + 90, 2);//��ʼ����
	//origin.x + 960, origin.y + 50 //������ʼ����
	//origin.x + 700, origin.y + 0 //���ƽ�������
	//origin.x + 620, origin.y + 14 //�յ�����
	if (nullptr == _carrot)
		return false;
	_carrot->setScale(0.45);

	//Monster6
	_monster6 = nullptr;
	InitSprite(_monster6, this, "MainMenu/front_monster_6.png", origin.x + 995, origin.y + 248, 1);
	if (nullptr == _monster6)
		return false;
	_monster6->setScale(0.75);
	//Monster6Hand
	_monster6Hand = nullptr;
	InitSprite(_monster6Hand, this, "MainMenu/front_monster_6_hand.png", origin.x + 894, origin.y + 256, -1);
	if (nullptr == _monster6Hand)
		return false;
	_monster6Hand->setScale(0.75);

	//���ɰ�ť
	auto confuseBtn = Button::create("MainMenu/front_btn_help_normal.png", "MainMenu/front_btn_help_pressed.png", "null.png");
	if (nullptr == confuseBtn)
		problemLoading("MainMenu/front_btn_help_normal.png||MainMenu/front_btn_help_pressed.png");
	else
	{
		_monster6Hand->addChild(confuseBtn, 0);
		confuseBtn->setPosition(Vec2(170, 405));
	}


	//Monster5
	_monster5 = nullptr;
	InitSprite(_monster5, this, "MainMenu/front_monster_5.png", origin.x + 882, origin.y + 155, 1);
	if (nullptr == _monster5)
		return false;
	_monster5->setScale(0.75);


	//����2
	Sprite* smoke2 = nullptr;
	InitSprite(smoke2, this, "MainMenu/front_smoke_3.png", origin.x + 1020, origin.y + 165, 1);
	if (nullptr == smoke2)
		return false;


	//Monster3
	_monster3 = nullptr;
	InitSprite(_monster3, this, "MainMenu/front_monster_3.png", origin.x + 160, origin.y + 190, 1);
	if (nullptr == _monster3)
		return false;
	_monster3->setScale(0.75);


	//Monste1
	_monster1 = nullptr;
	InitSprite(_monster1, this, "MainMenu/front_monster_1.png", origin.x + 230, origin.y + 155, 1);
	if (nullptr == _monster1)
		return false;
	_monster1->setScale(0.85);


	//����1
	Sprite* smoke1 = nullptr;
	InitSprite(smoke1, this, "MainMenu/front_smoke_1.png", origin.x + 120, origin.y + 170, 1);
	if (nullptr == smoke1)
		return false;

	if (!InitUIAnimation())
		return false;
	return true;
}

bool MainScene::InitUIAnimation()
{
	//1�ź�5�Ź��ﶯ��
	auto monster15MoveBy1 = MoveBy::create(actionDuration * 2, Vec2(7, 0));
	auto monster15MoveBy2 = MoveBy::create(actionDuration * 2, Vec2(-7, 0));
	auto monster15Seq = Sequence::create(monster15MoveBy1, monster15MoveBy2, nullptr);
	_monster1->runAction(RepeatForever::create(monster15Seq));
	_monster5->runAction(RepeatForever::create(monster15Seq->clone()));


	//3�š�4�ź�6�Ź���(�Լ����ֱ�)����
	auto monster346MoveBy1 = MoveBy::create(actionDuration * 2, Vec2(0, 7));
	auto monster346MoveBy2 = MoveBy::create(actionDuration * 2, Vec2(0, -7));
	auto monster346Seq = Sequence::create(monster346MoveBy1, monster346MoveBy2, nullptr);
	_monster3->runAction(RepeatForever::create(monster346Seq));
	_monster4->runAction(RepeatForever::create(monster346Seq->clone()));
	_monster6->runAction(RepeatForever::create(monster346Seq->clone()));
	_monster6Hand->runAction(RepeatForever::create(monster346Seq->clone()));


	//Monster2��ʼ����2�Ź��ﶯ��
	_monster2 = Sprite::create(AutoPolygon::generatePolygon("MainMenu/front_monster_2.png"));
	if (nullptr == _monster2)
	{
		problemLoading("MainMenu/front_monster_2.png");
		return false;
	}
	_monster2->setScale(0.75);
	this->addChild(_monster2, 1);
	auto monster2MoveTo = MoveTo::create(actionDuration * 0.5, Vec2(Director::getInstance()->getVisibleOrigin().x + 342, Director::getInstance()->getVisibleOrigin().y + 140));
	auto monster2Seq = Sequence::create(monster2MoveTo, CallFunc::create([&]() {
		auto monster2MoveBy1 = MoveBy::create(actionDuration * 0.55, Vec2(0, 7));
		auto monster2MoveBy2 = MoveBy::create(actionDuration * 0.55, Vec2(0, -7));
		auto monsterSeq = Sequence::create(monster2MoveBy1, monster2MoveBy2, nullptr);
		_monster2->runAction(RepeatForever::create(monsterSeq));
		}), nullptr);
	_monster2->runAction(monster2Seq);


	//�ܲ�����������������+���Ų��У������������߼����Ų����˶���
	ccBezierConfig controlPointTo;
	controlPointTo.controlPoint_1.set(Director::getInstance()->getVisibleOrigin().x + 960, Director::getInstance()->getVisibleOrigin().y + 50);
	controlPointTo.controlPoint_2.set(Director::getInstance()->getVisibleOrigin().x + 700, Director::getInstance()->getVisibleOrigin().y + 0);
	controlPointTo.endPosition.set(Director::getInstance()->getVisibleOrigin().x + 620, Director::getInstance()->getVisibleOrigin().y + 14);
	auto carrotBezierTo = BezierTo::create(actionDuration * 0.5, controlPointTo);
	auto carrotScaleTo = ScaleTo::create(actionDuration * 0.5, 0.75);
	auto carrotSpawn = Spawn::createWithTwoActions(carrotBezierTo, carrotScaleTo);
	_carrot->runAction(carrotSpawn);
	return true;
}

bool MainScene::init()
{
	if (!InitUI())
		return false;

	return true;
}

