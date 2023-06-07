#pragma once
#include "AbstractScene.h"
#include"Ranking.h"
class DrawRanking: public AbstractScene {
private:
    int i;
    int  RANKING_MAX = 10;
    int Rank[10];

    Ranking ranking;

public:
    DrawRanking();
    ~DrawRanking();
    // •`‰æˆÈŠO‚ÌXV‚ğÀ‘•
    virtual AbstractScene* Update() override;

    // •`‰æ‚ÉŠÖ‚·‚é‚±‚Æ‚ğÀ‘•
    virtual void Draw() const override;
};