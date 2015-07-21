#include "HudLayer.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "Ui/UIHelper.h"

USING_NS_CC;

HudLayer* HudLayer::sInstance = nullptr;

HudLayer::HudLayer() :m_MoveFunc(nullptr), m_Left(false), m_Right(false)
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

	m_LeftBtn = static_cast<ui::Button*>(m_Hud->getChildByName("global_anchor_lb")->getChildByName("Btn_Left"));
	m_RightBtn = static_cast<ui::Button*>(m_Hud->getChildByName("global_anchor_rb")->getChildByName("Btn_Right"));
	m_AttackBtn = static_cast<ui::Button*>(m_Hud->getChildByName("global_anchor_rb")->getChildByName("Btn_Attack"));

	m_LeftBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::onLeftControlTouch, this));
	m_RightBtn->addTouchEventListener(CC_CALLBACK_2(HudLayer::onRightControlTouch, this));
	m_AttackBtn->addClickEventListener(CC_CALLBACK_1(HudLayer::onAttackBtnClick, this));

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
	m_AttackFunc();
}

