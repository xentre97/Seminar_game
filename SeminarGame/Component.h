#pragma once

/// <summary>
/// Component���N���X
/// �p�����ĉ������Ƃ���,�P��Actor�Ɏ������邾���ł���(�͂�)
/// </summary>
class Component
{
public:
	Component(class Actor* owner);
	virtual ~Component();

	virtual void update();
	virtual void input() {}

protected:
	class Actor* mOwner;
};

