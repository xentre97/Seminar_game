#include "EnemyActor.h"
#include "GamePlay.h"
#include "SpriteComponent.h"
#include "PlayerActor.h"
#include "MoveComponent.h"

EnemyActor::EnemyActor(Sequence* sequence)
	: Actor(sequence)
{
	mTexture = LoadTexture("test.png");
	mPosition = Vector2{ 500.0f, 300.0f };
	mRectangle = {
		mPosition.x - mTexture.width / 2.0f,
		mPosition.y - mTexture.height / 2.0f,
		(float)mTexture.width,
		(float)mTexture.height
	};
	//プレイヤーから～マス以内に入ったら静止するための射程の概念の変数を定義(初期値2)
	attackRange = 5;
	//プレイヤー取得
	GamePlay* scene = static_cast<GamePlay*>(mSequence);
	mPlayer = scene->getPlayer();

	//MoveComponentを生成と保持
	mMoveComp = new MoveComponent(this);
	mMoveComp->setMoveSpeed(100.0f);


	static_cast<GamePlay*>(mSequence)->addEnemy(this);
	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(mTexture);
}

EnemyActor::~EnemyActor()
{
}
void EnemyActor::update()
{
	Actor::update();
	// Enemyの移動の実装
	// pPosition.xとmPosition.x
	Vector2 pPosition = mPlayer->getPosition();
	//水平移動
	if(abs(mPosition.x - pPosition.x) > attackRange || abs(mPosition.y - pPosition.x) > attackRange){
		//射程外にあるので、自身の位置に対するプレイヤーの位置の方向を取得(自身正なら-1、負なら1に進む)
		int xDirection = ((mPosition.x - pPosition.x) < 0) - ((mPosition.x - pPosition.x) > 0);
		//mPosition.x += xDirection;
		this->setForward(xDirection);

		//鉛直移動
		//if()

	}
	else{
		//静止しているので、攻撃の実装
		setForward(0);
	}
	mPosition.y += GetRandomValue(0,2.0);


	// Enemyの移動が完全に終了した後の位置を基に逐次描画するためのRectangle位置明示
	this->computeRectangle();
}

void EnemyActor::computeRectangle() {
	mRectangle.x = mPosition.x - mTexture.width / 2.0f;
	mRectangle.y = mPosition.y - mTexture.height / 2.0f;
}


void EnemyActor::jump() {
	if( mMoveComp && !mMoveComp->isJumping()) {
		mMoveComp->setVelocityY(mMoveComp->getJumpSpeed());
		mMoveComp->setJumping(true);
	}
}

void EnemyActor::fixFloorCol() {
	if (mMoveComp)
	{
		mMoveComp->setVelocityY(0.0f);
		mMoveComp->setJumping(false);
	}
}
