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
    // �`��ȊO�̍X�V������
    virtual AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const override;
};