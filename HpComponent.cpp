#include "HpComponent.h"
#include <iostream>
#include <raylib.h>
#include "Actor.h"

HpComponent::HpComponent(Actor* owner, float maxHp, float invincibleDuration)
	: Component(owner)
	, mMaxHp(maxHp)
	, mCurHp(maxHp)
	, mInvincibleDuration(invincibleDuration)
	, mInvincibleTime(0.0f) //�����l��0�Ŗ��G�łȂ��Ƃ���
{
}
// ���ǉ��Fupdate�֐��̋�̓I�ȏ���������
void HpComponent::update()
{
	// ���G���Ԃ��c���Ă���ꍇ
	if (mInvincibleTime > 0.0f)
	{
		// �o�ߎ��ԁi�f���^�^�C���j���^�C�}�[�������
		mInvincibleTime -= GetFrameTime();
	}
}

bool HpComponent::TakeDamage(float damage)
{
	if (isInvincible()) {
		return false;
	}

	mInvincibleTime = mInvincibleDuration;
	// hp��0�ȉ��ɂȂ�Ȃ�
	mCurHp -= damage;
	if (mCurHp <= 0.0f) {
		mCurHp = 0.0f;
		return true;
	}
	//�f�o�b�O�p
	std::cout << "mCurHp=" << mCurHp << std::endl;
	return false;
}

void HpComponent::Recover(float recover)
{
	// hp��mMaxHp�𒴂��Ȃ�
	float diff = mMaxHp - mCurHp;
	if (diff <= recover) {
		recover = diff;
	}
	mCurHp += recover;
}

void HpComponent::AddMaxHp(float add)
{
	mMaxHp += add;
	mCurHp += add;
}
