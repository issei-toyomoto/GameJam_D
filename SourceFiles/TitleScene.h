#pragma once

#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int state = 0;
    int ctrl_state;
    int img_title;
    int font[2][4];
    int bgm, se_cursor, se_select;
public:
    // �R���X�g���N�^
    Title();

    // �f�X�g���N�^
    ~Title();

	// �`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	// �`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;
};