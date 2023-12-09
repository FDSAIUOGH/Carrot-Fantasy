#include "ChooseLevel.h"
#include "MainScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;


float ChooseLevel::discountText = 7.5;

cocos2d::Scene* ChooseLevel::createScene()
{
	return ChooseLevel::create();
}

// ö�٣����б����Ÿ���ڵ�Ĳ㼶������ʹ�ø���ڵ�Ĳ㼶���ڹ���
enum zOrderMap
{
	route = 1,             // ��·�㼶
	routeButtonEffect = 5, // ��ť��Ч�㼶
	levelButton = 10       // ��ť�㼶
};

//// ���캯��
//ChooseLevel::ChooseLevel()
//{
//	InitUI();
//	InitEvent();
//}


bool ChooseLevel::init()
{
	if (!Scene::init())
		return false;


	InitUI();

	InitEvent();
	LoadTiledMap();

	return true;
}

void ChooseLevel::InitUI()
{
	//������������
	auto scrollView = ScrollView::create();
	_scrollView = cocos2d::ui::ScrollView::create();
	_scrollView = cocos2d::ui::ScrollView::create();
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setTouchEnabled(true);
	scrollView->setContentSize(Director::getInstance()->getVisibleSize());
	scrollView->setScrollBarEnabled(false);
	this->addChild(scrollView);
	this->addChild(_scrollView);
	Sprite* imageView = nullptr;
	string filePath;
	float nextPosX = 0.f;
	for (int i = 0; i < 14; i++)
	{
		filePath = "ChooseLevel/Map/stage_map_" + to_string(i) + ".png";
		imageView = Sprite::create(filePath);
		//����ê��λ������Ϊ��14�ŵ�ͼ��ǰ���13�ŵ�ͼ��Ȳ�һ��
		imageView->setAnchorPoint(Vec2(0, 0.5));
		imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
		nextPosX += imageView->getContentSize().width;
		scrollView->addChild(imageView);
	}
	scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));


	//UI��ť�ؼ�
	auto layerUI = Layer::create();
	this->addChild(layerUI);
	auto leftPanelPinfo = AutoPolygon::generatePolygon("ChooseLevel/stagemap_toolbar_leftbg.png");
	//�ñ���ͼʼ������Ļ�����Ͻ�
	auto leftPanel = Sprite::create(leftPanelPinfo);
	leftPanel->setAnchorPoint(Vec2(0, 1));
	leftPanel->setPosition(0, Director::getInstance()->getVisibleSize().height);
	leftPanel->setScale(0.7);
	layerUI->addChild(leftPanel);
	//��������ͼ������ӽڵ㣨������ť��
	string toolbarHomeFilePath = "ChooseLevel/stagemap_toolbar_home.png";
	_toolbarHome = Button::create(toolbarHomeFilePath, toolbarHomeFilePath, "");
	_toolbarHome->setAnchorPoint(Vec2(0, 0));
	_toolbarHome->setPosition(Vec2(10, 10));
	_toolbarHome->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarHome);

	string toolbarShopFilePath = "ChooseLevel/stagemap_toolbar_shop.png";
	_toolbarShop = Button::create(toolbarShopFilePath, toolbarShopFilePath, "");
	_toolbarShop->setAnchorPoint(Vec2(0, 0));
	_toolbarShop->setPosition(Vec2(125, 10));
	_toolbarShop->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarShop);

	string toolbarLeaderboardFilePath = "ChooseLevel/stagemap_toolbar_leaderboard.png";
	_toolbarLeaderboard = Button::create(toolbarLeaderboardFilePath, toolbarLeaderboardFilePath, "");
	_toolbarLeaderboard->setAnchorPoint(Vec2(0, 0));
	_toolbarLeaderboard->setPosition(Vec2(235, 10));
	_toolbarLeaderboard->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarLeaderboard);


	//�����м�Ĵ�����ť
	string discountTagStoneFilePath = "ChooseLevel/zh/discount_tag_stone.png";
	_discountTagStone = Button::create(discountTagStoneFilePath, discountTagStoneFilePath, "");
	_discountTagStone->setAnchorPoint(Vec2(0.5, 1));
	_discountTagStone->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
	_discountTagStone->setScale(0.7);

	_discountText = Label::createWithBMFont("ChooseLevel/discount.fnt", "8");
	_discountTagStone->addChild(_discountText);
	_discountText->setAnchorPoint(Vec2(0, 0));
	_discountText->setPosition(160, 65);
	layerUI->addChild(_discountTagStone);


	//�������Ͻ� �����ǰ�ť
	string toolbarRightbgFilePath = "ChooseLevel/stagemap_toolbar_rightbg.png";
	_toolbarRightbg = Button::create(toolbarRightbgFilePath, toolbarRightbgFilePath, "");
	_toolbarRightbg->setAnchorPoint(Vec2(1, 1));
	_toolbarRightbg->setPosition(Director::getInstance()->getVisibleSize());
	_toolbarRightbg->setScale(0.7);
	layerUI->addChild(_toolbarRightbg);

	//�����������ǵ�ͼƬ����
	auto starImage = Sprite::create("ChooseLevel/zh/stagemap_toolbar_overten.png");
	starImage->setAnchorPoint(Vec2(1, 1));
	starImage->setPosition(Director::getInstance()->getVisibleSize());
	starImage->setScale(0.7);
	layerUI->addChild(starImage);

	auto text = Label::createWithSystemFont("010", "Arial", 24);
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(220, 73));
	starImage->addChild(text);
}

