#include "ranking.h"
#include"DxLib.h"
ranking::ranking()
{
   /* ranking[i];*/
    i = 0;
    RANKING_MAX;
}
void ranking::Update()
{

}
void ranking::Draw()const
{
    for (int i = 0; i < RANKING_MAX; i++) {
        DrawFormatString(120, 100 + (i * 30), GetColor(255, 255, 255), "%d 位　 %.1f 秒", i + 1, Ranking[i]);
    }
}