#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "common.h"


class GameMain : public AbstractScene {
private:
    int state;
    int score = 0;

    int x;
    int y;

    int BackImg;    //�w�i�摜
    int FlowerImg;  //
    int WeedImg;

    Player player; //�v���C���[

    int Grass[MAP_HEIGHT][MAP_WIDTH];   //���E�Ԃ̏��(0�F�����Ȃ��@1�F���@2�F��)
    
public:
    // �R���X�g���N�^
    GameMain();

    // �f�X�g���N�^
    ~GameMain();

	// �`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	// �`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;

    //�X�e�[�W������
    void SetStage(int level);
};