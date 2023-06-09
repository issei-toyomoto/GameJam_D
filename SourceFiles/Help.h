#pragma once

#include "AbstractScene.h"

#define FONT_TYPE_DEFAULT 0
#define FONT_TYPE_LOAD_1 1

#define FONT_SIZE_128 0
#define FONT_SIZE_64 1
#define FONT_SIZE_32 2
#define FONT_SIZE_16 3

class Help : public AbstractScene {
private:
    int state = 0;
    int ctrl_state;
    int img_title, img_ctrl, img_help[7];
    int font[2][4];
    int bgm, se_cursor, se_select;

    int AnimImg;    //��ʈڍs���o�Ɏg���摜
    int Anim;       //��ʈڍs���o�Ǘ�
    bool Start;     //�Q�[�����C���Ɉڍs����Ȃ�true
public:
    // �R���X�g���N�^
    Help();

    // �f�X�g���N�^
    ~Help();

	// �`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	// �`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;
};