#include "HudLayer.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "Ui/UIHelper.h"
#include "AppDelegate.h"

USING_NS_CC;

HudLayer* HudLayer::sInstance = nullptr;

HudLayer::HudLayer() 
	:m_MoveFunc(nullptr)
	, m_EnemyAttack(nullptr)
	, m_AttackFunc(nullptr)
	, m_Left(false)
	, m_Right(false)
{
}

HudLayer::~HudLayer()
{
}

bool HudLayer::init()
{
	assert(sInstance == nullptr);
	sInstance = this;

	//Load HUD
	m_Hud = CSLoader::createNode("csb/HUD.csb");
	addChild(m_Hud);
	ui::Helper::doLayout(m_Hud);

	m_StartBtn = static_cast<ui::Button*>(m_Hud->getChildByName("global_anchor_rb")->getChildByName("startBtn"));
	m_StartBtn->addClickEventListener(CC_CALLBACK_1(HudLayer::onEnemyAttack, this));

	m_ResetBtn = static_cast<ui::Button*>(m_Hud->getChildByName("global_anchor_rb")->getChildByName("resetBtn"));
	m_ResetBtn->addClickEventListener(CC_CALLBACK_0(HudLayer::resetGame, this));

	m_PhysicsDebugDraw = static_cast<ui::CheckBox*>(m_Hud->getChildByName("global_anchor_rb")->getChildByName("PhysicsDebugDraw"));
	m_PhysicsDebugDraw->addEventListener(CC_CALLBACK_2(HudLayer::onUiSetDebugDraw,this));

	scheduleUpdate();

	return true;
}

void HudLayer::setControlTarget(std::function<void(float)> moveCallBack, std::function<void()> attackCallBack)
{
	m_MoveFunc = moveCallBack;
	m_AttackFunc = attackCallBack;
}

void HudLayer::onLeftControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent)
{
	switch (controlEvent)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_Left = true;
		m_Right = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_Left = false;
		break;
	default:
		break;
	}
}

void HudLayer::onRightControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent)
{
	switch (controlEvent)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_Left = false;
		m_Right = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_Right = false;
		break;
	default:
		break;
	}
}

void HudLayer::update(float dt)
{
	if (m_MoveFunc == nullptr)
		return;

	if (m_Left){
		m_MoveFunc(-1 * dt);
	}
	else if(m_Right){
		m_MoveFunc(dt);
	}
}

void HudLayer::clearMoveState()
{
	m_Left = false;
	m_Right = false;
}

void HudLayer::onAttackBtnClick(Ref* sender)
{
	if (m_AttackFunc != nullptr)
		m_AttackFunc();
}

void HudLayer::onEnemyAttack(Ref* sender)
{
	if (m_EnemyAttack != nullptr)
		m_EnemyAttack();
}

void HudLayer::setEnemyAttack(std::function<void()> enemyAttackCallBack)
{
	m_EnemyAttack = enemyAttackCallBack;
}

void HudLayer::resetGame()
{
	AppDelegate::getGameWorld().reset(); 
}

void HudLayer::onUiSetDebugDraw(Ref* ref, ui::CheckBox::EventType e)
{
	if (e == ui::CheckBox::EventType::SELECTED)
		AppDelegate::getGameWorld().setPhyiscsDebugDraw(true);
	else if (e == ui::CheckBox::EventType::UNSELECTED)
		AppDelegate::getGameWorld().setPhyiscsDebugDraw(false);
	else
		assert(false);
}

