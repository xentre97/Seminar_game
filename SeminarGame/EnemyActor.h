#pragma once
#include "Actor.h"

/// <summary>
/// �G�A�N�^�[
/// �K�v�ɉ����Ă܂��p������
/// </summary>
class EnemyActor :
    public Actor
{
public:
    EnemyActor(class Sequence* sequence);
    ~EnemyActor();

    void update() override;
    void computeRectangle();

    void jump();
    void fixFloorCol();

private:
    class PlayerActor* mPlayer;
    class MoveComponent* mMoveComp;
    int attackRange;
};

