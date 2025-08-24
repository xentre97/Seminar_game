#include "CameraComponent.h"
#include "Actor.h"
#include "GamePlay.h"

CameraComponent::CameraComponent(Actor* owner)
	: Component(owner)
	, mCamera({ 0 })
	, mStageWidth(0.0f)
	, mStageHeight(0.0f)
{
	mCamera.zoom = 1.0f;
	mCamera.rotation = 0.0f;
	mCamera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	// getSequence�͐݌v�Ƃ��Ĕ�����������Ȃ�
	// stage�N���X���V���O���g���ō��Ƃ��̕������������H
	mStageWidth = static_cast<GamePlay*>(mOwner->getSequence())->getStageWidth();
}

void CameraComponent::update()
{
	// owner��x���W��ǂ�
	float targetX = mOwner->getPosition().x;
	
	float centerX = GetScreenWidth() / 2.0f;

	// �v���C���[����ʂ̍��[���璆���ɗ���܂ł̓J�������Œ�
	if (mOwner->getPosition().x < centerX) {
		targetX = centerX;
	}
	// �X�e�[�W�E�[�ɓ��B������J�����Œ�
	if (mOwner->getPosition().x > mStageWidth - centerX) {
		targetX = mStageWidth - centerX;
	}
	mCamera.target = { targetX, GetScreenHeight() / 2.0f };
}
