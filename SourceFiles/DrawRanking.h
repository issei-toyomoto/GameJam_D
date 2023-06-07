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
    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};