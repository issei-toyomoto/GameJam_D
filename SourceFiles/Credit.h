#pragma once
#include "AbstractScene.h"

class Credit : public AbstractScene
{
private:
    int g_KeyFlg; //�������̓L�[��
    int g_OldKey; //�O��̓���
    int g_NowKey; //����̓��̓L�[
    int img_title;
public:
    // �R���X�g���N�^
    Credit();

    // �f�X�g���N�^
    ~Credit();

    // �`��ȊO�̍X�V������
    virtual AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const override;

};

