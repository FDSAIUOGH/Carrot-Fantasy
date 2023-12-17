#include "UpCardLayer.h"
#include "Arms.h"
#include "GameScene.h"
CUpCardLayer::CUpCardLayer()
{

}

CUpCardLayer::~CUpCardLayer()
{

}

bool CUpCardLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_pUpGrade = Sprite::create();
	m_pSell = Sprite::create();
	m_pRander = Sprite::create();
	m_pUpGrade->setAnchorPoint(Vec2(0.5,-0.5));
	m_pSell->setAnchorPoint(Vec2(0.5, 1.5));
	this->addChild(m_pRander);
	this->addChild(m_pUpGrade);
	this->addChild(m_pSell);
	this->setVisible(false);
	return true;
}

void CUpCardLayer::clickEvent(Vec2 clickPos, CArms* pArms)
{
	if (this->isVisible())
	{
		if (m_pUpGrade->getBoundingBox().containsPoint(this->convertToNodeSpace(clickPos)))//����
		{
			int nMoney = m_pSelect->getArmsDt()->vecMoney[m_pSelect->getGrade()];//�õ�����������
			if (m_pSelect->getGrade()<m_pSelect->getArmsDt()->vecMoney.size()//��Ƭ���Ƕ�����Ƭ
				&&CGameScene::getInstance()->getUILayer()->getMoney()>=nMoney)//ʣ���ұ����������������
			{
				
				CGameScene::getInstance()->getUILayer()->addMoney(-nMoney);
				m_pSelect->upgrade();
			}
		}

		if (m_pSell->getBoundingBox().containsPoint(this->convertToNodeSpace(clickPos)))//����
		{
			int nNum = 0;//������ֵ

			for (int i = 0; i < m_pSelect->getGrade(); i++)
			{
				nNum += m_pSelect->getArmsDt()->vecMoney[i];
			}

			CGameScene::getInstance()->getUILayer()->addMoney(nNum*0.8);
			m_pSelect->removeFromParent();
			if (m_pSelect->getLastBullet()&&m_pSelect->getLastBullet()->getTag()==1)
			{
				m_pSelect->getLastBullet()->removeFromParent();
			}
		}

		this->setVisible(false);
		return;
	}
	if (!this->isVisible() || pArms)//��һ�ε��,��ʾ��Ƭ
	{
		Vec2 tiledPos = CGameScene::getInstance()->getGameMap()->getTiledByPos(clickPos);
		Vec2 Pos = CGameScene::getInstance()->getGameMap()->getPixelByTiledPos(tiledPos);
		this->setPosition(Pos);
		this->setSpriteCard(pArms);
		m_pSelect = pArms;
		this->setVisible(true);
	}
	else
	{
		this->setVisible(false);
	}
}
void CUpCardLayer::setSpriteCard(CArms* pArms)