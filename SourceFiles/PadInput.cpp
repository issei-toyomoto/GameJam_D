#include "PadInput.h"
#include<math.h>

char InputControl::NowKey[BUTTONS];
char InputControl::OldKey[BUTTONS];
XINPUT_STATE InputControl::Input;
Stick InputControl::Rstick;
Stick InputControl::Lstick;


float InputControl::LstickRad()
{
    float L_X = Input.ThumbLX / MAXL_X;
    float L_Y = Input.ThumbLY / MAXL_Y;

    if (L_X == 0 && L_Y == 0)return 0;
    return (float)atan2(L_Y, L_X);
}

float InputControl::LstickTilt()
{
    float L_X = Input.ThumbLX / MAXL_X;
    float L_Y = Input.ThumbLY / MAXL_Y;

    L_X *= L_X;
    L_Y *= L_Y;

    if (L_X == 0 && L_Y == 0)return 0;
    return (float)sqrt(L_Y + L_X);
}