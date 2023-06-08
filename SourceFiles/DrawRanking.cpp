#include"DrawRanking.h"
#include"main.h"

DrawRanking::DrawRanking()
{
    Ranking::ReadRanking();
};

DrawRanking::~DrawRanking()
{

};

AbstractScene* DrawRanking::Update()
{
    if (InputControl::OnButton(XINPUT_BUTTON_A)|| InputControl::OnButton(XINPUT_BUTTON_B))
    {
        return new Title();
    }

    return this;
};

void DrawRanking::Draw()const 
{
    SetFontSize(64);
    for (int i = 0; i < RANK_MAX; i++) {
        DrawFormatString(120, 100 + (i * 90), GetColor(255, 255, 255), "%d ˆÊ@ %s@%7d", Ranking::GetData(i).no, Ranking::GetData(i).name, Ranking::GetData(i).score);
    };

};