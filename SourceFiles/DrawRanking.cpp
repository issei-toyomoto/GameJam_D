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
    if (InputControl::OnButton(XINPUT_BUTTON_A))
    {
        return new Title();
    }

    return this;
};

void DrawRanking::Draw()const 
{
    for (int i = 0; i < RANK_MAX; i++) {
        DrawFormatString(120, 100 + (i * 30), GetColor(255, 255, 255), "%d ˆÊ@ %s@%7d", Ranking::GetData(i).no, Ranking::GetData(i).name, Ranking::GetData(i).score);
    };

};