#include "GameMenu.h"
#include "HelperScene.h"
#include "GameMenu.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

using namespace cocos2d::experimental;
using namespace cocos2d::ui;
/*错误处理*/
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
}
/*工具函数*/
int find(float page[], int N, float x) {
	for (int i = 0; i < N; i++) {
		if (x >= page[i]) {
			return i - 1;
		}
	}
	return -1;
}
/*****************************  HelperScene类  ***********************************************************/
cocos2d::Scene* HelperScene::createScene()
{
	return HelperScene::create();
}
bool HelperScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/************************************************  背景创建  *******************************************************/
	auto background_image = Sprite::create("/HelperScene/help_3-hd_bg.png");
	background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(background_image);
	//help_layer
	auto help_layer = HelpLayer::createLayer();
	help_layer->setName("HelpLayer");
	this->addChild(help_layer);
	//monster_layer 
	auto monster_layer = MonsterLayer::createLayer();
	monster_layer->setName("MonsterLayer");
	monster_layer->setVisible(false);//初始化时被设置为不可见状态
	this->addChild(monster_layer);
	// tower_layer
	auto tower_layer = TowerLayer::createLayer();
	tower_layer->setName("TowerLayer");
	tower_layer->setVisible(false);//初始化时被设置为不可见状态
	this->addChild(tower_layer);


	//home键
	auto menu_all = Menu::create();
	menu_all->setPosition(Vec2::ZERO);

	auto home = MenuItemImage::create("/HelperScene/help_1-hd_67.PNG", "/HelperScene/help_1-hd_38.PNG", CC_CALLBACK_1(HelperScene::goto_home, this));
	home->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
		origin.y + visibleSize.height * 0.92));
	menu_all->addChild(home);
	this->addChild(menu_all);
	/***********************************************选项卡****************************************************/
	//help选项卡
	auto help_btn = ui::Button::create("/HelperScene/help_1-hd-33_normal.PNG", "/HelperScene/help_1-hd-33_normal.PNG", "/HelperScene/help_1-hd_33.PNG");
	help_btn->setName("HelpBtn");
	help_btn->setScale(0.8);
	help_btn->setPosition(Vec2(origin.x + visibleSize.width*0.31,
		origin.y + visibleSize.height*0.925));
	//help_btn->addTouchEventListener(CC_CALLBACK_1(HelperScene::goto_help, this));
	help_btn->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::BEGAN) {
			AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
		}
		else if (type == ui::Widget::TouchEventType::ENDED) {
			goto_help(sender);
		}
		});
	help_btn->setEnabled(false);
	this->addChild(help_btn);
	//monster选项卡
	auto monster_btn = ui::Button::create("/HelperScene/help_1-hd_71_normal.PNG", "/HelperScene/help_1-hd_71_normal.PNG", "/HelperScene/help_1-hd_71.png");
	monster_btn->setName("MonsterBtn");
	monster_btn->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height*0.922));
	//monster_btn->addTouchEventListener(CC_CALLBACK_1(HelperScene::goto_monster, this));
	monster_btn->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::BEGAN) {
			AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
		}
		else if (type == ui::Widget::TouchEventType::ENDED) {
			goto_monsters(sender);
		}
		});
	this->addChild(monster_btn);
	//person选项卡
	auto tower_btn = ui::Button::create("/HelperScene/help_1-hd_66_normal.PNG", "/HelperScene/help_1-hd_66_normal.PNG", "/HelperScene/help_1-hd_66.PNG");
	tower_btn->setName("TowerBtn");
	tower_btn->setPosition(Vec2(origin.x + visibleSize.width*0.69,
		origin.y + visibleSize.height*0.923));
	//tower_btn->addTouchEventListener(CC_CALLBACK_1(HelperScene::goto_tower, this));
	tower_btn->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::BEGAN) {
			AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
			goto_towers(sender); // 在按下时直接执行函数
		}
		});

	this->addChild(tower_btn);


	return true;
}
void HelperScene::goto_home(Ref* psender)
{
	AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
	Scene* menu_scene = CGameMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, menu_scene, Color3B::BLACK));
}
void HelperScene::goto_help(Ref* psender)
{
	//AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
	Node* help = this->getChildByName("HelpLayer");
	Node* monster = this->getChildByName("MonsterLayer");
	Node* tower = this->getChildByName("TowerLayer");

	help->setVisible(true);
	monster->setVisible(false);
	tower->setVisible(false);

	Node* toplayer = help->getChildByName("toplayer");
	toplayer->setPosition(Vec2::ZERO);

	Node* num = help->getChildByName("page_num1");
	static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");

	Node* help_btn = this->getChildByName("HelpBtn");
	help_btn->setScale(0.8);
	static_cast<ui::Button*>(help_btn)->setEnabled(false);
	Node* monster_btn = this->getChildByName("MonsterBtn");
	static_cast<ui::Button*>(monster_btn)->setEnabled(true);
	Node* tower_btn = this->getChildByName("TowerBtn");
	static_cast<ui::Button*>(tower_btn)->setEnabled(true);
}
void HelperScene::goto_monsters(Ref* psender)
{
	//AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
	Node* help = this->getChildByName("HelpLayer");
	Node* monster = this->getChildByName("MonsterLayer");
	Node* tower = this->getChildByName("TowerLayer");

	help->setVisible(false);
	monster->setVisible(true);
	tower->setVisible(false);

	Node* help_btn = this->getChildByName("HelpBtn");
	static_cast<ui::Button*>(help_btn)->setEnabled(true);
	Node* monster_btn = this->getChildByName("MonsterBtn");
	monster_btn->setScale(0.8);
	static_cast<ui::Button*>(monster_btn)->setEnabled(false);
	Node* tower_btn = this->getChildByName("TowerBtn");
	static_cast<ui::Button*>(tower_btn)->setEnabled(true);
}
void HelperScene::goto_towers(Ref* psender)
{
	AudioEngine::play2d("sound/Select.mp3", false, 1.2f);
	Node* help = this->getChildByName("HelpLayer");
	Node* monster = this->getChildByName("MonsterLayer");
	Node* tower = this->getChildByName("TowerLayer");

	help->setVisible(false);
	monster->setVisible(false);
	tower->setVisible(true);

	Node* toplayer2 = tower->getChildByName("toplayer2");
	toplayer2->setPosition(Vec2::ZERO);

	Node* num = tower->getChildByName("page_num2");
	static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");

	Node* help_btn = this->getChildByName("HelpBtn");
	static_cast<ui::Button*>(help_btn)->setEnabled(true);
	Node* monster_btn = this->getChildByName("MonsterBtn");
	static_cast<ui::Button*>(monster_btn)->setEnabled(true);
	Node* tower_btn = this->getChildByName("TowerBtn");
	tower_btn->setScale(0.8);
	static_cast<ui::Button*>(tower_btn)->setEnabled(false);
}
/*************************************** HelpLayer类  ******************************************/
cocos2d::Layer* HelpLayer::createLayer()
{
	return HelpLayer::create();
}
bool HelpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	this->setName("HelpLayer");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/**************************  滑动层  ********************************/
	auto toplayer = Layer::create();
	toplayer->setName("toplayer");
	/**************************  第一页  ******************************/
	auto help_1_image = Sprite::create("/HelperScene/help_3-hd_1.png");
	help_1_image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_1_image);
	auto help_1_txt = Sprite::create("/HelperScene/help_1-hd_73.PNG");
	help_1_txt->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.22));
	toplayer->addChild(help_1_txt);
	/**************************  第二页  ******************************/
	auto help_2_image = Sprite::create("/HelperScene/help_3-hd_2.png");
	help_2_image->setPosition(Vec2(origin.x + visibleSize.width * 1.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_2_image);
	auto help_2_txt = Sprite::create("/HelperScene/help_1-hd_4.PNG");
	help_2_txt->setPosition(Vec2(origin.x + visibleSize.width *1.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_2_txt);
	/**************************  第三页  ******************************/
	auto help_3_image = Sprite::create("/HelperScene/help_3-hd_3.png");
	help_3_image->setPosition(Vec2(origin.x + visibleSize.width * 2.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_3_image);
	auto help_3_txt = Sprite::create("/HelperScene/help_1-hd_50.PNG");
	help_3_txt->setPosition(Vec2(origin.x + visibleSize.width * 2.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_3_txt);
	/**************************  第四页  ******************************/
	auto help_4_image = Sprite::create("/HelperScene/help_3-hd_4.png");
	help_4_image->setPosition(Vec2(origin.x + visibleSize.width * 3.5, origin.y + visibleSize.height *0.55));
	toplayer->addChild(help_4_image);
	auto help_4_txt = Sprite::create("/HelperScene/help_1-hd_65.PNG");
	help_4_txt->setPosition(Vec2(origin.x + visibleSize.width * 3.5, origin.y + visibleSize.height *0.22));
	toplayer->addChild(help_4_txt);
	this->addChild(toplayer);

	/***************************  页码  ******************************/
	auto page_num_image = Sprite::create("/HelperScene/help_1-hd_0.PNG");//创建了一个 Sprite 对象，用于显示页码的背景图片
	page_num_image->setPosition(Vec2(origin.x + visibleSize.width *0.51, origin.y + visibleSize.height * 0.06));
	this->addChild(page_num_image);
	auto num_divide = Sprite::create("/HelperScene/num_-1.png");//标记图片，用于表示页码之间的分隔符和最大页码数
	num_divide->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.062));
	this->addChild(num_divide);
	num_divide->setScale(1.4);
	auto num_4 = Sprite::create("/HelperScene/num_4.png");
	num_4->setPosition(Vec2(origin.x + visibleSize.width / 2 + num_4->getContentSize().width * 2, origin.y + visibleSize.height * 0.062));
	this->addChild(num_4);
	num_4->setScale(1.4);
	auto page_num = Sprite::create("/HelperScene/num_1.png");//创建了一个 Sprite 对象用于显示当前页码的数字图片
	page_num->setName("page_num1");
	page_num->setScale(1.4);
	page_num->setPosition(Vec2(origin.x + visibleSize.width / 2 - page_num->getContentSize().width * 3, origin.y + visibleSize.height * 0.062));
	this->addChild(page_num);
	/****************************  滑动实现  *****************************/
	auto listener = EventListenerTouchOneByOne::create();//创建了一个触摸监听器
	//onTouchBegan 函数捕获触摸开始事件，并返回 true，表示事件已被处理
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	//onTouchMoved 函数捕获触摸移动事件，计算出触摸点在水平方向上的位移 distance，并通过修改 toplayer 的 X 位置来实现滑动效果
	listener->onTouchMoved = [this,toplayer](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		toplayer->setPositionX(toplayer->getPositionX() + distance);
	};
	//onTouchEnded 函数捕获触摸结束事件，计算触摸点的起始位置与结束位置之间的水平位移 distance。
	listener->onTouchEnded = [this,toplayer,visibleSize](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;
		float page[4] = { 0,-visibleSize.width,-2 * visibleSize.width,-3 * visibleSize.width };
		if (distance > visibleSize.width / 6) {
		//如果位移超过屏幕宽度的六分之一，且向右滑动
			if (toplayer->getPosition().x > 0) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
			}
			else {
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
					Node* num =this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
			}
		}
		else if (distance < -visibleSize.width / 6) {
		//如果位移超过屏幕宽度的六分之一，且向左滑动
			if (toplayer->getPosition().x < page[3]) {
				toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
			}
			else {
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
				}
			}
		}
		else {
			//如果位移没有达到六分之一屏幕宽度
			if (distance > 0) {
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[3], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
				}
			}
			else {
				if (toplayer->getPosition().x < 0 && toplayer->getPosition().x >page[1]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
				}
				else if (toplayer->getPosition().x < page[1] && toplayer->getPosition().x >page[2]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[1], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
				}
				else if (toplayer->getPosition().x < page[2] && toplayer->getPosition().x >page[3]) {
					toplayer->runAction(MoveTo::create(0.1, Vec2(page[2], 0)));
					Node* num = this->getChildByName("page_num1");
					static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
/**************************************  MonsterLayer类  ************************************/
cocos2d::Layer* MonsterLayer::createLayer()
{
	return MonsterLayer::create();
}
bool MonsterLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	this->setName("MonsterLayer");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	auto bg_image = Sprite::create("/HelperScene/help_3-hd_monster.png");
	bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height*0.45));
	this->addChild(bg_image);

	//文字
	auto little_monster_txt = Sprite::create("/HelperScene/help_1-hd_14.PNG");
	little_monster_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
		origin.y + visibleSize.height *0.45));
	this->addChild(little_monster_txt);

	auto fly_monster_txt = Sprite::create("/HelperScene/help_1-hd_1.PNG");
	fly_monster_txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height *0.45));
	this->addChild(fly_monster_txt);

	auto boss_monster_txt = Sprite::create("/HelperScene/help_1-hd_2.PNG");
	boss_monster_txt->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
		origin.y + visibleSize.height *0.45));
	this->addChild(boss_monster_txt);

	auto blood_1 = Sprite::create("/HelperScene/help_1-hd_3.PNG");
	blood_1->setPosition(Vec2(origin.x + visibleSize.width *0.336,
		origin.y + visibleSize.height * 0.285));
	this->addChild(blood_1);
	auto blood_2= Sprite::create("/HelperScene/help_1-hd_3.PNG");
	blood_2->setPosition(Vec2(origin.x + visibleSize.width *0.645,
		origin.y + visibleSize.height * 0.285));
	this->addChild(blood_2);

	auto speed_1= Sprite::create("/HelperScene/help_1-hd_29.PNG");
	speed_1->setPosition(Vec2(origin.x + visibleSize.width *0.336,
		origin.y + visibleSize.height * 0.355));
	this->addChild(speed_1);
	auto speed_2 = Sprite::create("/HelperScene/help_1-hd_29.PNG");
	speed_2->setPosition(Vec2(origin.x + visibleSize.width *0.645,
		origin.y + visibleSize.height * 0.355));
	this->addChild(speed_2);

	auto txt = Sprite::create("/HelperScene/help_1-hd_39.PNG");
	txt->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height * 0.2)); 
	this->addChild(txt);

	return true;
}
/*************************************  TowerLayer类  ***********************************/
cocos2d::Layer* TowerLayer::createLayer()
{
	return TowerLayer::create();
}
bool TowerLayer::init()
{
	if (!Layer::create()) {
		return false;
	}
	this->setName("TowerLayer");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/**************************  滑动层  ********************************/
	auto toplayer2 = Layer::create();//创建了新的图层对象toplayer2,用于展示滑动的内容
	toplayer2->setName("toplayer2");
	/**************************  第1页  ******************************/
	auto tower_1 = Sprite::create("/HelperScene/tower_1.png");
	tower_1->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_1);
	/**************************  第2页  ******************************/
	auto tower_2 = Sprite::create("/HelperScene/tower_2.png");
	tower_2->setPosition(Vec2(origin.x + visibleSize.width * 1.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_2);	
	/**************************  第3页  ******************************/
	auto tower_3 = Sprite::create("/HelperScene/tower_3.png");
	tower_3->setPosition(Vec2(origin.x + visibleSize.width * 2.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_3);	
	/**************************  第4页  ******************************/
	auto tower_4 = Sprite::create("/HelperScene/tower_4.png");
	tower_4->setPosition(Vec2(origin.x + visibleSize.width * 3.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_4);	
	/**************************  第5页  ******************************/
	auto tower_5 = Sprite::create("/HelperScene/tower_5.png");
	tower_5->setPosition(Vec2(origin.x + visibleSize.width * 4.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_5);	
	/**************************  第6页  ******************************/
	auto tower_6 = Sprite::create("/HelperScene/tower_6.png");
	tower_6->setPosition(Vec2(origin.x + visibleSize.width * 5.5,
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_6);	
	/**************************  第7页  ******************************/
	auto tower_7 = Sprite::create("/HelperScene/tower_7.png");
	tower_7->setPosition(Vec2(origin.x + visibleSize.width * 6.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_7);	
	/**************************  第8页  ******************************/
	auto tower_8 = Sprite::create("/HelperScene/tower_8.png");
	tower_8->setPosition(Vec2(origin.x + visibleSize.width * 7.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_8);	
	/**************************  第9页  ******************************/
	auto tower_9 = Sprite::create("/HelperScene/tower_9.png");
	tower_9->setPosition(Vec2(origin.x + visibleSize.width * 8.5, 
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_9);	
	/**************************  第10页  ******************************/
	auto tower_10 = Sprite::create("/HelperScene/tower_10.png");
	tower_10->setPosition(Vec2(origin.x + visibleSize.width * 9.5,
		origin.y + visibleSize.height * 0.5));
	toplayer2->addChild(tower_10);
	this->addChild(toplayer2);
	/***************************  页码  ******************************/
	//page_num_image 是用于显示页码的背景图片的精灵对象
	auto page_num_image = Sprite::create("/HelperScene/help_1-hd_0.PNG");
	page_num_image->setPosition(Vec2(origin.x + visibleSize.width * 0.51, origin.y + visibleSize.height * 0.06));
	this->addChild(page_num_image);
	//num_divide 是用于显示分隔符的精灵对象
	auto divide_num = Sprite::create("/HelperScene/num_-1.png");
	divide_num->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.062));
	this->addChild(divide_num);
	divide_num->setScale(1.4);
	//num_10 是显示数字 "10" 的精灵对象,表示总页码为10
	auto num_10 = Sprite::create("/HelperScene/num_10.png");
	num_10->setPosition(Vec2(origin.x + visibleSize.width / 2 + num_10->getContentSize().width, 
		origin.y + visibleSize.height * 0.062));
	this->addChild(num_10);
	num_10->setScale(1.4);
	//page_num 是用于显示当前页码的精灵对象
	auto page_num = Sprite::create("/HelperScene/num_1.png");
	page_num->setName("page_num2");
	page_num->setScale(1.4);
	page_num->setPosition(Vec2(origin.x + visibleSize.width / 2 - page_num->getContentSize().width * 3,
		origin.y + visibleSize.height * 0.062));
	this->addChild(page_num);
	/****************************  滑动实现  *****************************/
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	listener2->onTouchMoved = [this, toplayer2](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		toplayer2->setPositionX(toplayer2->getPositionX() + distance);
	};
	listener2->onTouchEnded = [this, toplayer2, visibleSize](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;
		float page[10] = { 0,-visibleSize.width,-2 * visibleSize.width,-3 * visibleSize.width,-4 * visibleSize.width,
			-5 * visibleSize.width,-6 * visibleSize.width,-7 * visibleSize.width,-8 * visibleSize.width,-9 * visibleSize.width };
		int n = find(page, 10, toplayer2->getPosition().x);
		if (distance > visibleSize.width / 6) {
			if (toplayer2->getPosition().x > 0) {
				toplayer2->runAction(MoveTo::create(0.1, Vec2(page[0], 0)));
			}
			else {
				if (n != -1) {
					toplayer2->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
				}
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					default:
						break;
				}
			}
		}
		else if (distance < -visibleSize.width / 6) {
			if (toplayer2->getPosition().x < page[9]) {
				toplayer2->runAction(MoveTo::create(0.1, Vec2(page[9], 0)));
			}
			else {
				if (n != -1) {
					toplayer2->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
				}
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_10.png");
						break;
					default:
						break;
				}
			}
		}
		else {
			if (distance > 0) {
				if (n != -1) {
					toplayer2->runAction(MoveTo::create(0.1, Vec2(page[n + 1], 0)));
				}
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_10.png");
						break;
					default:
						break;
				}
			}
			else {
				if (n != -1) {
					toplayer2->runAction(MoveTo::create(0.1, Vec2(page[n], 0)));
				}
				Node* num = this->getChildByName("page_num2");
				switch (n) {
					case 0:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_1.png");
						break;
					case 1:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_2.png");
						break;
					case 2:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_3.png");
						break;
					case 3:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_4.png");
						break;
					case 4:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_5.png");
						break;
					case 5:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_6.png");
						break;
					case 6:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_7.png");
						break;
					case 7:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_8.png");
						break;
					case 8:
						static_cast<Sprite*>(num)->setTexture("/HelperScene/num_9.png");
						break;
					default:
						break;
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	return true;
}
