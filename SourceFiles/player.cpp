#include"common.h"
#include "player.h"
#include"DxLib.h"
#include"PadInput.h"
#include<Math.h>

Player::Player()
{
    //�����̍��W
    X = SCREEN_WIDTH / 2;
    Y = SCREEN_HEIGHT / 2 + UI_SIZE / 2;

    //�ō����x��ݒ肷��
    SpdX = 0;
    SpdY = 0;
    MSpdX = 8;
    MSpdY = 8;

    SickleIng = LoadGraph("images/kama.png");
}

Player::~Player()
{
}

void Player::Update() 
{
    //�X�e�B�b�N���͒l
    float InpX = InputControl::TipLeftLStick(STICKL_X);
    float InpY = -InputControl::TipLeftLStick(STICKL_Y);

    //�X�e�B�b�N�p�x�E�X��
    float Rad = InputControl::LstickRad();
    float Tilt = InputControl::LstickTilt();

    //�����x
    float add = 0.2;

    //�X�e�B�b�N�̌X�������ȏ�Ȃ����
    if (0.2 <= Tilt && !Attack) 
    {
        //�p�x�擾
        Angle = 180 / 3.14 * Rad + 180;
        
        //�U�������𓾂�
        Way = (Angle - 22.5) / 45;
        if (Angle < 22.5 || 360 - 22.5 < Angle)Way = 7;

        //X��
        SpdX += add * InpX;
        //���x���ő呬�x�ȏ�Ȃ璲������
        if (0 < InpX && MSpdX * InpX < SpdX)SpdX = MSpdX * InpX;
        if (InpX < 0 && SpdX < MSpdX * InpX)SpdX = MSpdX * InpX;

        //Y��
        SpdY += add * InpY;
        //���x���ő呬�x�ȏ�Ȃ璲������
        if (0 < InpY && MSpdY * InpY < SpdY)SpdY = MSpdY * InpY;
        if (InpY < 0 && SpdY < MSpdY * InpY)SpdY = MSpdY * InpY;
    }
    //�X�e�B�b�N�̌X�������ȉ��Ȃ猸��
    else 
    {
        //���x�̍��v�����
        float absX = fabsf(SpdX);
        float absY = fabsf(SpdY);
        float total = absX + absY;

        if (Attack) 
        {
            absX *= 3;
            absY *= 3;
        }

        //X���x�����v�ɑ΂���䗦�ɉ����Č���������
        if (SpdX < 0)
        {
            SpdX += add * (absX / total);
            if (0 < SpdX)SpdX = 0;
        }
        else if (0 < SpdX)
        {
            SpdX -= add * (absX / total);
            if (SpdX < 0)SpdX = 0;
        }

        //Y���x�����v�ɑ΂���䗦�ɉ����Č���������
        if (SpdY < 0)
        {
            SpdY += add * (absY / total);
            if (0 < SpdY)SpdY = 0;
        }
        else if (0 < SpdY)
        {
            SpdY -= add * (absY / total);
            if (SpdY < 0)SpdY = 0;
        }
    }

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

    if (Attack) 
    {
        Attack++;
        if (20 < Attack) 
        {
            Attack = 0;
            Combo = 0;
        }
    }

    if (InputControl::OnButton(XINPUT_BUTTON_B) && Attack == 0)
    {
        Attack++;
        Combo++;
    }
}

void Player::Draw() const
{
    DrawBox(X - BLOCK_SIZE / 2, Y - BLOCK_SIZE / 2, X + BLOCK_SIZE / 2, Y + BLOCK_SIZE / 2, 0x0000ff, true);

    DrawFormatString(200, 20, 0xffffff, "%d", Way);
    
    if (Attack) 
    {
        double stX = 0, stY = 0;		//�U�肩�Ԃ�O�̍��W
        double finX = 0, finY = 0;		//�U�肩�Ԃ�����̍��W
        double Dis = 0;			//�̂̒��S����̋���

        double finAng = 0;	//�U�肩�Ԃ�p�x
        if (Attack <= 6) 
        {
            finAng = 45 * (-Way + 3) + (180 / 5 * (Attack - 1));
            stX = X;
            stY = Y;
            Dis = 70;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
        else
        {
            finAng = 45 * (-Way + 3) + 180;
            stX = X;
            stY = Y;
            Dis = 70;

            finX = stX + Dis * cos((3.14 / 180) * (finAng - 90));
            finY = stY + Dis * sin((3.14 / 180) * (finAng - 90));
        }
        DrawRotaGraph(finX, finY, 1, (3.14 / 180) * finAng, SickleIng, true, true);
    }
}
