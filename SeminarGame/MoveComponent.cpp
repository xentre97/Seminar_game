#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner)
	: Component(owner)
	, mGravity(1.0f)
	, mMoveSpeed(200.0f)
	, mJumpSpeed(-30.0f)
	, mVelocityX(0.0f)
	, mVelocityY(0.0f)
	, mIsJumping(false)
{
}

void MoveComponent::update(){
	float deltaTime = GetFrameTime();

	//水平移動
	int forward = mOwner->getForward();
	mVelocityX = forward * mMoveSpeed;

	//垂直移動
	mVelocityY += mGravity * deltaTime;

	//速度を位置に反映
	Vector2 pos = mOwner->getPosition();
	pos.x += mVelocityX * deltaTime;
	pos.y += mVelocityY * deltaTime;

	mOwner->setPosition(pos);

}
