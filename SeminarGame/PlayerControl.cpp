#include "PlayerControl.h"
#include <raylib.h>
#include "PlayerActor.h"
#include <string>

PlayerControl::PlayerControl(PlayerActor* actor)
	: MoveComponent(actor)
	, mPlayer(actor)
	//, mMoveState(ms_idle)
	//, mActionState(as_idle)
	, mIsGuarding(false)
	, mDashSpeed(mMoveSpeed * 1.5f)
{
}

void PlayerControl::input()
{
	Vector2 pos = mOwner->getPosition();
	
	// ������
	mVelocityX = 0.0f;
	
	// 1.MoveState�̕���
	switch (mPlayer->getMoveState())
	{
	case PlayerActor::ms_idle:
	{
		if (IsKeyPressed(KEY_SPACE)) {
			mPlayer->setMoveState(PlayerActor::ms_jump);
			mVelocityY = mJumpSpeed;
		}
		else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				mPlayer->setMoveState(PlayerActor::ms_dash);
			}
			else {
				mPlayer->setMoveState(PlayerActor::ms_walk);
			}
		}
		break;
	}
	case PlayerActor::ms_walk:
	{
		if (IsKeyPressed(KEY_SPACE)) {
			mPlayer->setMoveState(PlayerActor::ms_jump);
			mVelocityY = mJumpSpeed;
		}
		else if (!(IsKeyDown(KEY_D) || IsKeyDown(KEY_A))) {
			mPlayer->setMoveState(PlayerActor::ms_idle);
		}
		else if (IsKeyDown(KEY_LEFT_SHIFT)) {
			mPlayer->setMoveState(PlayerActor::ms_dash);
		}
		break;
	}
	case PlayerActor::ms_dash:
	{
		if (IsKeyPressed(KEY_SPACE)) {
			mPlayer->setMoveState(PlayerActor::ms_jump);
			mVelocityY = mJumpSpeed;
		}
		else if (!IsKeyDown(KEY_LEFT_SHIFT)) {
			if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
				mPlayer->setMoveState(PlayerActor::ms_walk);
			}
			else {
				mPlayer->setMoveState(PlayerActor::ms_idle);
			}
		}
		break;
	}
	case PlayerActor::ms_jump:
	{
		break;
	}
	}
	
	// 2.ActionState�̕���
	switch (mPlayer->getActionState())
	{
	case PlayerActor::as_idle:
	{
		if (IsKeyPressed(KEY_W)) {
			mPlayer->setActionState(PlayerActor::as_attack);
			actionTimer = 0.0f;
		}
		else if (IsKeyDown(KEY_S)) {
			mPlayer->setActionState(PlayerActor::as_guard);
		}
		break;
	}
	case PlayerActor::as_attack:
	{
		break;
	}
	case PlayerActor::as_guard:
	{
		if (!IsKeyDown(KEY_S)) {
			mPlayer->setActionState(PlayerActor::as_idle);
		}
		break;
	}
	}

	// ���R����
	if (mVelocityY > 0.0f && mPlayer->getMoveState() != PlayerActor::ms_jump) {
		mPlayer->setMoveState(PlayerActor::ms_jump);
	}

	if (IsKeyDown(KEY_D)) {
		mPlayer->setForward(1);
	}
	else if(IsKeyDown(KEY_A)) {
		mPlayer->setForward(-1);
	}
}

void PlayerControl::update()
{
	// �d��
	if (mVelocityY < 10) {
		mVelocityY += mGravity;
	}
	// ���x��ݒ�
	Vector2 pos = mOwner->getPosition();

	// 1,MoveState��update
	switch (mPlayer->getMoveState())
	{
	case PlayerActor::ms_idle:
	{
		break;
	}
	case PlayerActor::ms_walk:
	{
		if (IsKeyDown(KEY_D)) {
			mVelocityX = mMoveSpeed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_A)) {
			mVelocityX = -mMoveSpeed * GetFrameTime();
		}
		break;
	}
	case PlayerActor::ms_dash:
	{
		if (IsKeyDown(KEY_D)) {
			mVelocityX = mDashSpeed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_A)) {
			mVelocityX = -mDashSpeed * GetFrameTime();
		}
		break;
	}
	case PlayerActor::ms_jump:
	{
		if (IsKeyDown(KEY_D)) {
			mVelocityX = mMoveSpeed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_A)) {
			mVelocityX = -mMoveSpeed * GetFrameTime();
		}
		break;
	}
	}

	// 1,ActionState��update
	switch (mPlayer->getActionState())
	{
	case PlayerActor::as_idle:
	{
		break;
	}
	case PlayerActor::as_attack:
	{
		actionTimer += 1.0f;
		break;
	}
	case PlayerActor::as_guard:
	{
		break;
	}
	}

	pos.x += mVelocityX;
	pos.y += mVelocityY;
	// �������ɂԂ���Ƃ�,velocityY��GamePlay�N���X��
	// updateCollision�֐���0�ɖ߂����	
	mOwner->setPosition(pos);

	if (mPlayer->getActionState() == PlayerActor::as_attack) {
		actionTimer += 1.0f;
		if (actionTimer > 60.0f) {
			mPlayer->setActionState(PlayerActor::as_idle);
		}
	}

	StateDraw();
}

// GamePlay�ŌĂԁB���Ƃ̏Փˉ����Ɏg����B
// �d�͂͏�ɓ����Ă���̂Œn��ɂ���Ƃ���ɌĂ΂��
void PlayerControl::fixFloorCol()
{
	// Y�����̑��x��������
	mVelocityY = 0.0f;
	// �󒆂���̉����̏ꍇ��State��ύX����
	if (mPlayer->getMoveState()  == PlayerActor::ms_jump) {
		mPlayer->setMoveState(PlayerActor::ms_idle);
	}
}

void PlayerControl::StateDraw()
{
	// MoveState
	switch (mPlayer->getMoveState())
	{
	case PlayerActor::ms_idle: {
		DrawText("Move : Idle", 700, 50, 30, BLACK); break;
	}
	case PlayerActor::ms_walk: {

		DrawText("Move : Walk", 700, 50, 30, BLACK); break;
	}
	case PlayerActor::ms_dash: {
		DrawText("Move : Dash", 700, 50, 30, BLACK); break;
	}
	case PlayerActor::ms_jump: {
		DrawText("Move : Jump", 700, 50, 30, BLACK); break;
	}
	// ActionState
	}
	switch (mPlayer->getActionState())
	{
	case PlayerActor::as_idle: {
		DrawText("Action : idle", 700, 100, 30, BLACK); break;
	}
	case PlayerActor::as_attack: {
		DrawText("Action : attack", 700, 100, 30, BLACK); break;
	}
	case PlayerActor::as_guard: {
		DrawText("Action : guard", 700, 100, 30, BLACK); break;
	}
	}
}
