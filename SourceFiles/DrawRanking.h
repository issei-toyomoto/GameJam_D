#pragma once

#include "AbstractScene.h"

class DrawRanking : public AbstractScene {

public:
    DrawRanking();
    ~DrawRanking();

    // �`��ȊO�̍X�V������
    virtual AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const override;
};