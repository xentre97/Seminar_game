#pragma once
#include "Component.h"

/// <summary>
/// �A�N�^�[��Hp����������
/// Component�������̂́A�G�E�v���C���[�E�j��ł���I�u�W�F�N�g���ɃA�^�b�`���邱�Ƃ�z�肵������
/// </summary>
class HpComponent :
    public Component
{
public:
    HpComponent(class Actor* owner, float maxHp = 1.0f, float invincibleDuration = 1.0f);

    void update() override;

    // bool�^��true�Ȃ琶���Afalse�Ȃ玀�S�𔻒�B�_���[�W�������Ōv�Z���Ă���
    bool TakeDamage(float damage);
    void Recover(float recover);

    // 0�ȉ���
    bool IsKilled() const { return mCurHp <= 0.0f; }

    //���ݖ��G���Ԓ����ǂ�����Ԃ�
    bool isInvincible() const { return mInvincibleTime > 0.0f; }

    // Getter,Setter
    float GetCurHp() const { return mCurHp; }
    void SetMaxHp(float maxHp) { mMaxHp = maxHp, mCurHp = maxHp; }
    // �֗��n(SetterGetter�ł��ł��邯��...�Ƃ����z)
    float GetHpPercentage() const { return mCurHp / mMaxHp; }
    // �ő�Hp���₷
    void AddMaxHp(float add);

private:
    float mCurHp;   // ����Hp
    float mMaxHp;   // �ő�Hp ��������Actor���Ŏ������Ă������Ǝv���܂�(����Ă݂Ď���)

    float mInvincibleTime;
    float mInvincibleDuration;
};

