#include "AnimSpriteComponent.h"
#include <iostream>

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(30.0f)
	, mLoopFlag(true)
	, mAnimBegin(0)
	, mAnimEnd(1)
	, mIsAnimating(false)
{
}

void AnimSpriteComponent::update()
{
	SpriteComponent::update();

	if (mAnimTextures.size() > 0)
	{
		// ���[�v�A�j���[�V����
		if (mLoopFlag)
		{
			mCurrFrame += mAnimFPS / (float)GetFPS();
			int frameCount = mAnimEnd - mAnimBegin + 1;
		/*if (mCurrFrame >= mAnimEnd + 1)
		{
			mCurrFrame = mCurrFrame - (mAnimEnd + 1);
		}*/

			// ���[�v�␳
			if (mCurrFrame >= frameCount)
			{
				mCurrFrame = fmod(mCurrFrame, (float)frameCount);
			}
			setTexture(mAnimTextures[static_cast<int>(mCurrFrame + mAnimBegin)]);
		}
		// ���[�v����Ȃ��ꍇ
		else if (!mLoopFlag && mIsAnimating)
		{
			mCurrFrame += mAnimFPS / (float)GetFPS();
			if (mCurrFrame > mAnimEnd - mAnimBegin)
			{
				mCurrFrame = 0.0f;
				mIsAnimating = false;
			}
			setTexture(mAnimTextures[static_cast<int>(mCurrFrame + mAnimBegin)]);
		}
		// ���[�v�łȂ��A�j���[�V�����̏I�����A�擪�̃e�N�X�`���ɐݒ肷��
		else if (!mLoopFlag && !mIsAnimating)
		{
			setTexture(mAnimTextures[0]);
		}
	}
}

void AnimSpriteComponent::setAnimTextures(const std::vector<Texture2D>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// �擪�̃e�N�X�`����ݒ�
		mCurrFrame = 0.0f;
		setTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::play(int begin, int end, bool loop, float fps)
{
	mAnimBegin = begin;
	mAnimEnd = end;
	mAnimFPS = fps;
	mLoopFlag = loop;
	mCurrFrame = 0.0f;
	mIsAnimating = true;

	// �J�n���̃t���[����ݒ�
	setTexture(mAnimTextures[mAnimBegin]);
}