void ChooseLevel::InitEvent()
{

	//��ʼ����ҳ��ť���̵갴ť�����а�ť�������¼�
	_toolbarHome->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto mainScene = MainScene::createScene();
			Director::getInstance()->replaceScene(mainScene);
		}
		});

	_toolbarShop->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the shop");
		}
		});


	_toolbarLeaderboard->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the leaderboard");
		}
		});

	//��ʼ���м�Ĵ�����ť
	_discountTagStone->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the discountTagStone");
		}
		});


	//��ʼ�����Ͻ����������¼�
	_toolbarRightbg->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("click the toolbarRightbg");
		}
		});

}

// LoadTiledMap ����
void ChooseLevel::LoadTiledMap()
{
	TMXTiledMap* map = TMXTiledMap::create("ChooseLevel/Map/TiledMap.tmx");
	//��ȡ��Ƭ��ͼ�е�point�����
	auto objectGroup = map->getObjectGroup("point");
	//��������е����ж����ȡ����
	auto objs = objectGroup->getObjects();
	//��������
	for (int i = 0; i < objs.size(); i++)
	{
		//������Ƭ��ͼ��λ��������Ϣ���ùؿ���ť
		auto button = Button::create();
		_scrollView->addChild(button, zOrderMap::levelButton, i);
		//std::vector<cocos2d::ui::Button*> _routeButtonArray;
		_routeButtonArray.push_back(button);
		//ͼƬ����
		string texture = "ChooseLevel/stagepoint_adv.png";
		auto valueMap = objs[i].asValueMap();
			//�жϵ�ǰ�ؿ�����
			if (valueMap["isBoos"].asString() == "YES")//�Ƿ�Ϊboss�ؿ�
				texture = "ChooseLevel/stagepoint_gate.png";
			else if (valueMap["isTime"].asString() == "YES")//�Ƿ�Ϊʱ��ؿ�
				texture = "ChooseLevel/stagepoint_time.png";
			else if (valueMap["isChange"].asString() == "YES")//�Ƿ�Ϊ�漴�ؿ�
				texture = "ChooseLevel/stagepoint_chance.png";

		button->loadTextures(texture, texture, "");
		//��ť��λ������
		button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//��ȡ���������:(asһ��ķ��� ��ת�����ͣ�
		//���ð�ťTag�ǳ���Ҫ��ʵ���Ͼ��ǵ�ǰ�ؿ�����������0��ʼ����0��ʾ��1�أ�1��ʾ��2�أ��Դ����ơ�
		button->setTag(i);
		button->setScale(0.7);
		//�����¼�������
		button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				//��ǰ�ؿ��ȼ�������Tagֵ���ض�Ӧ�ؿ�������
				log("hello %d", ((Button*)sender)->getTag());
				//TODO�����عؿ����ݣ�������Ϸ
			}
			});

	}
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChooseLevel.cpp\n");
}
