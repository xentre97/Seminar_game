#pragma once
#include "Actor.h"
#include <map>
#include "PlayerControl.h"

/// <summary>
/// PlayerActor�N���X
/// </summary>
class PlayerActor :
    public Actor
{
public:
    // �s���̏�ԂƃA�N�V�����̏�Ԃɕ�����
    // ���ꂼ��̏�Ԃ�\���ϐ�������(mMoveState,mActionState)
    // mActionState = ms_idle �͉\,�C��t����K�v������
    // enum�𕪂��Ă�����
    enum PlayerState
    {
        // moveState
        ms_idle,
        ms_walk,
        ms_dash,
        ms_jump,
        // actionState
        as_idle,
        as_attack,
        as_guard
    };
    PlayerActor(class Sequence* sequence);

    void input() override;
    void update() override;

    const Camera2D& getCamera() const ;
    class PlayerControl& getPlayerControl();
    PlayerState getMoveState() { return mMoveState; }
    PlayerState getActionState() { return mActionState; }
    
    void computeRectangle();
    void setMoveState(PlayerState state) { mMoveState = state; }
    void setActionState(PlayerState state) { mActionState = state; }
    
private:
    PlayerState mMoveState;
    PlayerState mActionState;
    class CameraComponent* mCameraComp;
    class PlayerControl* mPlayerControl;
    class AnimSpriteComponent* mAnimsc;
    bool mForward;
};

// ����
// AD : �ړ�
// Space : �W�����v
// Shift + �ړ� : �_�b�V��
// S : �K�[�h(�ړ�,�W�����v�s��)
// W : �U��

// ��� ��Ԃɂ���ăA�j���[�V������ς���
// �U��...1���̊G
// �ړ�...���[�v�A�j���[�V����
// �W�����v...�W�����v�̊G
// �K�[�h...�ꖇ�̊G
// ���Ă����(��U�ۗ�)