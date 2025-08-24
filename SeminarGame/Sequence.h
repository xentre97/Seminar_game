#pragma once
#include <vector>
#include <raylib.h>
#include "Actor.h"

/// <summary>
/// �V�[�P���X�̐e�N���X
/// �^�C�g��,�Q�[�����,�Q�[���I�[�o�[�Ȃǂ��q�Ɏ���
/// 
/// </summary>
class Sequence
{
public:
    virtual ~Sequence();

    virtual void input();
    virtual void update();
    virtual void draw();

    virtual void unloadData() {};

    // �V�[���J�ڂ��K�v�ɂȂ����玟�̃V�[�P���X��Ԃ�
    virtual Sequence* nextSequence() { return nullptr; }

    void addActor(Actor* actor);
    void removeActor(Actor* actor);

protected:
    // ���̃V�[�P���X�ɑ��݂���A�N�^�[�̔z��
    std::vector<class Actor*> mActors;
    // �R���X�g���N�^��protected�ɂ��Ē��� new Sequence�ł��Ȃ��悤��
    Sequence() {};
};
