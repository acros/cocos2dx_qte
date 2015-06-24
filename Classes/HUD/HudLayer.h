#ifndef __IN_GAME_HUD_H__
#define __IN_GAME_HUD_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ui/UIButton.h"

USING_NS_CC;

class Soldier;
// enum class DirectionState{
// 	Dir_None,
// 	Dir_Left,
// 	Dir_Right,
// 
// 	//TODO
// 	Dir_Up,
// 	Dir_Down
// };

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

	void setControlTarget(std::function<void(float)> moveCallBack,std::function<void()> attackCallBack);

	void update(float dt)override;

	void clearMoveState();
protected:

	std::function<void(float)>	m_MoveFunc;
	std::function<void()>		m_AttackFunc;

	void onLeftControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent);
	void onRightControlTouch(Ref *sender, ui::Widget::TouchEventType controlEvent);
	void onAttackBtnClick(Ref* sender);

	RefPtr<Node>		m_Hud;

	RefPtr<ui::Button>		m_LeftBtn;
	RefPtr<ui::Button>		m_RightBtn;
	RefPtr<ui::Button>		m_AttackBtn;

	bool isSpriteInteract();

	//DirectionState		m_DirState;
	bool	m_Left;
	bool	m_Right;

private:
	static HudLayer*	sInstance;
};

#endif