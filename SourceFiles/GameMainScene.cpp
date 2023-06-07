#include "common.h"
#include "main.h"
#include "Result.h"
#include "PadInput.h"

#include "Player.h"
#include "UI.h"


#define DEBUG

GameMain::GameMain() {
    // 初期化処理
    state = 0;

    BackImg = LoadGraph("images/back.png");
    FlowerImg = LoadGraph("images/flower.png");
    WeedImg = LoadGraph("images/kusa.png");
    
    SetStage(1);
};

GameMain::~GameMain() {
    // 終了処理
};

AbstractScene* GameMain::Update() { // ここで値の更新など、処理


    player.Update();

    if (InputControl::OnButton(XINPUT_BUTTON_START))return new Result(score);
    if (ui.Update() == -1) {
        return nullptr;
    };
    return this;    //シーン継続
};

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);
    DrawGraph(0, 0, BackImg, true);
    DrawBox(0, 0, 1280, 100, GetColor(0, 0, 0), TRUE);

    //花、草表示処理
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (Grass[i][j] == 2) {
                DrawGraph(MARGIN_X + (j * BLOCK_SIZE), MARGIN_Y + UI_SIZE + (i * BLOCK_SIZE), FlowerImg, true);
            }

            if (Grass[i][j] == 1) {
                DrawGraph(MARGIN_X + (j * BLOCK_SIZE), MARGIN_Y + UI_SIZE + (i * BLOCK_SIZE), WeedImg, true);
            }
        }
    }

    //花、草が消えた時のスコア処理
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            GrassTmp[i][j] = Grass[i][j];
        }
    }
   #ifdef DEBUG
    int margin = (SCREEN_HEIGHT - 100) % BLOCK_SIZE / 2;
    for (int i = 100 + margin; i < 720; i += BLOCK_SIZE)
    {
        DrawLine(margin, i, 1280 - margin, i, 0xffffff);
        if ((i - 100) / BLOCK_SIZE % 5 == 0)DrawLine(margin, i, 1280 - margin, i, 0xff0000);
    }

    margin = SCREEN_WIDTH % BLOCK_SIZE / 2;
    for (int i = margin; i < 1280; i += BLOCK_SIZE)
    {
        DrawLine(i, 100 + margin, i, 720 - margin, 0xffffff);
        if (i / BLOCK_SIZE % 5 == 0)DrawLine(i, 100 + margin, i, 720 - margin, 0xff0000);
    }

    DrawFormatString(200, 20, 0xffffff, "X    : %d", player.AtkPos('X'));
    DrawFormatString(200, 40, 0xffffff, "Y    : %d", player.AtkPos('Y'));
    DrawFormatString(200, 60, 0xffffff, "NONE : %d", player.AtkPos('Z'));
    
#endif
    
    player.Draw();

    ui.Draw();
};

void GameMain::SetStage(int stage) 
{

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            Grass[i][j] = 0;
            GrassTmp[i][j] = 0;
        }
    }

    for (int i = 0; i < FLOWER_NUM * stage; i++) {
        y = GetRand(MAP_HEIGHT);
        x = GetRand(MAP_WIDTH);
        if (Grass[y][x] == 0) {
            Grass[y][x] = FLOWER;
        }
        else {
            i--;
        }
        
    }
   
    for (int i = 0; i < WEED_NUM * stage; i++) {
        y = GetRand(MAP_HEIGHT);
        x = GetRand(MAP_WIDTH);
        if (Grass[y][x] == 0) {
            Grass[y][x] = WEED;
        }
        else {
            i--;
        }

    }
   
}