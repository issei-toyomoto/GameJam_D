#pragma once

#include "AbstractScene.h"

class DrawRanking : public AbstractScene {

public:
    DrawRanking();
    ~DrawRanking();

    // •`‰æˆÈŠO‚ÌXV‚ğÀ‘•
    virtual AbstractScene* Update() override;

    // •`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
    virtual void Draw() const override;
};