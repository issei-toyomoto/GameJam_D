#include "RunWeed.h"
#include"common.h"
#include"DxLib.h"
#include<Math.h>

RunWeed::RunWeed(float InitX, float InitY)
{
    //�����̍��W
    X = InitX;
    Y = InitY;

    //�ō����x��ݒ肷��
    SpdX = 0;
    SpdY = 0;
    MSpd = 16;

    //�摜��ݒ肷��
    Image = LoadGraph("images/kusa.png");
}

RunWeed::~RunWeed()
{
}

void RunWeed::Update(float Px, float Py)
{

    //�v���C���[�Ԃ�X���AY���Ƃ̋��������
    float DisX = X - Px;
    float DisY = Y - Py;

    //�v���C���[�Ԃ̋���
    float AbsX = fabsf(Px - X);
    float AbsY = fabsf(Py - Y);
    float Dis = (float)sqrt(AbsX * AbsX + AbsY * AbsY);

    //�[�����Z�h�~
    //if (DisX == 0.f)DisX = 1.f;
    //if (DisY == 0.f)DisY = 1.f;

    //�ǂ��l�߂�ꂽ���̓���
    //��ʍ��[�ɒǂ��l�߂�ꂽ��
    if (X < MARGIN_X + BLOCK_SIZE)
    {
        //����̊p�ɂ��鎞
        if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE)
        {
            //�v���C���[�̈ʒu�ɉ����ĉE�����ɓ�����
            if (Px < Py - UI_SIZE)
            {
                DisX = 1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = 1;
            }
        }
        //�����̊p�ɂ��鎞
        else if (SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
        {
            //�v���C���[�̈ʒu�ɉ����ĉE����ɓ�����
            if (Px < SCREEN_HEIGHT - Py)
            {
                DisX = 1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = -1;
            }
        }
        //�p�ɂ��Ȃ��Ƃ�
        else
        {
            //�v���C���[�ƕǂƂ̔��ˊp�����悤�ɓ�����
            DisX = -DisX;
        }
    }
    //��ʉE�[�ɒǂ��l�߂�ꂽ��
    else if (SCREEN_WIDTH - MARGIN_X - BLOCK_SIZE < X)
    {
        //�E��̊p�ɂ��鎞
        if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE)
        {
            //�v���C���[�̈ʒu�ɉ����č������ɓ�����
            if (SCREEN_WIDTH - Px < Py - UI_SIZE)
            {
                DisX = -1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = 1;
            }
        }
        //�E���̊p�ɂ��鎞
        else if (SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
        {
            //�v���C���[�̈ʒu�ɉ����č�����ɓ�����
            if (SCREEN_WIDTH - Px < SCREEN_HEIGHT - Py)
            {
                DisX = -1;
                DisY = 0;
            }
            else
            {
                DisX = 0;
                DisY = -1;
            }
        }
        //�p�ɂ��Ȃ��Ƃ�
        else
        {
            //�v���C���[�ƕǂƂ̔��ˊp�����悤�ɓ�����
            DisX = -DisX;
        }
    }
    //��ʏォ���̒[�ɂ���Ƃ�
    else if (Y < MARGIN_Y + UI_SIZE + BLOCK_SIZE || SCREEN_HEIGHT - MARGIN_Y - BLOCK_SIZE < Y)
    {
        //�v���C���[�ƕǂƂ̔��ˊp�����悤�ɓ�����
        DisY = -DisY;
    }

    //�v���C���[���痣��邽�߂̊p�x
    float Rad = (float)atan2(DisY, DisX);

    //�v���C���[�Ԃ̋���
    //DisX = fabsf(Px - X);
    //DisY = fabsf(Py - Y);
    //float Dis = (float)sqrt(DisX * DisX + DisY * DisY);

    //�p�x���W�A��
    float InpX = (float)cos(Rad);
    float InpY = (float)tan(Rad);


    //�v���C���[�Ƃ̋��������ȏ�Ȃ����
    if (Dis <= 150 && RunCool == 0)
    {
        RunTime = 15;
        RunCool = RunTime + 60;
        RunRad = Rad;
    }

    if (RunTime)
    {
        //X��
        SpdX = MSpd * (float)cos(RunRad);

        //Y��
        SpdY = MSpd * (float)sin(RunRad);
        RunTime--;
    }
    //�X�e�B�b�N�̌X�������ȉ��Ȃ猸��
    else
    {
        SpdX = 0;
        SpdY = 0;
    }

    if (--RunCool < 0)RunCool = 0;

    //X���W��X���x�ɉ����ĕω�������
    X += SpdX;
    //��ʒ[�ɂ��ǂ蒅�����Ƃ��ɕ␳����
    while (X - BLOCK_SIZE / 2 < MARGIN_X)
    {
        X++;
    }

    while (SCREEN_WIDTH - MARGIN_X < X + BLOCK_SIZE / 2)
    {
        X--;
    }

    //Y���W��Y���x�ɉ����ĕω�������
    Y += SpdY;
    //��ʒ[�ɂ��ǂ蒅�����Ƃ��ɕ␳����
    while (Y - BLOCK_SIZE / 2 < MARGIN_Y + 100)
    {
        Y++;
    }

    while (SCREEN_HEIGHT - MARGIN_Y < Y + BLOCK_SIZE / 2)
    {
        Y--;
    }
}

void RunWeed::Draw() const
{
    //DrawBox(X - BLOCK_SIZE / 2, Y - BLOCK_SIZE / 2, X + BLOCK_SIZE / 2, Y + BLOCK_SIZE / 2, 0x00ff00, true);
    DrawRotaGraph(X, Y, 1, 0, Image, true);
}