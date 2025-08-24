#pragma once
#include "Sequence.h"
#include "PlayerActor.h"

/// <summary>
/// GamePlay�V�[�P���X
/// </summary>
class GamePlay :
    public Sequence
{
public:
    GamePlay();
    ~GamePlay() override;

    void input() override;
    void update() override;
    void draw() override;
    void unloadData() override;
    Sequence* nextSequence() override;

    bool loadStage(const char* filename);

    void addEnemy(class EnemyActor* enemy);
    // �G�����񂾂Ƃ��ɌĂяo�����
    void destroyEnemy(class EnemyActor* enemy);
    std::vector<class EnemyActor*> const getEnemies() { return mEnemies; }
    // �G�₻�̑����v���C���[�����擾���邽�߂ɒ�`
    PlayerActor* getPlayer() const { return mPlayer; }

    void addSprite(class SpriteComponent* sprite);
    void removeSprite(class SpriteComponent* sprite);

    const int& getStageWidth() const { return mStageWidth; }

private:
    // collision�֘A�̍X�V�������܂Ƃ܂��Ă�
    void updateCollision();
    Sequence* mNext = nullptr;
    // �G�̔z��(���Collision�p�Ɏg��)
    std::vector<class EnemyActor*> mEnemies;
    class PlayerActor* mPlayer;
    // Sprite�̔z��
    std::vector<class SpriteComponent*> mSprites;
    // �X�e�[�W����ǂݍ��񂾎l�p�`�̔z��(����ǂ̕`��,collision�Ɏg�p)
    std::vector<struct Rectangle> mStageRecs;
    int mStageWidth;
    int mStageHeight;
    Camera2D mCamera;
};

// collision�̏�����collisionManager�݂����Ȃ̍����
// �O�ɏo���Ă����������ł�
