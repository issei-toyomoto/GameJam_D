#pragma once
#include "AbstractScene.h"
#include "Ranking.h"
#include "DxLib.h"
#include "PadInput.h"
#include <string>

class InputRankingScene : public AbstractScene
{
private:
    RankingData ranking;

    int Img;	//背景画像格納用
    int Score;	//スコア格納用
    bool XOnce;	//Lスティック入力重複防止用（横）
    bool YOnce;	//Lスティック入力重複防止用（縦）

    //SE用
    int SelectSE;
    int DecisionSE;

    //フォント用
    int NameFont1;
    int NameFont2;
    int NameFont3;
    std::string Name;	//名前入力用

    POINT CursorPoint;	//カーソルの座標用

    //入力可能文字格納
    const char KeyBoard[5][14] = { "ABCDEFGHIJKLM" ,"NOPQRSTUVWXYZ" ,"abcdefghijklm" ,"nopqrstuvwxyz" ,"0123456789" };

public:

    //コンストラクタ
    InputRankingScene(int score);

    //デストラクタ
    ~InputRankingScene();

    //描画以外の更新を実行
    AbstractScene* Update()override;

    //描画に関することを実装
    void Draw()const override;
};

