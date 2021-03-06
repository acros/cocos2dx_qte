#ifndef __IN_GAME_HUD_H__
#define __IN_GAME_HUD_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"
#include "ui/UICheckBox.h"

USING_NS_CC;


class HudLayer : public cocos2d::Layer{
CC_CONSTRUCTOR_ACCESS:
	HudLayer();
	~HudLayer();

	virtual bool init()override;
public:
	static HudLayer*	getInstance(){
		assert(sInstance != nullptr);
		return sInstance;
	}

	CREATE_FUNC(HudLayer);

	//Hack
	void setControlTarget(std::function<void(float)> moveCallBack,std::function<void()> attackCallBack);
	void setEnemyAttack(std::function<void()> enemyAttackCallBack);

	void update(float dt)override;
	void clearMoveState();

	void resetGame();

protected:
	void onUiSetDebugDraw(Ref*, ui::CheckBox::EventType);

	std::function<void(float)>	m_MoveFunc;
	std::function<void()>		m_AttackFunc;
	std::function<void()>		m_EnemyAttack;

	void onLeftControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent);
	void onRightControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent);
	void onAttackBtnClick(Ref* sender);
	void onEnemyAttack(Ref* sender);

	RefPtr<Node>		m_Hud;

	RefPtr<ui::Button>		m_StartBtn;
	RefPtr<ui::Button>		m_ResetBtn;
	RefPtr<ui::CheckBox>	m_PhysicsDebugDraw;

	//DirectionState		m_DirState;
	bool	m_Left;
	bool	m_Right;

private:
	static HudLayer*	sInstance;
};

#endif