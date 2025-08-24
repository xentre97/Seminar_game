#include "SpriteComponent.h"
#include "Actor.h"
#include "GamePlay.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	: Component(owner)
	, mTexture()
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	static_cast<GamePlay*>(mOwner->getSequence())->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	static_cast<GamePlay*>(mOwner->getSequence())->removeSprite(this);
}

void SpriteComponent::draw()
{
	if (IsTextureValid(mTexture))
	{
		Vector2 pos = mOwner->getPosition();
		// �`��
		Rectangle src = { 0, 0, mOwner->getForward() * (float)mTexWidth, (float)mTexHeight };
		Rectangle dst = { pos.x, pos.y, (float)mTexWidth, (float)mTexHeight };
		Vector2 origin = { mTexWidth / 2.0f, mTexHeight / 2.0f };
		DrawTexturePro(mTexture, src, dst, origin, 0.0f, WHITE);
	}
}

void SpriteComponent::setTexture(Texture2D texture)
{
	// Draw�֐����g����悤�� (mTexture��nullptr�ł͂Ȃ��Ȃ�,true��Ԃ�)
	mTexture = texture;
	// �e�N�X�`���̍����ƕ������߂�
	mTexWidth = mTexture.width;
	mTexHeight = mTexture.height;
}
