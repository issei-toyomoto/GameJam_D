#pragma once

#include "AbstractScene.h"
#include "Player.h"
#include "UI.h"
#include "common.h"


class GameMain : public AbstractScene {
private:
    int state;
    int score = 0;
    int Time;
    int StageNum = 1;

    int x;
    int y;

    int BackImg;    //背景画像
    int FlowerImg;  //
    int WeedImg;

    Player player; //プレイヤー
    UI ui;          //UI

    int Grass[MAP_HEIGHT][MAP_WIDTH];   //草・花の状態(0：何もない　1：草　2：花)
    int GrassTmp[MAP_HEIGHT][MAP_WIDTH];
    
    int ZeroCnt;
    int ItemCnt;

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;

    //ステージ初期化
    void SetStage(int level);

    int GetScore() { return score; }
};