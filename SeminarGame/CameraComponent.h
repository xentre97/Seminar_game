#pragma once
#include "Component.h"
#include <raylib.h>

/// <summary>
/// �J�����̊��(���̂܂܎g���Ă��邪)
/// </summary>
class CameraComponent :
    public Component
{
public:
    CameraComponent(class Actor* owner);
    void update() override;
    const Camera2D& getCamera() const { return mCamera; }
private:
    Camera2D mCamera;
    float mStageWidth;
    float mStageHeight;
};

