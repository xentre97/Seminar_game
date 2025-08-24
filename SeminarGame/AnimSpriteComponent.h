#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <raylib.h>

/// <summary>
/// �A�j���[�V�����t���X�v���C�g�̕`��
/// </summary>
class AnimSpriteComponent :
    public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
    // ���̃t���[�����ƂɃA�j���[�V�������X�V component����override
    void update() override;
    // �A�j���[�V�����Ɏg���e�N�X�`���̐ݒ�
    void setAnimTextures(const std::vector<Texture2D>& textures);
    // �A�j���[�V�������Đ�����
    void play(int begin, int end, bool loop, float fps = 60.0f);

private:
    // �A�j���[�V�����ł̂��ׂẴe�N�X�`��
    std::vector<Texture2D> mAnimTextures;
    // ���ݕ\�����Ă���t���[��
    float mCurrFrame;
    // �A�j���[�V������FPS ���I�ɕύX�\
    float mAnimFPS;
    bool mLoopFlag;
    int mAnimBegin;
    int mAnimEnd;
    bool mIsAnimating;
};